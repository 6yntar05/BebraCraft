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
layout(location = 0) out vec4 COL0; // color
layout(location = 1) out vec4 COL1; // normal
layout(location = 2) out vec4 COL2; // position

void main(void) {
    COL0 = texture(skybox, TexCoords);

    COL0 = vec4(
        COL0.xyz * (-(atan(3.3 - (worldTime*10.0)) / 2.85) + 0.5),
        COL0.w
    );

    // G-Buffer filling
    COL1 = vec4(Normal, COL0.w); // normal
    COL2 = vec4(glPos.xyz, 0.0);  // position
}