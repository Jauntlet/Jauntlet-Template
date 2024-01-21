#version 450

in vec2 fragmentUV;

out vec4 color;

uniform sampler2D imageTexture;

void main() {	
    color = texture(imageTexture, fragmentUV); //* fragmentColor;
}
