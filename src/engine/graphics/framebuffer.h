#pragma once

#include <string>
#include <vector>
#include <iostream>

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
        void bind();
        void unbind();

        gbuffer(const uint width, const uint height);
        ~gbuffer();
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
        
        void render() const;

        screenObject(const uint width, const uint height, const graphics::shaderProgram shader);
        ~screenObject();
    };

}
}