#include <string>
#include <vector>
#include <iostream>

#include "engine/graphics/framebuffer.h"

namespace bebra {
namespace graphics {

// class GBuffer
    void GBuffer::init(const unsigned int width, const unsigned int height) {
        this->width = width;
        this->height = height;

        glGenFramebuffers(1, &this->descriptor);
        glBindFramebuffer(GL_FRAMEBUFFER, this->descriptor);

        color = bebra::graphics::createTexture(GL_RGBA16F, width, height); // TODO: Multisample
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
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "Error creating FBO\n";
    }

    void GBuffer::deinit() {
        glGenFramebuffers(1, &this->descriptor);
        glBindFramebuffer(GL_FRAMEBUFFER, this->descriptor);
    }

    void GBuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, this->descriptor);
    }

    void GBuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GBuffer::GBuffer(const unsigned int width, const unsigned int height) { this->init(width, height); }
    GBuffer::~GBuffer() { this->deinit(); }

    void GBuffer::updateMode(unsigned int width, unsigned int height) {
        this->deinit();
        this->init(width, height);
    }

// class ScreenObject
    void ScreenObject::clear() const {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void ScreenObject::render(bool renderHud) const {
        // Shader and VAO
        this->shader.use();
        glUniform1i(glGetUniformLocation(this->shader.program, "renderHUD"), renderHud);
        glUniform1i(glGetUniformLocation(this->shader.program, "width"), this->gbuffer->width);
        glUniform1i(glGetUniformLocation(this->shader.program, "height"), this->gbuffer->height);
        glBindVertexArray(this->VAO);

        // Textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->gbuffer->color);
        // glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_RGBA, 1920, 1080, GL_TRUE); // TODO
        glUniform1i(glGetUniformLocation(this->shader.program, "colorbuffer"), 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->gbuffer->normal);
        glUniform1i(glGetUniformLocation(this->shader.program, "normalbuffer"), 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->gbuffer->position);
        glUniform1i(glGetUniformLocation(this->shader.program, "positionbuffer"), 2);

        // Render
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    }

    void ScreenObject::updateMode(unsigned int width, unsigned int height) {
        gbuffer->updateMode(width, height);
        glViewport(0, 0, width, height);
    }

    ScreenObject::ScreenObject(const unsigned int width, const unsigned int height, const graphics::ShaderProgram shader)
        : shader(shader)
    {
        this->gbuffer = new bebra::graphics::GBuffer {width, height};

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

        updateMode(width, height);
    }

    ScreenObject::~ScreenObject() {
        delete this->gbuffer;

        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }

}
}