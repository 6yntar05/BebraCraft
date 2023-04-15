#version 300 es
precision mediump float;

// VBO & Textures
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
flat in int vertexID;
//uniform mediump sampler2DArray textureArray;
uniform mediump sampler2D textureUV;

// Vertex input
in vec4 glPos;

// Game
uniform float worldTime;

// G-Buffer
layout(location = 0) out vec4 COL0; // color
layout(location = 1) out vec4 COL1; // normal
layout(location = 2) out vec4 COL2; // position

// Constants
const float camShadEase = 5.0;
const float sideShading = 0.2;
const float downShading = 0.3;

void main(void) {
    //COL0 = texture(textureArray, vec3(TexCoord, (vertexID%36)/4)); // TODO: UV textures
    COL0 = texture(textureUV, TexCoord); // TODO: UV textures
    
    if (COL0.w < 0.001) discard; // Dirty 'hack'

    // Camera shadow
    if (COL0.w > 0.9)
        COL0.xyz -= vec3(
            ( 1.0 - gl_FragCoord.z )
            /*--------------------*/ /
                   camShadEase
        );
    
    // Simple shading
    COL0 = vec4(
            COL0.xyz * (
                1.0 - ( max( abs(Normal.x), abs(Normal.z) ) * sideShading )
            ),
            COL0.w
        );

    if (Normal.y > 0.0)
        COL0 = vec4(
                COL0.xyz * (1.0 - downShading),
                COL0.w
            );

    COL0 = vec4(
            COL0.xyz * (-(atan(3.3 - (worldTime*10.0)) / 2.85) + 0.5),
            /* (1.0 - (
                pow(0.95 - globalLight, 3)
            )),*/
            COL0.w
        );
    
    // G-Buffer filling
    COL1 = vec4(Normal, COL0.w); // Normal
    COL2 = vec4(glPos.xyz, gl_FragCoord.w); // Position
    
}
