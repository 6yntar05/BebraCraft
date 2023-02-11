#version 110

#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in float texIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;
out float TexIndex;

void main(void){
    gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoord = texCoord;
    TexIndex = texIndex;
}
