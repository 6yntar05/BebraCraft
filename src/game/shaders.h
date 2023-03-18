#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/graphics/shaders.h"

namespace craft {

    class shaderApi {
        // Base object for shader API construction
    };

    class skyboxShaderApi : public shaderApi {
      private:
        bebra::graphics::shaderProgram program;

      protected:
        GLint viewLoc;
        GLint projectionLoc;
        GLint worldTimeLoc;

      public:
        void view(glm::mat4 view) {
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        }
        void projection(glm::mat4 projection) {
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        }
        void worldTime(double time) {
            glUniform1f(worldTimeLoc, time);
        }

        skyboxShaderApi(bebra::graphics::shaderProgram shaderProgram) : program(shaderProgram) {
            viewLoc       = glGetUniformLocation(program.program, "view");
            projectionLoc = glGetUniformLocation(program.program, "projection");
            worldTimeLoc  = glGetUniformLocation(program.program, "worldTime");
        }
    };

    class blockShaderApi : public skyboxShaderApi {
      private:
        bebra::graphics::shaderProgram program;

      protected:
        GLint modelLoc;

      public:
        void model(glm::mat4 model) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        }

        blockShaderApi(bebra::graphics::shaderProgram shaderProgram)
        : skyboxShaderApi(shaderProgram), program(shaderProgram) {
            modelLoc = glGetUniformLocation(program.program, "model");
        }
    };

}