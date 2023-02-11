#version 110

#extension GL_ARB_explicit_attrib_location : require
//#extension GL_EXT_texture_array : require

in vec2 TexCoord;
in float TexIndex;

out vec4 color;

uniform sampler2D front;
uniform sampler2D back;
uniform sampler2D up;
uniform sampler2D down;
uniform sampler2D left;
uniform sampler2D right;

//uniform sampler2DArray textures;

void main(void){
    if (TexIndex == 0.0)
        color = texture2D(front, TexCoord);
    else if (TexIndex == 1.0)
        color = texture2D(back, TexCoord);
    else if (TexIndex == 2.0)
        color = texture2D(up, TexCoord);
    else if (TexIndex == 3.0)
        color = texture2D(down, TexCoord);
    else if (TexIndex == 4.0)
        color = texture2D(left, TexCoord);
    else if (TexIndex == 5.0)
        color = texture2D(right, TexCoord);
    else
        color = vec4(1.0, 0.0, 1.0, 1.0); // Error

    //color = texture2DArray(textures, vec3(TexCoord, 0.0));
    //if (color.a < 0.01) discard;
}
