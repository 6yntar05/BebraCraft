#include <iostream>
#include <vector>
#include <functional>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/core.h"
#include "engine/graphics/cubemaps.h"
#include "engine/graphics/shaders.h"
#include "engine/objects/base.h"

#include "game/demoChunkGen.h"
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
    bebra::contextCreate(window, windowWidth, windowHeight, false, true);
    bebra::graphics::Shader blockShader("shaders/block.vs", "shaders/block.frag");
    bebra::graphics::Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.frag");
    bebra::graphics::Shader faceShader("shaders/face.vs", "shaders/face.frag");

    // Create skyBox (Keep it higher then other texture loadings, otherwise you get a flipped textures)
    GLuint skyVBO, skyVAO;
    bebra::graphics::loadObject(skyVBO, skyVAO);
    auto skyBoxTexture = bebra::graphics::loadCubemap(
        {"textures/skybox/ft.png",
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
    auto chunk = bebra::utils::genChunk();
    int chunkSize = static_cast<int>(chunk.size());

    // Create renderbuffer
    float quadVertices[] = { // атрибуты вершин в нормализованных координатах устройства для прямоугольника, который имеет размеры экрана 
         // координаты // текстурные координаты
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	// VAO прямоугольника
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    // Конфигурация фреймбуфера
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // Создание текстуры для прикрепляемого объекта цвета
    GLuint textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    //glBindTexture(GL_TEXTURE_2D, 0);
    // Создание объекта рендербуфера дла прикрепляемых объектов глубины и трафарета (сэмплирование мы не будет здесь проводить)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight); // использование одного объекта рендербуфера для буферов глубины и трафарета
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // теперь прикрепляем это дело
	// Теперь, когда мы создали фреймбуфер и прикрепили все необходимые объекты, проверяем завершение формирования фреймбуфера
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Runtime vars
    std::list<SDL_Keycode> keyPressed;
    bool window_running = true;
    static float speed = 0.05f;
    
    while (window_running) { // Render cycle
        handleInput(keyPressed, speed, yaw, pitch, window_running);

        // Position calculation (This block fuckt CPU)
        glm::mat4 model          = glm::rotate(glm::mat4(1.0f), 1.0f * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 view           = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 viewIdenpedent = glm::mat4(glm::mat3(view));
        glm::mat4 projection     = glm::perspective(glm::radians(fov), window_aspect_ratio, 0.1f, 300.0f); // 300 - render distance
        glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        cameraFront = glm::normalize(direction);

		// Clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(15.0/255.0, 15.0/255.0, 15.0/255.0, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        
        { // SkyBox render
            glDepthMask(GL_FALSE);
            skyboxShader.Use();
            int viewLocIdenpedent = glGetUniformLocation(skyboxShader.Program, "view");
            glUniformMatrix4fv(viewLocIdenpedent, 1, GL_FALSE, glm::value_ptr(viewIdenpedent));
            int projectionLocIdenpedent = glGetUniformLocation(skyboxShader.Program, "projection");
            glUniformMatrix4fv(projectionLocIdenpedent, 1, GL_FALSE, glm::value_ptr(projection));
            glBindVertexArray(skyVAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthMask(GL_TRUE);
        }

        { // Chunks render
            blockShader.Use();
            int modelLoc = glGetUniformLocation(blockShader.Program, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            int viewLoc = glGetUniformLocation(blockShader.Program, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projectionLoc = glGetUniformLocation(blockShader.Program, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
                        bebra::objects::object* block = row.at(iBlock);
                        
                        if (!block->texture.textures.size())
                            return;

                        // Block space transformation
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, {iBlock,iLayer,iRow});
                        if (block->rotate != 0.0)
                            model = glm::rotate(model, glm::radians(block->rotate), {0.0, 1.0, 0.0});

                        switch(block->id) {
                            case bebra::objects::eblock:
                                glBindVertexArray(blockVAO);
                                break;

                            case bebra::objects::eplant:
                                glBindVertexArray(plantVAO);
                                break;

                            case bebra::objects::efluid:
                                glBindVertexArray(fluidVAO);
                                break;

                            default:
                                glBindVertexArray(blockVAO);
                                break;
                        }

                        int modelLoc = glGetUniformLocation(blockShader.Program, "model");
                        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                        if ((block->id == bebra::objects::eglass) || (block->id == bebra::objects::efluid)) { // Pass textures to fragment shaders
                            glActiveTexture(GL_TEXTURE0);
                            if ((iRow == 0) || ((iRow > 0) && (chunk.at(iLayer).at(iRow-1).at(iBlock)->id != block->id)))
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(0));
                            else
                                glBindTexture(GL_TEXTURE_2D, alphaTexture);
                            glUniform1i(glGetUniformLocation(blockShader.Program, "front"), 0);

                            glActiveTexture(GL_TEXTURE1);
                            if ((chunk.at(iLayer).at(iRow+1).at(iBlock)->id != block->id))
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(1));
                            else
                                glBindTexture(GL_TEXTURE_2D, alphaTexture);
                            glUniform1i(glGetUniformLocation(blockShader.Program, "back"), 1);

                            glActiveTexture(GL_TEXTURE2);
                            if ((iBlock == 15) || ( (iBlock < 15) && (row[++iBlock]->id!=block->id) ))
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(2));
                            else
                                glBindTexture(GL_TEXTURE_2D, alphaTexture);
                            glUniform1i(glGetUniformLocation(blockShader.Program, "left"), 2);

                            glActiveTexture(GL_TEXTURE3);
                            if ((iBlock <= 1) || ((iBlock > 0) && (row[iBlock-2]->id!=block->id)))
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(3));
                            else
                                glBindTexture(GL_TEXTURE_2D, alphaTexture);
                            glUniform1i(glGetUniformLocation(blockShader.Program, "right"), 3);

                            glActiveTexture(GL_TEXTURE4);
                            if ((iLayer == (static_cast<int>(chunk.size()))) || ((iLayer < static_cast<int>(chunk.size()-1)) && (chunk.at(iLayer+1).at(iRow).at(iBlock-1)->id != block->id)) )
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(4));
                            else
                                glBindTexture(GL_TEXTURE_2D, alphaTexture);
                            glUniform1i(glGetUniformLocation(blockShader.Program, "up"), 4);

                            glActiveTexture(GL_TEXTURE5);
                            if ((iLayer == 0) || ((iLayer > 0) && (chunk.at(iLayer-1).at(iRow).at(iBlock-1)->id != block->id)))
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(5));
                            else
                                glBindTexture(GL_TEXTURE_2D, alphaTexture);
                            glUniform1i(glGetUniformLocation(blockShader.Program, "down"), 5);

                            glDepthMask(GL_FALSE);
                            glDrawArrays(GL_TRIANGLES, 0, 36);
                            glDepthMask(GL_TRUE);              
                            
                        } else {
                            glActiveTexture(GL_TEXTURE0);
                            glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(0));
                            glUniform1i(glGetUniformLocation(blockShader.Program, "front"), 0);

                            glActiveTexture(GL_TEXTURE1);
                            glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(1));
                            glUniform1i(glGetUniformLocation(blockShader.Program, "back"), 1);

                            if (block->id != bebra::objects::eplant) {
                                glActiveTexture(GL_TEXTURE2);
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(2));
                                glUniform1i(glGetUniformLocation(blockShader.Program, "left"), 2);

                                glActiveTexture(GL_TEXTURE3);
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(3));
                                glUniform1i(glGetUniformLocation(blockShader.Program, "right"), 3);
                            
                                glActiveTexture(GL_TEXTURE4);
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(4));
                                glUniform1i(glGetUniformLocation(blockShader.Program, "up"), 4);

                                glActiveTexture(GL_TEXTURE5);
                                glBindTexture(GL_TEXTURE_2D, block->texture.textures.at(5));
                                glUniform1i(glGetUniformLocation(blockShader.Program, "down"), 5);

                                glDrawArrays(GL_TRIANGLES, 0, 36);
                            } else {
                                glDisable(GL_CULL_FACE);
                                glDepthMask(GL_FALSE);
                                glDrawArrays(GL_TRIANGLES, 0, 12);
                                glDepthMask(GL_TRUE);
                                glEnable(GL_CULL_FACE);
                            }
                        }
                    };

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

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(15.0/255.0, 15.0/255.0, 15.0/255.0, 1.0f);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        faceShader.Use();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glUniform1i(glGetUniformLocation(faceShader.Program, "screenTexture"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_DEPTH_TEST);

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    return 0;
}
