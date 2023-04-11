#pragma once
#include "engine/graphics/cubemaps.h"
#include "engine/graphics/shaders.h"

#include "game/shaders.h"

namespace craft {

class skybox { // TODO
private:
    bebra::graphics::ShaderProgram shader;
    craft::SkyboxShaderApi shaderApi;
    GLuint VBO;
    GLuint VAO;
    GLuint texture;

public:
    skybox(bebra::graphics::ShaderProgram shader = {"shaders/skybox.vert", "shaders/skybox.frag"}) 
        : shader(shader), shaderApi(shader)
    {
        bebra::graphics::loadObject(this->VBO, this->VAO);
        this->texture = bebra::graphics::loadCubemapTexture({
          "textures/skybox/ft.png",
          "textures/skybox/bk.png",
          "textures/skybox/up.png",
          "textures/skybox/dn.png",
          "textures/skybox/lf.png",
          "textures/skybox/rt.png"
        });

    }

    void render(const glm::mat4& view, const glm::mat4& projection, const double rawTime) {
        glDepthMask(GL_FALSE);
        shader.use();
        shaderApi.view(view);
        shaderApi.projection(projection);
        shaderApi.worldTime(rawTime);
        glBindVertexArray(this->VAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
    }
};

} // namespace craft
