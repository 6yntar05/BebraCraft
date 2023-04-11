#version 300 es
precision mediump float;

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

void main(void) {
    color = texture(skybox, TexCoords);

    color = vec4(
        color.xyz * (-(atan(3.3 - (worldTime*10.0)) / 2.85) + 0.5),
        color.w
    );

    // G-Buffer filling
    normal = vec4(Normal, color.w);
    position = vec4(glPos.xyz, 0.0);
}