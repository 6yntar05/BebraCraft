#version 300 es
precision mediump float;

in vec2 TexCoords;
in vec2 glPos;

uniform int renderHUD;
uniform int width;
uniform int height;

uniform sampler2D colorbuffer;
uniform sampler2D normalbuffer;
uniform sampler2D positionbuffer;

out vec4 color;

void main(void) {
    // Draw from GBuffer
    color = texture(colorbuffer, TexCoords);

    // Crosshair
    float widhtRatio = 1.0 / float(width);
    float heightRatio = 1.0 / float(height);
    float xcomp = abs(glPos.x + (widhtRatio/2.0));
    float ycomp = abs(glPos.y + (heightRatio/2.0));

    if ((renderHUD != 0) && (
        ((          // Horisontal
            xcomp >= 0.0 &&
            xcomp <= (widhtRatio * 20.0)
        ) && (
            ycomp >= 0.0 &&
            ycomp <= (heightRatio * 2.0)
        )) || ((    // Verical
            xcomp >= 0.0 &&
            xcomp <= (widhtRatio * 2.0)
        ) && (
            ycomp >= 0.0 &&
            ycomp <= (heightRatio * 20.0)
        ))
    )) {
        color.xyz = vec3(1.0) - color.xyz;
    }
}