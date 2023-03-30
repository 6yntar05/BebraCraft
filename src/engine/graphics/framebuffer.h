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

        uint width;
        uint height;

      private:
        GLuint depth;   // RBO

		void init(const uint width, const uint height);
		void deinit();

      public:
        GBuffer(const uint width, const uint height);
        ~GBuffer();
        void updateMode(uint width, uint height);

		void bind();
        void unbind();
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
        
        void render(bool renderHud = true) const;
        void updateMode(uint width, uint height) {
            gbuffer->updateMode(width, height);
        }

        ScreenObject(const uint width, const uint height, const graphics::ShaderProgram shader);
        ~ScreenObject();
    };

}
}