#include "game/shaders.h"
#include <glm/gtc/type_ptr.hpp>

namespace craft {

// class skyboxShaderApi
    void skyboxShaderApi::view(const glm::mat4 view) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    void skyboxShaderApi::projection(const glm::mat4 projection) {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
    void skyboxShaderApi::worldTime(const double time) {
        glUniform1f(worldTimeLoc, time);
    }

    skyboxShaderApi::skyboxShaderApi(const bebra::graphics::shaderProgram shaderProgram)
    : program(shaderProgram) {
        viewLoc       = glGetUniformLocation(program.program, "view");
        projectionLoc = glGetUniformLocation(program.program, "projection");
        worldTimeLoc  = glGetUniformLocation(program.program, "worldTime");
    }

//class blockShaderApi
    void blockShaderApi::view(const glm::mat4 view) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    void blockShaderApi::projection(const glm::mat4 projection) {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
    void blockShaderApi::worldTime(const double time) {
        glUniform1f(worldTimeLoc, time);
    }
    void blockShaderApi::model(const glm::mat4 model) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    }

    blockShaderApi:: blockShaderApi(const bebra::graphics::shaderProgram shaderProgram)
    : program(shaderProgram) {
        viewLoc       = glGetUniformLocation(program.program, "view");
        projectionLoc = glGetUniformLocation(program.program, "projection");
        worldTimeLoc  = glGetUniformLocation(program.program, "worldTime");
        modelLoc = glGetUniformLocation(program.program, "model");
    }

}