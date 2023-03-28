#include "engine/graphics/textures.h"
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>

class Texture {
  private:
    SDL_Surface* const surface;
    unsigned char** pixels;
    const bool isFlipped;
    unsigned char* buffer; bool isBufferAllocated = false;  // For texture flipping

  public:
    uint width;
    uint height;
    int mode;

    unsigned char* getData(const bool flipped = false) {
        if (flipped ^ isFlipped) {
            uint channels = ((mode==GL_RGBA)?4:3);  // Color channels

            if (isBufferAllocated)  // Allocation check
                delete[] buffer;
            this->buffer = new unsigned char[width*height*channels];
            this->isBufferAllocated = true;
            
            for (uint h = 0; h < height; h++)
                for (uint w = 0; w < width; w++)
                    for (uint c = 0; c < channels; c++)
                        buffer [        // to:
                            h*(width*channels) +        // Vertical
                            w*(channels) +              // Horisontal
                            c                           // Channel
                        ] = (*pixels) [ // from:
                            (height-h-1)*(width*channels) + // Vertical (flipped)
                            w*(channels) +              // Horisontal
                            c                           // Channel
                        ];

            return buffer;
        }
        return *pixels;
    }

    Texture(const std::string path, const bool flipped = false)
    : surface(IMG_Load(path.c_str())), isFlipped(flipped) {
        this->pixels = new unsigned char* (static_cast<unsigned char*>(surface->pixels));
        this->width = surface->w;
        this->height = surface->h;
        if (surface->format->BytesPerPixel == 4)
            mode = GL_RGBA;
        else
            mode = GL_RGB;
    }

    ~Texture() {
        delete this->pixels;
        if (isBufferAllocated)
            delete[] buffer;
        SDL_FreeSurface(surface);
    }
};

namespace bebra::graphics {

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

void loadTextureArray(GLuint* const texture, const std::vector<std::string> pathes) { // ISSUES (OPENGLES)
    //loadTexture(texture, pathes.at(0));
    //return;
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
    Texture image {pathes.at(0).c_str()};
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 5, GL_RGBA16, image.width, image.height, pathes.size());
        // Create array
    for (uint i = 0; i < pathes.size(); i++) {
        Texture image {pathes.at(i).c_str(), true};
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, image.width, image.height, 1, image.mode, GL_UNSIGNED_BYTE, image.getData());
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
        Texture image {pathes.at(i)};
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