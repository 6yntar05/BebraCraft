#version 330 core 

#extension GL_ARB_explicit_attrib_location : require

// Vertex input
in vec3 TexCoords;
in vec3 Normal;
in vec4 glPos;

uniform samplerCube skybox;
 
// World data
uniform float worldTime;

// Out
out vec4 color;
out vec4 normal;
out vec4 position;

void main() {
    color = texture(skybox, TexCoords);

    color = vec4(
        color.xyz * (-(atan(3.3 - (worldTime*10)) / 2.85) + 0.5),
        color.w
    );

    normal = vec4(Normal, 1.0);

    // G-Buffer filling
    normal = vec4(Normal, color.w);
    position = vec4(glPos.xyz, 0.0);
}