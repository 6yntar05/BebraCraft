#include "engine/graphics/textures.h"

#include <stb/stb_image.h>

namespace bebra {
namespace graphics {

    GLuint createTexture(const GLint internalformat, const uint width, const uint height, const GLenum format, const GLenum type) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, GL_RGBA, type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        return texture;
    }

    void loadTexture(GLuint* const texture, const std::string path) {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
        // Set our texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Smoth MIN scaling with mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Detailed MAG scaling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 14);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL , 10);

        // Load, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *image = stbi_load(path.c_str(), &width, &height, &nrChannels, 0); 

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(image);
    }

    void loadTextureArray(GLuint* const texture, const std::vector<std::string> pathes) {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D_ARRAY, *texture);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY, 16);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 4);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // Smoth MIN scaling with mipmap
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Detailed MAG scaling

        int width, height, channels;
        stbi_load(pathes.at(0).c_str(), &width, &height, &channels, 0);
        //glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA, width, height, pathes.size());
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, pathes.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        for (uint i = 0; i < pathes.size(); i++) {
            unsigned char* data = stbi_load(pathes.at(i).c_str(), &width, &height, &channels, 0);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    GLuint loadTextureArray(const std::vector<std::string> pathes) {
        GLuint texture;
        loadTextureArray(&texture, pathes);
        return texture;
    }

}
}