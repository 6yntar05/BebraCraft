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

        unsigned int width;
        unsigned int height;

      private:
        GLuint depth;   // RBO

		void init(const unsigned int width, const unsigned int height);
		void deinit();

      public:
        GBuffer(const unsigned int width, const unsigned int height);
        ~GBuffer();
        void updateMode(unsigned int width, unsigned int height);

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
        
        void clear() const;
        void render(bool renderHud = true) const;
        void updateMode(unsigned int width, unsigned int height);

        ScreenObject(const unsigned int width, const unsigned int height, const graphics::ShaderProgram shader);
        ~ScreenObject();
    };

}
}