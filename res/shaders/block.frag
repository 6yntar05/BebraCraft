#version 330 core

#extension GL_ARB_explicit_attrib_location : require

// VBO & Textures
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
flat in int vertexID;
uniform sampler2D front;
uniform sampler2D back;
uniform sampler2D up;
uniform sampler2D down;
uniform sampler2D left;
uniform sampler2D right;

// Raw data
in vec4 glPos;

// FX
float camShadEase = 5.0;

// Color
out vec4 color;

void main(void){
    // Texture choosing (very cringe, i know)
    if (vertexID < 6)
        color = texture2D(front, TexCoord);
    else if (vertexID < 12)
        color = texture2D(back, TexCoord);
    else if (vertexID < 18)
        color = texture2D(left, TexCoord);
    else if (vertexID < 24)
        color = texture2D(right, TexCoord);
    else if (vertexID < 30)
        color = texture2D(up, TexCoord);
    else if (vertexID < 36)
        color = texture2D(down, TexCoord);
    else // Out of range
        color = vec4(1.0, 0.0, 1.0, 1.0);

    // Camera shadow
    if (color.w > 0.9)
        color.xyz -= vec3(
            ( 1.0 - gl_FragCoord.z )
            /*--------------------*/ /
                   camShadEase
        );
    
    //color = vec4(Normal*255, 1.0);
}
