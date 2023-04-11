#include "engine/graphics/textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace bebra::graphics {

unsigned char* Texture::getData() {
    return image;
}

Texture::Texture(const std::string path, const bool flip) {
    if (flip)
        stbi_set_flip_vertically_on_load(true);
    // Mode
    int channels;
    this->image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (channels >= 4)
        mode = GL_RGBA;
    else
        mode = GL_RGB;
        // GL_RED
}

Texture::~Texture() {
    stbi_image_free(image);
}

GLuint createTexture(const GLint internalformat, const uint width, const uint height, const GLenum format, const GLenum type) {
    GLuint texture;
    // Bind
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Creating texture
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, GL_RGBA, type, NULL);
    // Unbind
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

GLuint createMultisampleTexture(const GLint internalformat, const uint width, const uint height, const GLenum format, const GLenum type) {
    GLuint texture;
    // Bind
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
    // Texture params
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Creating texture
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, internalformat, width, height, GL_TRUE);
    // Unbind
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    return texture;
}

void loadTexture(GLuint* const texture, const std::string path) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // Texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // Smoth MIN scaling with mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Detailed MAG scaling
    // Reading texture & creating mipmaps
    Texture image {path.c_str(), true};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
    glGenerateMipmap(GL_TEXTURE_2D);
    // Unding
    glBindTexture(GL_TEXTURE_2D, 0);
}

void loadTexture(GLuint* const texture, const std::vector<unsigned char> data, uint width, uint height, uint channels) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // Texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // Smoth MIN scaling with mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Detailed MAG scaling
    // Reading texture & creating mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, (channels==4)?GL_RGBA:GL_RGB, width, height, 0, (channels==4)?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    // Unding
    glBindTexture(GL_TEXTURE_2D, 0);

}

void loadTextureArray(GLuint* const texture, const std::vector<std::string> pathes) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, *texture);
    // Texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY, 16);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 4);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // Smoth MIN scaling with mipmap
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Detailed MAG scaling
    // Reading texture & creating mipmaps
    Texture image {pathes.at(0).c_str(), true};
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.width, image.height, pathes.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    for (uint i = 0; i < pathes.size(); i++) {
        Texture image {pathes.at(i).c_str(), true};
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, image.width, image.height, 1, image.mode, GL_UNSIGNED_BYTE, image.getData());
    }
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    // Unbinding
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void loadTextureArray(GLuint* const texture, const std::vector<std::vector<unsigned char>> data, uint width, uint height, uint channels) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, *texture);
    // Texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY, 16);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 4);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // Smoth MIN scaling with mipmap
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Detailed MAG scaling
    // Reading texture & creating mipmaps
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 5, GL_RGBA, width, height, data.size());
        // Create array
    for (uint i = 0; i < data.size(); i++) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, (channels==4)?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data.at(i).data());
    }
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    // Unding
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

GLuint loadTextureArray(const std::vector<std::string> pathes) {
    // Wrapper
    GLuint texture;
    loadTextureArray(&texture, pathes);
    return texture;
}

void loadCubemapTexture(GLuint* const texture, std::vector<std::string> pathes) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *texture);

    for (unsigned int i = 0; i < pathes.size(); i++) {
        Texture image {pathes.at(i), false};
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            image.mode, image.width, image.height,
            0, GL_RGB, GL_UNSIGNED_BYTE, image.getData()
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint loadCubemapTexture(const std::vector<std::string> pathes) {
    // Wrapper
    GLuint texture;
    loadCubemapTexture(&texture, pathes);
    return texture;
}

} // namespace bebra::graphics