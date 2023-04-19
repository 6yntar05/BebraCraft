#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stb_image.h>

#include <string>
#include <vector>

namespace bebra::graphics {

class Texture {
private:
    std::vector<unsigned char> image;
    void findGLMode();

public:
    // Data
    int width;
    int height;
    int mode;
    int channels;
    uint uvCount = 1;

    // Service
    unsigned char* getData() { return image.data(); }
    void append(Texture another);   // Creating UV
    void operator+(Texture another) { this->append(another); }

    Texture(const std::vector<unsigned char> raw, int width, int height, int channels = 4);
    Texture(const std::string path, const bool flip = true);
};

static Texture placeholder {
    {
        (u_char)250, (u_char)000, (u_char)240, (u_char)230,  (u_char)010, (u_char)010, (u_char)010, (u_char)230,
        (u_char)010, (u_char)010, (u_char)010, (u_char)230,  (u_char)250, (u_char)000, (u_char)240, (u_char)230
    }, 2, 2, 4
};

GLuint createTexture(
    const GLint internalformat, const uint width, const uint height,
    const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
);
GLuint createMultisampleTexture(
    const GLint internalformat, const uint width, const uint height,
    const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
);

void loadTexture(GLuint* const texture, Texture raw);
void loadTexture(GLuint* const texture, const std::vector<unsigned char> data, uint width, uint height, uint channels);
GLuint loadTexture(Texture raw);

void loadTextureArray(GLuint* const texture, std::vector<Texture> textures);
GLuint loadTextureArray(std::vector<std::string> pathes);

void loadCubemapTexture(GLuint* const texture, std::vector<std::string> pathes);
GLuint loadCubemapTexture(std::vector<std::string> pathes);

} // namespace bebra::graphics