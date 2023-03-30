#include "engine/camera.h"
#include "engine/core.h"
#include "engine/graphics/shaders.h"
#include "engine/graphics/framebuffer.h"
#include "engine/objects/objects.h"
#include "engine/utils/font.h"
#include "engine/utils/glerrors.h"

#include "game/demoChunkGen.h"
#include "game/control.h"
#include "game/shaders.h"
#include "game/skybox.h"

#include <iostream>
#include <vector>
#include <functional>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* argv[]) {
    // Init & Creating window
    SDL_DisplayMode display = bebra::init(bebra::GApi::OpenGL);
    bebra::Window window {"BebraCraft", display, SDL_WINDOW_OPENGL};
    bebra::contextCreate(window);

    // Creating camera:
    bebra::Camera camera { glm::vec3(-2.0f, 8.0f, 6.0f) };
    camera.speed = 0.05;

    // Create screen object and G-Buffer
    bebra::graphics::ShaderProgram screenShader {"shaders/screen.vert", "shaders/screen.frag"}; // GL::ERROR::1281 -> INVALID_VALUE
    bebra::graphics::ScreenObject screen {
        (uint)window.mode.w, (uint)window.mode.h, screenShader
    };

    // Objects // TODO: texture manager
        // Creating skybox
    craft::skybox skybox { bebra::graphics::ShaderProgram {"shaders/skybox.vert", "shaders/skybox.frag"} }; // GL::ERROR::1281 -> INVALID_VALUE
        // Loading shaders
    bebra::graphics::ShaderProgram blockShader {"shaders/block.vert", "shaders/block.frag"}; // GL::ERROR::1281 -> INVALID_VALUE
    craft::BlockShaderApi blockShaderSet {blockShader};
        // Buffers
    GLuint VBO, plantVAO, fluidVAO, blockVAO, EBO;
    bebra::objects::Plant::loadObject(VBO, plantVAO, EBO);
    bebra::objects::Block::loadObject(VBO, blockVAO, EBO);
    bebra::objects::Fluid::loadObject(VBO, fluidVAO, EBO);

    // Load chunks
    auto chunk = craft::genChunk();
    int chunkSize = static_cast<int>(chunk.size());

    // Runtime vars
    std::list<SDL_Keycode> keyPressed;
    float worldTime = 0.0, rawTime = 0.0;

    // Load font
    bebra::graphics::ShaderProgram fontShader {"shaders/font.vert", "shaders/font.frag"};
    bebra::utils::Font text {"./fonts/Monocraft.ttf", fontShader, 18};

    while (window.isRunning) { // Render cycle
        // Calculate shadertime
        //worldTime += 0.001;
        rawTime = 0.5 + (glm::cos(worldTime) / 2.0);

        // Handling input and window events
        bool isModeChanged = false;
        handleInput(keyPressed, camera, window, isModeChanged);
        if (isModeChanged) {
            screen.updateMode(window.mode.w, window.mode.h);
            glViewport(0, 0, window.mode.w, window.mode.h);
        }

        // Position calculation // Todo: camera class
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
        skybox.render(viewIdenpedent, projection, rawTime);
        //for (int x = 0; x < 16; x++) for (int y = 0; y < 16; y++) // TODO: rewrite this shit
        { // Chunks render
            blockShader.use();
            blockShaderSet.model(model);
            blockShaderSet.view(view);
            blockShaderSet.projection(projection);
            blockShaderSet.worldTime(rawTime);

            static auto cameraBlocksPos = glm::value_ptr(camera.pos);

            /// Render chunk
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

                        // TODO: texture sets manager, non-cringe alpha blending, instance manager, multithreading
                        GLint textureSlot = GL_TEXTURE31;
                        GLint textureSlotIndex = 31; // < Max texture slots
                        glActiveTexture(textureSlot + textureSlotIndex);
                        glBindTexture(GL_TEXTURE_2D_ARRAY, block->texture.textureArray);
                        glUniform1i(glGetUniformLocation(blockShader.program, "textureArray"), (textureSlot-GL_TEXTURE0)+textureSlotIndex);
                        if (block->id == bebra::objects::eplant) {
                            glDisable(GL_CULL_FACE);
                            glDrawArrays(GL_TRIANGLES, 0, 12);
                            glEnable(GL_CULL_FACE);
                        } else
                            glDrawArrays(GL_TRIANGLES, 0, 36);
                        
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
        screen.gbuffer->unbind();
        screen.render();

        // Render HUD
        text.render("BebraCraft pre-alpha-1", projectionFont, 10.0, float(window.mode.h) - float(std::max(text.width, text.height)) - 5.0);

        bebra::utils::glHandleError(glGetError());
        SDL_GL_SwapWindow(window.itself);
    }

    return 0;
}
