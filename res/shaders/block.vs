#version 330 core

#extension GL_ARB_explicit_attrib_location : require

// VBO & Textures
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
out vec3 Position;
out vec2 TexCoord;
flat out int vertexID;

// Positions
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 glPos;

void main(void){
    // Calculate position
    gl_Position = projection * view * model * vec4(position, 1.0);
    
    // Pass data to fragment shader
    vertexID = gl_VertexID;
    TexCoord = texCoord;
    Position = position;
    glPos = gl_Position;

}
