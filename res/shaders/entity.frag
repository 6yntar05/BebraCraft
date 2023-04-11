#version 300 es
precision mediump float;

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
out vec4 color;
out vec4 normal;
out vec4 position;

void main(void) {
    color = texture2D(texture, TexCoord);
    
    if (color.w < 0.001) discard; // Dirty 'hack'
    
    // G-Buffer filling
    normal = vec4(Normal, color.w);
    position = vec4(glPos.xyz, gl_FragCoord.w);
    
}
