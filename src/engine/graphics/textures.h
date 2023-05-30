#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stb_image.h>

#include <string>
#include <vector>

namespace bebra::graphics {

// Texture params:
enum TextureFormat { eRGBA, eRGB, eR };
enum TextureWrapping { eClamp, eClampToEdge, eRepeat, eRepeatMirrored };
enum TextureFiltering { eNearest, eLinear, eNearestMipmapLinear, eNearestMipmapNearest, eLinearMipmapLinear, eLinearMipmapNearest };

struct TextureParams {
    TextureFormat    format       = eRGBA;
    TextureFiltering minFilteting = eNearest;
    TextureFiltering magFilteting = eNearest;
    TextureWrapping  sideWrapping = eRepeat;
    TextureWrapping  topWrapping  = eRepeat;
    int anisotropyLevel = 16;
};

// Texture class:
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

// Texture loading:
GLuint createTexture(
    const GLint internalformat, const uint width, const uint height,
    const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
);
GLuint createMultisampleTexture(
    const GLint internalformat, const uint width, const uint height,
    const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE
);

void loadTexture(GLuint* const texture, Texture raw, const TextureParams params = {});
void loadTexture(GLuint* const texture, const std::vector<unsigned char> data,
    uint width, uint height, uint channels, const TextureParams params = {}
);
GLuint loadTexture(Texture raw, const TextureParams params = {});

void loadTextureArray(GLuint* const texture, std::vector<Texture> textures, const TextureParams params = {});
GLuint loadTextureArray(std::vector<std::string> pathes, TextureParams params = {});

void loadCubemapTexture(GLuint* const texture, std::vector<std::string> pathes, const TextureParams params = {});
GLuint loadCubemapTexture(std::vector<std::string> pathes, TextureParams params = {});

} // namespace bebra::graphics