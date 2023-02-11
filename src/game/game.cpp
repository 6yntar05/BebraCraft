#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include <list>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/core.h"
#include "engine/input.h"
#include "engine/graphics/cubemaps.h"
#include "engine/graphics/shaders.h"
#include "engine/objects/block.h"
#include "engine/objects/chunk.h"
#include "engine/utils/demoChunkGen.h"

#include "game/control.h"

int windowWidth = 1920;
int windowHeight = 1080;
float window_aspect_ratio = float(windowWidth) / float(windowHeight);

float yaw = 0.0f;
float pitch = 0.0f;
float fov = 90.0f;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
glm::vec3 cameraPos   = glm::vec3(-2.0f, 8.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

int main() {
    bebra::init(bebra::gapi::OpenGL);
    auto window = bebra::window("BebraCraft", windowWidth, windowHeight, SDL_WINDOW_OPENGL);
    bebra::contextCreate(window, windowWidth, windowHeight, false);
    bebra::graphics::Shader ourShader("shaders/block.vs", "shaders/block.frag");
    bebra::graphics::Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.frag");

    // Create skyBox (Keep it higher then other texture loadings, otherwise you get a flipped textures)
    GLuint VBOsky, VAOsky;
    bebra::graphics::loadObject(VBOsky, VAOsky);
    auto skyBoxTexture = bebra::graphics::loadCubemap();

    // Create blocks
    GLuint VBO, VAO, EBO;
    bebra::objects::block::loadObject(VBO, VAO, EBO);

    // Load chunks
    auto shittedChunk = bebra::utils::genChunk();

    // Runtime vars
    std::list<SDL_Keycode> keyPressed;
    bool window_running = true;
    static float speed = 0.05f;

    while (window_running) { // Every frame
        handleInput(keyPressed, speed, yaw, pitch, window_running);

        // Position calculation
        glm::mat4
            model = glm::rotate(glm::mat4(1.0f), 1.0f * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp),
            viewIdenpedent = glm::mat4(glm::mat3(view));
        glm::mat4 projection = glm::perspective(glm::radians(fov), window_aspect_ratio, 0.1f, 300.0f); // 300 - render distance
        glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

		// Clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(54.0/255.0, 58.0/255.0, 61.0/255.0, 1.0f);

        { // SkyBox render
            glDepthMask(GL_FALSE);
            skyboxShader.Use();
            int viewLocIdenpedent = glGetUniformLocation(skyboxShader.Program, "view");
            glUniformMatrix4fv(viewLocIdenpedent, 1, GL_FALSE, glm::value_ptr(viewIdenpedent));
            int projectionLocIdenpedent = glGetUniformLocation(skyboxShader.Program, "projection");
            glUniformMatrix4fv(projectionLocIdenpedent, 1, GL_FALSE, glm::value_ptr(projection));
            glBindVertexArray(VAOsky);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);
        }

        { // Blocks render
            ourShader.Use();
            int modelLoc = glGetUniformLocation(ourShader.Program, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            int viewLoc = glGetUniformLocation(ourShader.Program, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projectionLoc = glGetUniformLocation(ourShader.Program, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(VAO);
            
            for (int iLayer = 0; iLayer < static_cast<int>(shittedChunk.size()); iLayer++) {
                bebra::objects::chunkLayer& layer = shittedChunk[iLayer];
                for (int iRow = 0; iRow < 16; iRow++) {
                    bebra::objects::chunkRow& row = layer[iRow];
                    for (int iBlock = 0; iBlock < 16; iBlock++) {
                        bebra::objects::block& block = row[iBlock];
                        if (!block.inited) continue;
                        // IGNORE block.pos!!! CHUNK WILL OVERRIDE BLOCK POSITION!
                        glm::vec3 blockPos = {float(iBlock), float(iLayer), float(iRow)};

                        // Block space transformation
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, blockPos);
                        model = glm::rotate(model, block.rotate, glm::vec3(1.0f, 1.0f, 1.0f));

                        int modelLoc = glGetUniformLocation(ourShader.Program, "model");
                        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                        { // Pass textures to fragment shaders
                            glActiveTexture(GL_TEXTURE0);
                            glBindTexture(GL_TEXTURE_2D, block.textures.front);
                            glUniform1i(glGetUniformLocation(ourShader.Program, "front"), 0);

                            glActiveTexture(GL_TEXTURE1);
                            glBindTexture(GL_TEXTURE_2D, block.textures.back);
                            glUniform1i(glGetUniformLocation(ourShader.Program, "back"), 1);

                            glActiveTexture(GL_TEXTURE2);
                            glBindTexture(GL_TEXTURE_2D, block.textures.up);
                            glUniform1i(glGetUniformLocation(ourShader.Program, "up"), 2);

                            glActiveTexture(GL_TEXTURE3);
                            glBindTexture(GL_TEXTURE_2D, block.textures.down);
                            glUniform1i(glGetUniformLocation(ourShader.Program, "down"), 3);

                            glActiveTexture(GL_TEXTURE4);
                            glBindTexture(GL_TEXTURE_2D, block.textures.left);
                            glUniform1i(glGetUniformLocation(ourShader.Program, "left"), 4);

                            glActiveTexture(GL_TEXTURE5);
                            glBindTexture(GL_TEXTURE_2D, block.textures.right);
                            glUniform1i(glGetUniformLocation(ourShader.Program, "right"), 5);

                            glDrawArrays(GL_TRIANGLES, 0, 36);
                        }
                    }
                }
            }
            glBindVertexArray(0);
        }

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
