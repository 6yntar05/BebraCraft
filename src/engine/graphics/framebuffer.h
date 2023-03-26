#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "engine/graphics/textures.h"
#include "engine/graphics/shaders.h"

namespace bebra {
namespace graphics {

    class GBuffer {
      public:
        GLuint descriptor;

        // Buffers
        GLuint color;
        GLuint normal;
        GLuint position;

      private:
        GLuint depth;   // RBO

      public:
        void bind();
        void unbind();

        GBuffer(const uint width, const uint height);
        ~GBuffer();
    };

    class ScreenObject {
      private:
        graphics::ShaderProgram shader;

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
        bebra::graphics::GBuffer* gbuffer;
        
        void render() const;

        ScreenObject(const uint width, const uint height, const graphics::ShaderProgram shader);
        ~ScreenObject();
    };

}
}