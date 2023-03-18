#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "engine/graphics/textures.h"
#include "engine/graphics/shaders.h"

namespace bebra {
namespace graphics {

    class gbuffer {
      public:
        GLuint descriptor;

        // Buffers
        GLuint color;
        GLuint normal;
        GLuint position;

      private:
        GLuint depth;   // RBO

      public:
        void bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, this->descriptor);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.356, 0.6, 0.98, 1.0f);
        }

        void unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        gbuffer(unsigned int width, unsigned int height) {
            glGenFramebuffers(1, &this->descriptor);
            glBindFramebuffer(GL_FRAMEBUFFER, this->descriptor);

            color = bebra::graphics::createTexture(GL_RGBA16F, width, height);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);
            normal = bebra::graphics::createTexture(GL_RGBA, width, height);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal, 0);
            position = bebra::graphics::createTexture(GL_RGBA, width, height);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, position, 0);

            GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
            glDrawBuffers(3, DrawBuffers);

            // Creating renderbuffer for depth
            glGenRenderbuffers(1, &depth);
            glBindRenderbuffer(GL_RENDERBUFFER, depth);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth);

            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (status != GL_FRAMEBUFFER_COMPLETE)
                std::cerr << "Error creating FBO\n";
        }

        ~gbuffer() {
            GLuint toDelete[] = {color, normal, position};
            glDeleteFramebuffers(3, toDelete);
        }
    };

    class screenObject {
      private:
        graphics::shaderProgram shader;

        GLuint VBO;
        GLuint VAO;

      public:
        static constexpr float verticies[] = { //Coords(2), TexturesPos(2)
           -1.0f,  1.0f,   0.0f, 1.0f,
           -1.0f, -1.0f,   0.0f, 0.0f,
            1.0f, -1.0f,   1.0f, 0.0f,

           -1.0f,  1.0f,   0.0f, 1.0f,
            1.0f, -1.0f,   1.0f, 0.0f,
            1.0f,  1.0f,   1.0f, 1.0f
        };

        // Service
        bebra::graphics::gbuffer* gbuffer;
        
        void render() {
            this->shader.use();

            glBindVertexArray(this->VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->gbuffer->color);
            glUniform1i(glGetUniformLocation(this->shader.program, "colorbuffer"), 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this->gbuffer->normal);
            glUniform1i(glGetUniformLocation(this->shader.program, "normalbuffer"), 1);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, this->gbuffer->position);
            glUniform1i(glGetUniformLocation(this->shader.program, "positionbuffer"), 2);

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_BLEND);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glEnable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
        }

        screenObject(unsigned int width, unsigned int height, graphics::shaderProgram shader)
            : shader(shader)
        {
            this->gbuffer = new bebra::graphics::gbuffer {width, height};

            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &this->VBO);
            glBindVertexArray(this->VAO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), &verticies, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glBindVertexArray(0);
        }

        ~screenObject() {
            delete this->gbuffer;

            glDeleteVertexArrays(1, &this->VAO);
            glDeleteBuffers(1, &this->VBO);
        }
    };

}
}