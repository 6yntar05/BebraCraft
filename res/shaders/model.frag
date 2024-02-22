#version 300 es
precision mediump float;

/*
#if __VERSION__ >= 300
    #define TEXTURE_FUNC texture
#else
    #define TEXTURE_FUNC texture2D
#endif
*/

// VBO & Textures
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
uniform sampler2D texture;

// Vertex input
in vec4 glPos;

// Game
uniform float worldTime;

// G-Buffer
layout(location = 0) out vec4 COL0; // color
layout(location = 1) out vec4 COL1; // normal
layout(location = 2) out vec4 COL2; // position

void main(void) {
    COL0 = texture2D(texture, TexCoord);
    
    if (COL0.w < 0.001) discard; // Dirty 'hack'
    
    // G-Buffer filling
    COL1 = vec4(Normal, COL0.w);
    COL2 = vec4(glPos.xyz, gl_FragCoord.w);
    
}