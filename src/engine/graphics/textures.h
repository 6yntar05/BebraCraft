#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stb_image.h>

namespace bebra::graphics {

class Texture { // todo: not texture
private:
    unsigned char* image;

public:
    int width;
    int height;
    int mode;

    unsigned char* getData();
    Texture(const std::string path, const bool flip = true);
    ~Texture();
};

GLuint createTexture(
    const GLint internalformat, const uint width, const uint height,
    const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
);
GLuint createMultisampleTexture(
    const GLint internalformat, const uint width, const uint height,
    const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
);

void loadTexture(GLuint* const texture, const std::string path);
void loadTexture(GLuint* const texture, const std::vector<unsigned char> data, uint width, uint height, uint channels);
GLuint loadTexture(const std::string path);

void loadTextureArray(GLuint* const texture, std::vector<std::string> pathes);
void loadTextureArray(GLuint* const texture, const std::vector<std::vector<unsigned char>> data, uint width, uint height, uint channels);
GLuint loadTextureArray(std::vector<std::string> pathes);

void loadCubemapTexture(GLuint* const texture, std::vector<std::string> pathes);
GLuint loadCubemapTexture(std::vector<std::string> pathes);

} // namespace bebra::graphics