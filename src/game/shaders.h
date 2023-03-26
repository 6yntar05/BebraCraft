#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/graphics/shaders.h"

namespace craft {

    class blockShaderApi  {
      private:
        bebra::graphics::shaderProgram program;

      protected:
	    GLint viewLoc;
        GLint projectionLoc;
        GLint worldTimeLoc;
        GLint modelLoc;

      public:
	    void view(const glm::mat4 view);
        void projection(const glm::mat4 projection);
        void worldTime(const double time);
        void model(const glm::mat4 model);

        blockShaderApi(const bebra::graphics::shaderProgram shaderProgram);
    };

	class skyboxShaderApi {
      private:
        bebra::graphics::shaderProgram program;

      protected:
        GLint viewLoc;
        GLint projectionLoc;
        GLint worldTimeLoc;

      public:
        void view(const glm::mat4 view);
        void projection(const glm::mat4 projection);
        void worldTime(const double time);

        skyboxShaderApi(const bebra::graphics::shaderProgram shaderProgram);
    };

}