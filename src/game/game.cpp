#include "SDL_video.h"
#include "engine/camera.h"
#include "engine/core.h"
#include "engine/graphics/shaders.h"
#include "engine/graphics/framebuffer.h"
#include "engine/objects/objects.h"
#include "engine/utils/glerrors.h"
#include "engine/utils/font.h"

#include "engine/objects/mesh.h"

#include "game/demoChunkGen.h"
#include "game/control.h"
#include "game/shaders.h"
#include "game/skybox.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_log.h>

int main(int argc, char* argv[]) {
    // Initialization & Creating window
    SDL_DisplayMode display = bebra::init(bebra::GApi::OpenGL);
    bebra::Window window {"BebraCraft", display, SDL_WINDOW_OPENGL};
    bebra::glContextCreate(window);
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    // Creating camera in postision:
    bebra::Camera camera { glm::vec3(-2.0f, 8.0f, 6.0f) };
    camera.speed = 0.05;

    // Creating screen object and G-Buffer
    bebra::graphics::ShaderProgram screenShader {"shaders/screen.vert", "shaders/screen.frag"}; // FIXME GL::ERROR::1281 -> INVALID_VALUE
    bebra::graphics::ScreenObject screen {
        (uint)window.mode.w, (uint)window.mode.h, screenShader
    };

    // Objects // TODO: texture manager
        // Creating skybox
    craft::skybox skybox { bebra::graphics::ShaderProgram {"shaders/skybox.vert", "shaders/skybox.frag"} }; // FIXME GL::ERROR::1281 -> INVALID_VALUE
        // Loading shaders
    bebra::graphics::ShaderProgram blockShader {"shaders/block.vert", "shaders/block.frag"}; // FIXME GL::ERROR::1281 -> INVALID_VALUE
    craft::BlockShaderApi blockShaderSet {blockShader};
        // Buffers
    GLuint VBO, plantVAO, fluidVAO, blockVAO, EBO;
    bebra::objects::Plant::loadObject(VBO, plantVAO, EBO);
    bebra::objects::Block::loadObject(VBO, blockVAO, EBO);
    bebra::objects::Fluid::loadObject(VBO, fluidVAO, EBO);

    // Loading font
    bebra::graphics::ShaderProgram fontShader {"shaders/font.vert", "shaders/font.frag"};
    bebra::utils::Font text {"./fonts/Monocraft.ttf", fontShader, 18};

    // Loading chunks
    auto chunk = craft::genChunk();
    int chunkSize = static_cast<int>(chunk.size());

    // Mesh test...
    bebra::objects::Mesh testmesh;
    testmesh.move({10.0, 10.0, 10.0});
    bebra::objects::Mesh testmesh2;
    testmesh += testmesh2;

    // Runtime vars
    std::list<SDL_Keycode> keyPressed;
    float worldTime = 0.0, rawTime = 0.0;
    float maxFrametime = 0.0;

    Uint64 start = SDL_GetPerformanceCounter();
    while (window.isRunning) { // Render cycle
        uint chunkCallsCounter = 0;
        // Calculate shadertime
        //worldTime += 0.001;
        rawTime = 0.5 + (glm::cos(worldTime) / 2.0);

        // Handling input and window events
        bool isModeChanged = false;
        handleInput(keyPressed, camera, window, isModeChanged);

        if (isModeChanged)
            screen.updateMode(window.mode.w, window.mode.h);

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

        // Offscreen rendering in G-Buffer
		screen.gbuffer->bind();
        screen.clear();
        skybox.render(viewIdenpedent, projection, rawTime);

        if (window.debug.lines)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    

        // TODO: chunks loader -> mesh
        //for (int x = 0; x < 16; x++) for (int y = 0; y < 16; y++) // CALLS OVERHEAD
        { // Chunks render
            blockShader.use();
            blockShaderSet.model(model);
            blockShaderSet.view(view);
            blockShaderSet.projection(projection);
            blockShaderSet.worldTime(rawTime);
            static auto cameraBlocksPos = glm::value_ptr(camera.pos);

            // Functor: Render single layer of chunk
            static std::function layerFunctor = [&](bebra::objects::chunk& chunk, int iLayer) {
                bebra::objects::chunkLayer& layer = chunk.at(iLayer);

                // Functor: Render single row of chunk 
                static std::function rowFunctor = [&](bebra::objects::chunkLayer& layer, int iRow) {
                    bebra::objects::chunkRow& row = layer.at(iRow);
                    
                    // Functor: Render single block of chunk
                    static std::function blockFunctor = [&](bebra::objects::chunkRow& row, int iBlock) {
                        const bebra::objects::Object* block = row.at(iBlock);
                        
                        // Check for visible
                        if (!block->texture.arraySize) return;

                        // Block space transformation
                        glm::mat4 model = glm::mat4(1.0f);
                        //model = glm::translate(model, { iBlock + 16*x, iLayer, iRow + 16*y });
                        model = glm::translate(model, { iBlock, iLayer, iRow });
                        if (block->rotate != 0.0)
                            model = glm::rotate(model, glm::radians(block->rotate), { 0.0, 1.0, 0.0 });
                        blockShaderSet.model(model);

                        // Pick right buffers for current object
                        switch(block->id) {
                            case bebra::objects::eblock: { glBindVertexArray(blockVAO); break; }
                            case bebra::objects::eplant: { glBindVertexArray(plantVAO); break; }
                            case bebra::objects::efluid: { glBindVertexArray(fluidVAO); break; }
                            default: { glBindVertexArray(blockVAO); break; }
                        }

                        // TODO: texture sets manager
                        GLint textureSlot = GL_TEXTURE31;
                        GLint textureSlotIndex = 31; // < Max texture slots
                        glActiveTexture(textureSlot + textureSlotIndex);
                        glBindTexture(GL_TEXTURE_2D_ARRAY, block->texture.textureArray);
                        glUniform1i(glGetUniformLocation(blockShader.program, "textureArray"), (textureSlot-GL_TEXTURE0)+textureSlotIndex);
                        if (block->id == bebra::objects::eplant) {
                            glDisable(GL_CULL_FACE);
                            glDrawArrays(GL_TRIANGLES, 0, 12);
                            glEnable(GL_CULL_FACE);
                        } else {
                            //glDrawArrays(GL_TRIANGLES, 0, 36);
                        }
                        chunkCallsCounter++;

                        // Mesh test:
                        testmesh.render();

                    };
                    // TODO: inverse for depth-test optimization
                    //-Y[->>Camera   ]+Y
                    for (int iBlock = 0; iBlock < std::min(std::max(0, static_cast<int>(std::round(cameraBlocksPos[0]))), 16); iBlock++)
                        blockFunctor(row, iBlock);
                    //-Y[   Camera<<-]+Y
                    for (int iBlock = 15; iBlock >= std::max(0, static_cast<int>(std::round(cameraBlocksPos[0]))); iBlock--)
                        blockFunctor(row, iBlock);
                };

                //-X[->>Camera   ]+X
                for (int iRow = 0; iRow < std::min(std::max(0, static_cast<int>(std::round(cameraBlocksPos[2]))), 16); iRow++)
                    rowFunctor(layer, iRow);
                //-X[   Camera<<-]+X
                for (int iRow = 15; iRow >= std::max(0, static_cast<int>(std::round(cameraBlocksPos[2]))); iRow--)
                    rowFunctor(layer, iRow);
            };
            //DN[->>Camera   ]UP
            for (int iLayer = 0; iLayer < std::min(std::max(0, static_cast<int>(std::round(cameraBlocksPos[1]))), chunkSize) ; iLayer++)
                layerFunctor(chunk, iLayer);
            //DN[   Camera<<-]UP
            for (int iLayer = chunkSize-1; iLayer >= std::min(std::max(0, static_cast<int>(std::round(cameraBlocksPos[1]))), chunkSize); iLayer--)
                layerFunctor(chunk, iLayer);
        }

        // Render from G-Buffer
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        screen.gbuffer->unbind();
        screen.render(!window.debug.nohud);

        // Calculate frametime & FPS
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

        bebra::utils::glHandleError(glGetError());
        SDL_GL_SwapWindow(window.itself);
    }

    SDL_Quit();
    return 0;
}
