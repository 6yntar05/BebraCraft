#version 300 es
precision highp float;

// VBO & Textures
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

// Positions
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 glPos;

void main(void) {
    // Calculate position
    gl_Position = projection * view * model * vec4(position, 1.0);

    // Pass data to fragment shader
    TexCoord = texCoord;
    Normal = normal;
    Position = position;
    
    glPos = gl_Position;
}