#include "game/shaders.h"
#include <glm/gtc/type_ptr.hpp>

namespace craft {

// class SkyboxShaderApi
    void SkyboxShaderApi::view(const glm::mat4 view) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    void SkyboxShaderApi::projection(const glm::mat4 projection) {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
    void SkyboxShaderApi::worldTime(const double time) {
        glUniform1f(worldTimeLoc, time);
    }

    SkyboxShaderApi::SkyboxShaderApi(const bebra::graphics::ShaderProgram shaderProgram)
    : program(shaderProgram) {
        viewLoc       = glGetUniformLocation(program.program, "view");
        projectionLoc = glGetUniformLocation(program.program, "projection");
        worldTimeLoc  = glGetUniformLocation(program.program, "worldTime");
    }

//class BlockShaderApi
    void BlockShaderApi::view(const glm::mat4 view) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    void BlockShaderApi::projection(const glm::mat4 projection) {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
    void BlockShaderApi::worldTime(const double time) {
        glUniform1f(worldTimeLoc, time);
    }
    void BlockShaderApi::model(const glm::mat4 model) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    }

    BlockShaderApi:: BlockShaderApi(const bebra::graphics::ShaderProgram shaderProgram)
    : program(shaderProgram) {
        viewLoc       = glGetUniformLocation(program.program, "view");
        projectionLoc = glGetUniformLocation(program.program, "projection");
        worldTimeLoc  = glGetUniformLocation(program.program, "worldTime");
        modelLoc = glGetUniformLocation(program.program, "model");
    }

}