#include "engine/core.h"
#include "engine/graphics/shaders.h"
#include "engine/graphics/cubemaps.h"
#include "engine/graphics/framebuffer.h"
#include "engine/graphics/textures.h"
#include "engine/objects/objects.h"

#include "game/demoChunkGen.h"
#include "game/control.h"
#include "game/shaders.h"

#include <iostream>
#include <vector>
#include <functional>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
glm::vec3 cameraPos   = glm::vec3(-2.0f, 8.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

int main() {
    unsigned int windowWidth = 1920;
    unsigned int windowHeight = 1080;
    float window_aspect_ratio = float(windowWidth) / float(windowHeight);
    // Init
    bebra::init(bebra::gapi::OpenGL);
    auto window = bebra::window("BebraCraft", windowWidth, windowHeight, SDL_WINDOW_OPENGL);
    bebra::contextCreate(window, windowWidth, windowHeight);

    // Loading shaders
    bebra::graphics::shaderProgram blockShader  {"shaders/block.vert", "shaders/block.frag"};
    bebra::graphics::shaderProgram skyboxShader {"shaders/skybox.vert", "shaders/skybox.frag"};
    craft::blockShaderApi blockShaderSet    {blockShader};
    craft::blockShaderApi skyboxShaderSet   {skyboxShader};

    // Create screen object and G-Buffer
    bebra::graphics::screenObject screen {
        windowWidth, windowHeight, 
        bebra::graphics::shaderProgram {"shaders/screen.vert", "shaders/screen.frag"}
    };

    // Create skyBox (Keep it higher then other texture loadings, otherwise you get a flipped textures)
    GLuint skyVBO, skyVAO;
    bebra::graphics::loadObject(skyVBO, skyVAO);
    auto skyBoxTexture = bebra::graphics::loadCubemap({
        "textures/skybox/ft.png",
        "textures/skybox/bk.png",
        "textures/skybox/up.png",
        "textures/skybox/dn.png",
        "textures/skybox/lf.png",
        "textures/skybox/rt.png"});

    // Create objects
    GLuint VBO, plantVAO, fluidVAO, blockVAO, EBO;  // VBO & EBO is the same for every object
    bebra::objects::plant::loadObject(VBO, plantVAO, EBO);
    bebra::objects::block::loadObject(VBO, blockVAO, EBO);
    bebra::objects::fluid::loadObject(VBO, fluidVAO, EBO);
    GLuint alphaTexture;    // For culling of extra edges
    bebra::graphics::loadTexture(&alphaTexture, "textures/blocks/alpha.png");

    // Load chunks
    auto chunk = craft::genChunk();
    int chunkSize = static_cast<int>(chunk.size());

    // Runtime vars
        // SDL & Window
    std::list<SDL_Keycode> keyPressed;
    bool window_running = true;
        // Time
    float worldTime = 0;
    float rawTime   = 0;
        // Camera
    float yaw    = 0.0f;
    float pitch  = 0.0f;
    float fov    = 90.0f;
    float speed  = 0.05f;
    
    while (window_running) { // Render cycle
        worldTime += 0.001;
        rawTime = 0.5 + (glm::cos(worldTime) / 2.0);
        handleInput(keyPressed, speed, yaw, pitch, window_running);

        // Position calculation
        glm::mat4 model          = glm::rotate(glm::mat4(1.0f), 1.0f * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 view           = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 viewIdenpedent = glm::mat4(glm::mat3(view));
        glm::mat4 projection     = glm::perspective(glm::radians(fov), window_aspect_ratio, 0.1f, 300.0f); // 300 - render distance
        glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        // Offscreen rendering in G-Buffer
		screen.gbuffer->bind();
        
        { // SkyBox render
            glDepthMask(GL_FALSE);
            skyboxShader.use();
            skyboxShaderSet.view(viewIdenpedent);
            skyboxShaderSet.projection(projection);
            skyboxShaderSet.worldTime(rawTime);
            glBindVertexArray(skyVAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);
        }

        //for (int x = 0; x < 16; x++) for (int y = 0; y < 16; y++) // TODO: fix CPU utilization
        { // Chunks render
            blockShader.use();
            blockShaderSet.model(model);
            blockShaderSet.view(view);
            blockShaderSet.projection(projection);
            blockShaderSet.worldTime(rawTime);

            static auto cameraBlocksPos = glm::value_ptr(cameraPos);

            /// Render chunk
            // Functor: Render single layer of chunk
            static std::function layerFunctor = [&](bebra::objects::chunk& chunk, int iLayer) {
                bebra::objects::chunkLayer& layer = chunk.at(iLayer);

                // Functor: Render single row of chunk 
                static std::function rowFunctor = [&](bebra::objects::chunkLayer& layer, int iRow) {
                    bebra::objects::chunkRow& row = layer.at(iRow);
                    
                    // Functor: Render single block of chunk
                    static std::function blockFunctor = [&](bebra::objects::chunkRow& row, int iBlock) {
                        const bebra::objects::object* block = row.at(iBlock);
                        
                        // Check for visible
                        if (!block->texture.arraySize) return;

                        // Block space transformation
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, { iBlock, iLayer, iRow });
                        //model = glm::translate(model, { iBlock + 16*x, iLayer, iRow + 16*y });
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
                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D_ARRAY, block->texture.textureArray);
                        glUniform1i(glGetUniformLocation(blockShader.program, "textureArray"), 0);
                        if (block->id == bebra::objects::eplant)
                            glDrawArrays(GL_TRIANGLES, 0, 12);
                        else
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

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
