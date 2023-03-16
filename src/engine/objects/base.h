#pragma once
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace bebra {
namespace objects {

    enum objIdent {
        ebase,
        eblock,
        eglass,
        //eleaves,
        eplant,
        efluid
    };

    struct objectTexture {
        std::vector<GLuint> textures;
    };

    class object {
      public:
        // Structure and textures
        static constexpr float verticies[] = {{}};
        static constexpr GLuint indices[] = {{}};
        objectTexture texture;

        // Position
        float rotate;

        // Render
        static void loadObject(GLuint& VBO, GLuint& VAO, GLuint& EBO) {
            std::cerr << "Wtf its base object" << std::endl;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindVertexArray(0);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        };

        // Service
        objIdent id = objIdent::ebase;
        object() {};
        object(objIdent id) : id(id) {};
        object(objectTexture texture, float rotate = 0.0)
            : texture(texture), rotate(rotate) {}
    };

}
}