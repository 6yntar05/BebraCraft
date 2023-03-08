#version 110

#extension GL_ARB_explicit_attrib_location : require

in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourTexture;

void main(void){
    color = texture2D(ourTexture, TexCoord);
}
