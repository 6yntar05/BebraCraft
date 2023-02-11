#version 330 core

#extension GL_ARB_explicit_attrib_location : require

in vec3 TexCoords;
uniform samplerCube textures;

in vec2 TexCoord;
in float TexIndex;
uniform sampler2D front;
uniform sampler2D back;
uniform sampler2D up;
uniform sampler2D down;
uniform sampler2D left;
uniform sampler2D right;

out vec4 color;

void main(void){
    if (TexIndex == 0.0)
        color = texture2D(front, TexCoord);
    else if (TexIndex < 1.1)
        color = texture2D(back, TexCoord);
    else if (TexIndex < 2.1)
        color = texture2D(up, TexCoord);
    else if (TexIndex < 3.1)
        color = texture2D(down, TexCoord);
    else if (TexIndex < 4.1)
        color = texture2D(left, TexCoord);
    else if (TexIndex < 5.1)
        color = texture2D(right, TexCoord);
    else color = vec4(1.0, 0.0, 1.0, 1.0); // Error

    //color = texture(textures, TexCoords);
}
