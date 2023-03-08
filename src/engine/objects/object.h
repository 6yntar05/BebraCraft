#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace bebra::objects {
    struct objectTexture {
        GLuint front, back, up, down, left, right;

        objectTexture() {/*transparent... later*/}

        objectTexture(GLuint texture)
            : front(texture), back(texture), up(texture), down(texture), left(texture), right(texture)
            {}
        
        objectTexture(GLuint front, GLuint back, GLuint up, GLuint down, GLuint left, GLuint right)
            : front(front), back(back), up(up), down(down), left(left), right(right)
            {}
    };

    
}