#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/graphics/shaders.h"

namespace craft {

    class BlockShaderApi  {
      private:
        bebra::graphics::ShaderProgram program;
	      GLint viewLoc;
        GLint projectionLoc;
        GLint worldTimeLoc;
        GLint modelLoc;

      public:
	      void view(const glm::mat4 view);
        void projection(const glm::mat4 projection);
        void worldTime(const double time);
        void model(const glm::mat4 model);

        BlockShaderApi(const bebra::graphics::ShaderProgram shaderProgram);
    };

	class SkyboxShaderApi {
      private:
        bebra::graphics::ShaderProgram program;
        GLint viewLoc;
        GLint projectionLoc;
        GLint worldTimeLoc;

      public:
        void view(const glm::mat4 view);
        void projection(const glm::mat4 projection);
        void worldTime(const double time);

        void setData(const glm::mat4& view, const glm::mat4& projection, const double time) {
            this->view(view);
            this->projection(projection);
            this->worldTime(time);
        } // TODO: use this

        SkyboxShaderApi(const bebra::graphics::ShaderProgram shaderProgram);
    };

}