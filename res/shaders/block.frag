#version 330 core

#extension GL_ARB_explicit_attrib_location : require

// VBO & Textures
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
flat in int vertexID;
uniform sampler2DArray textureArray;

// Vertex input
in vec4 glPos;

// Game
uniform float worldTime;

// G-Buffer
out vec4 color;
out vec4 normal;
out vec4 position;

// Constants
const float camShadEase = 5.0;
const float sideShading = 0.1;
const float downShading = 0.2;

void main(void){
    color = texture(textureArray, vec3(TexCoord, vertexID/6));
    
    if (color.w < 0.001) discard; // Dirty 'hack'

    // Camera shadow
    if (color.w > 0.9)
        color.xyz -= vec3(
            ( 1.0 - gl_FragCoord.z )
            /*--------------------*/ /
                   camShadEase
        );
    
    // Simple shading
    color = vec4(
            color.xyz * (
                1.0 - ( max( abs(Normal.x), abs(Normal.z) ) * sideShading )
            ),
            color.w
        );

    if (Normal.y > 0.0)
        color = vec4(
                color.xyz * (1.0 - downShading),
                color.w
            );

    color = vec4(
            color.xyz * (-(atan(3.3 - (worldTime*10)) / 2.85) + 0.5),
            /* (1.0 - (
                pow(0.95 - globalLight, 3)
            )),*/
            color.w
        );
    
    // G-Buffer filling
    normal = vec4(Normal, color.w);
    position = vec4(glPos.xyz, gl_FragCoord.w);
    
}
