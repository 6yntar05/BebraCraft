#include "engine/graphics/textures.h"
#include <GL/gl.h>
#include <cstddef>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace bebra::graphics {

// Texture class:
void Texture::findGLMode() {
    if (this->channels >= 4)
        this->mode = GL_RGBA;
    else this->mode = GL_RGB;
    // GL_RED
}

void Texture::append(Texture another) { // Append to UV texture
    assert(height == another.height);
    assert(channels == another.channels);

    std::vector<unsigned char> newimage;
    size_t imageLineSize    = width * channels;
    size_t anotherLineSize  = another.width * another.channels;

    newimage.reserve(image.size() + another.image.size());
    for (int y = 0; y < this->height; y++) { // each UV line
        // Copy old texture line
        newimage.insert(
            newimage.end(),
            image.begin() + (imageLineSize * y),
            image.begin() + (imageLineSize *(y+1))
        );
        // Copy new texture line
        newimage.insert(
            newimage.end(),
            another.image.begin() + (anotherLineSize * y),
            another.image.begin() + (anotherLineSize *(y+1))
        );
    }

    this->image    = std::move(newimage);
    this->width   += another.width;
    this->uvCount += another.uvCount;
}

Texture::Texture(const std::vector<unsigned char> raw, int width, int height, int channels)
: image(raw), width(width), height(height), channels(channels) { findGLMode(); }

Texture::Texture(const std::string path, const bool flip) {
    if (flip)
        stbi_set_flip_vertically_on_load(true);
    unsigned char* stb_image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!stb_image) return;
    this->image.resize(width * height * channels);
    for(size_t i = 0; i < this->image.size(); i++)
        this->image[i] = stb_image[i];
    stbi_image_free(stb_image);

    findGLMode();
}

// Texture loading utils:
static void glSetTextureParams(GLuint textureType = GL_TEXTURE_2D, const TextureParams params = {}) {
    GLuint _param;

    // Wrapping:
    for (GLuint wrapSide : {GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T}) {
        TextureWrapping wrapType = (wrapSide == GL_TEXTURE_WRAP_S) ? params.sideWrapping : params.topWrapping;
        switch(wrapType) {
            case eClamp: _param = GL_CLAMP; break;
            case eClampToEdge: _param = GL_CLAMP_TO_EDGE; break;
            case eRepeat: _param = GL_REPEAT; break;
            case eRepeatMirrored: _param = GL_MIRRORED_REPEAT; break;
        }
        glTexParameteri(textureType, wrapSide, _param);
    }

    // Filtering:
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (GLuint wrapSide : {GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER}) {
        TextureFiltering filteringType = (wrapSide == GL_TEXTURE_MIN_FILTER) ? params.minFilteting : params.magFilteting;
        switch(filteringType) {
            case eNearest: _param = GL_NEAREST; break;
            case eLinear: _param = GL_LINEAR; break;
            case eNearestMipmapLinear: _param = GL_NEAREST_MIPMAP_LINEAR; break;
            case eNearestMipmapNearest: _param = GL_NEAREST_MIPMAP_NEAREST; break;
            case eLinearMipmapLinear: _param = GL_LINEAR_MIPMAP_LINEAR; break;
            case eLinearMipmapNearest: _param = GL_LINEAR_MIPMAP_NEAREST; break;
        }
        glTexParameteri(textureType, wrapSide, _param);
    }
    glTexParameteri(textureType, GL_TEXTURE_MAX_ANISOTROPY, params.anisotropyLevel);
    //glTexParameteri(textureType, GL_TEXTURE_MAX_LEVEL, 4);
    //glTexParameteri(textureType, GL_TEXTURE_BASE_LEVEL, 0);
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

void loadTexture(GLuint* const texture, Texture raw, TextureParams const params) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // Texture params
    glSetTextureParams(GL_TEXTURE_2D, params);
    // Reading texture & creating mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, raw.width, raw.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raw.getData());
    glGenerateMipmap(GL_TEXTURE_2D);
    // Unding
    glBindTexture(GL_TEXTURE_2D, 0);
}

void loadTexture(GLuint* const texture, const std::vector<unsigned char> data, uint width, uint height, uint channels, const TextureParams params) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // Texture params
    glSetTextureParams(GL_TEXTURE_2D, params);
    // Reading texture & creating mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, (channels==4)?GL_RGBA:GL_RGB, width, height, 0, (channels==4)?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    // Unding
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint loadTexture(Texture raw, const TextureParams params) {
    GLuint texture;
    loadTexture(&texture, raw, params);
    return texture;
}

void loadTextureArray(GLuint* const texture, std::vector<Texture> textures, const TextureParams params) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, *texture);
    // Texture params
    glSetTextureParams(GL_TEXTURE_2D_ARRAY, params);
    // Reading texture & creating mipmaps
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, textures.at(0).width, textures.at(0).height, textures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    for (uint i = 0; i < textures.size(); i++) {
        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY, 0, 0, 0, i,
            textures.at(i).width, textures.at(i).height, 1,
            textures.at(i).mode, GL_UNSIGNED_BYTE,
            textures.at(i).getData()
        );
    }
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    // Unbinding
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void loadTextureArray(GLuint* const texture, const std::vector<std::string> pathes, const TextureParams params) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, *texture);
    // Texture params
    glSetTextureParams(GL_TEXTURE_2D_ARRAY, params);
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

void loadTextureArray(GLuint* const texture, const std::vector<std::vector<unsigned char>> data, uint width, uint height, uint channels, const TextureParams params) {
    // Bind
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, *texture);
    // Texture params
    glSetTextureParams(GL_TEXTURE_2D_ARRAY, params);
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

GLuint loadTextureArray(const std::vector<std::string> pathes, const TextureParams params) {
    // Wrapper
    GLuint texture;
    loadTextureArray(&texture, pathes, params);
    return texture;
}

void loadCubemapTexture(GLuint* const texture, std::vector<std::string> pathes, const TextureParams params) {
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

    glSetTextureParams(GL_TEXTURE_CUBE_MAP, params);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint loadCubemapTexture(const std::vector<std::string> pathes, const TextureParams params) {
    // Wrapper
    GLuint texture;
    loadCubemapTexture(&texture, pathes, params);
    return texture;
}

} // namespace bebra::graphics