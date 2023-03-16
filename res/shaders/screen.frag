#version 330 core
  
in vec2 TexCoords;
 
uniform sampler2D colorbuffer;
uniform sampler2D normalbuffer;
uniform sampler2D positionbuffer;

out vec4 color;

void main() {

    color = texture(colorbuffer, TexCoords);

}