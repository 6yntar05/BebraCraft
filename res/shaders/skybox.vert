#version 300 es
precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;

out vec3 Normal;
out vec3 TexCoords;
out vec4 glPos;

void main(void) {
    TexCoords = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
    gl_Position = gl_Position.xyww; // zbuffer optimisation (requies GL_EQUAL-like blend func)
    Normal = aNormal;
    glPos = gl_Position;
} 
