#include "engine/camera.h"
#include "engine/core.h"
#include "engine/graphics/shaders.h"
#include "engine/graphics/framebuffer.h"
#include "engine/objects/base.h"
#include "engine/objects/block.h"
#include "engine/objects/objects.h"
#include "engine/objects/model.h"
#include "engine/utils/glerrors.h"
#include "engine/utils/font.h"

#include "engine/objects/mesh.h"

#include "game/demoChunkGen.h"
#include "game/control.h"
#include "game/shaders.h"
#include "game/skybox.h"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <typeinfo>
#include <vector>
#include <functional>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_log.h>

// TODO: novideo framebuffer problem

int main(int argc, char* argv[]) {
    // Initialization & Creating window
#ifdef __ANDROID__
    SDL_DisplayMode display = bebra::init(bebra::GApi::OpenGLES); // Only GLES or Vulkan(not implemented(And unlikely to be :З))
#else
    SDL_DisplayMode display = bebra::init(bebra::GApi::OpenGL); // TODO: OpenGLES
#endif
    bebra::Window window {"BebraCraft", display, SDL_WINDOW_OPENGL};
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    bebra::glContextCreate(window);
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    // Creating camera in postision:
    bebra::Camera camera { glm::vec3(-2.0f, 8.0f, 6.0f) };
    camera.speed = 0.05;

    // Creating screen object and G-Buffer
    bebra::graphics::ShaderProgram screenShader {"shaders/screen.vert", "shaders/screen.frag"};
    bebra::graphics::ScreenObject screen {
        (uint)window.mode.w, (uint)window.mode.h, screenShader
    };

    // Loading font
    bebra::graphics::ShaderProgram fontShader {"shaders/font.vert", "shaders/font.frag"};
    bebra::utils::Font text {"./fonts/Monocraft.ttf", fontShader, 18};

    // Objects
        // Creating skybox
    craft::skybox skybox { bebra::graphics::ShaderProgram {"shaders/skybox.vert", "shaders/skybox.frag"} };
        // Loading shaders
    bebra::graphics::ShaderProgram blockShader {"shaders/block.vert", "shaders/block.frag"};
    craft::BlockShaderApi blockShaderSet {blockShader};
        // Buffers
    GLuint VBO, plantVAO, fluidVAO, blockVAO, EBO;
    bebra::objects::Plant::loadObject(VBO, plantVAO, EBO);
    bebra::objects::Fluid::loadObject(VBO, fluidVAO, EBO);
    bebra::objects::Block::loadObject(VBO, blockVAO, EBO);

    // Test models:
    bebra::objects::Model senko {"./senko.gltf"}; // :з
    bebra::graphics::ShaderProgram entityShader {"shaders/entity.vert", "shaders/entity.frag"};
    craft::BlockShaderApi entityShaderSet {entityShader}; // compatible
    
    // Loading chunks
    auto chunk = craft::genChunk();
    bebra::world::Chunk testCoolChunk {&chunk, 0, 0};

    // Runtime vars
    std::list<SDL_Keycode> keyPressed;
    float worldTime = 0.0, rawTime = 0.0;
    float maxFrametime = 0.0;
    auto start = SDL_GetPerformanceCounter();

    while (window.isRunning) { // Render cycle
        uint chunkCallsCounter = 0;

        { // Handling input and window events
            bool isModeChanged = false;
            handleInput(keyPressed, camera, window, isModeChanged);
            if (isModeChanged)
                screen.updateMode(window.mode.w, window.mode.h);
        }

        // Calculate shadertime
        //worldTime += 0.001;
        rawTime = 0.5 + (glm::cos(worldTime) / 2.0);

        // Position calculation // Todo: put into a camera class
        glm::mat4 model          = glm::rotate(glm::mat4(1.0f), 1.0f * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 view           = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
        glm::mat4 viewIdenpedent = glm::mat4(glm::mat3(view));
        glm::mat4 projection     = glm::perspective(
                                        glm::radians(camera.fov),
                                        float(window.mode.w) / float(window.mode.h),
                                        0.1f, 300.0f
                                    ); // 300 - render distance
        glm::mat4 projectionFont = glm::ortho(0.0f, float(window.mode.w), 0.0f, float(window.mode.h));

        glm::vec3 direction;
            direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
            direction.y = sin(glm::radians(camera.pitch));
            direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front = glm::normalize(direction);

        // Offscreen rendering in G-Buffer // TODO: fix for opengles
		screen.gbuffer->bind();
        screen.clear();
        skybox.render(viewIdenpedent, projection, rawTime);
        if (window.debug.lines)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        { // Chunks rendering
            static auto cameraBlocksPos = glm::value_ptr(camera.pos);

            static std::function chunkPass = [&](bebra::objects::ObjIdent who) {
                blockShader.use();
                blockShaderSet.model(model);
                blockShaderSet.view(view);
                blockShaderSet.projection(projection);
                blockShaderSet.worldTime(rawTime);
                for (int iLayer = 0; iLayer < 15; iLayer++) {
                    bebra::objects::chunkLayer& layer = chunk.at(iLayer);
                    for (int iRow = 0; iRow < 16; iRow++) {
                        bebra::objects::chunkRow& row = layer.at(iRow);
                        for (int iBlock = 0; iBlock < 16; iBlock++) {
                            const bebra::objects::Object* block = row.at(iBlock);
                            
                            // Check for air
                            if (!block->texture.arraySize || block->id == bebra::objects::ebase) continue;

                            //
                            if(!((who == block->id) ||
                                ((who == bebra::objects::etransparent) && (block->id == bebra::objects::eplant)) ||
                                ((who == bebra::objects::esemitransparent) && (block->id == bebra::objects::efluid))
                            )) continue;

                            if (who == bebra::objects::esemitransparent)
                                glDepthMask(GL_FALSE);

                            // Pick right buffers for current object
                            switch(block->id) {
                                case bebra::objects::eplant: { glBindVertexArray(plantVAO); break; }
                                case bebra::objects::efluid: { glBindVertexArray(fluidVAO); break; }
                                default: { glBindVertexArray(blockVAO); break; }
                            }

                            // Block space transformation
                            glm::mat4 model = glm::mat4(1.0f);
                            model = glm::translate(model, { iBlock, iLayer, iRow });

                            //if (block->rotate != 0.0)
                            //    model = glm::rotate(model, glm::radians(block->rotate), { 0.0, 1.0, 0.0 });
                            blockShaderSet.model(model);

                            // TODO: texture sets manager
                            GLint textureSlot = GL_TEXTURE31;
                            GLint textureSlotIndex = 31; // < Max texture slots
                            glActiveTexture(textureSlot + textureSlotIndex);
                            glBindTexture(GL_TEXTURE_2D_ARRAY, block->texture.textureArray);
                            glUniform1i(glGetUniformLocation(blockShader.program, "textureArray"), (textureSlot-GL_TEXTURE0)+textureSlotIndex);
                            if (block->id == bebra::objects::eplant) {
                                glDisable(GL_CULL_FACE);
                                glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
                                glEnable(GL_CULL_FACE);
                            } else {
                                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                            }
                            chunkCallsCounter++;

                            if (who == bebra::objects::esemitransparent)
                                glDepthMask(GL_TRUE);
                        }
                    }
                }
            };

            chunkPass(bebra::objects::esolid);
            chunkPass(bebra::objects::etransparent);
            { // Test draw entity
                entityShader.use();
                entityShaderSet.model(model);
                entityShaderSet.view(view);
                entityShaderSet.projection(projection);
                entityShaderSet.worldTime(rawTime);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, senko._TMP_tex);
                glUniform1i(glGetUniformLocation(entityShader.program, "texture"), 0);
                for (auto& mesh : senko.meshes) {
                    //if (!mesh.internalName.compare("rightarm")) {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, { 10, 6.5, 4}); // before rotating!
                        //model = glm::translate(model, {camera.pos.x + 0.3, camera.pos.y - 1.5f, camera.pos.z}); // before rotating!
                        model *= mesh.transform;
                        entityShaderSet.model(model);
                        mesh.render();
                    //}
                }
            }
            chunkPass(bebra::objects::esemitransparent);

            // Mesh test:
            //testCoolChunk.meshSolid.render();

        }
        // TODO: game::objectsIds

        {// Render from G-Buffer
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            screen.gbuffer->unbind();
            screen.clear();
            screen.render(!window.debug.nohud);
        }

        { // Calculate frametime & FPS
            auto end = SDL_GetPerformanceCounter();
            float Frametime = ((end - start) * 1000.0) / (float)SDL_GetPerformanceFrequency();
            if (Frametime > maxFrametime)
                maxFrametime = Frametime;
            else
                maxFrametime = ((maxFrametime * 50.0) + Frametime) / 51.0;
            start = end;

            // Render HUD
            if (!window.debug.nohud) {
                static std::function topOffset = [&](uint lineFromTop) {
                    return float(window.mode.h) - ((float(std::max(text.width, text.height)) + 5.0) * (lineFromTop + 1));
                };

                text.render("Frametime: " + std::to_string(Frametime) + "ms" +
                            " / 2%Max: " + std::to_string(maxFrametime) + "ms",
                            projectionFont, 10.0, topOffset(0));
                text.render("Graphics calls: " + std::to_string(chunkCallsCounter), projectionFont, 10.0, topOffset(1));
                text.render("BebraCraft pre-alpha: " + std::string(__DATE__), projectionFont, 10.0, topOffset(2));
                text.render("Testchunk", projectionFont, 10.0, topOffset(3));
            }
        }

        bebra::utils::glHandleError(glGetError());
        SDL_GL_SwapWindow(window.itself);
    }

    SDL_Quit();
    return 0;
}
