#version 450

in vec2 fragmentUV;

out vec4 color;

uniform sampler2D imageTexture;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gSpecular;

void main() {
    vec3 FragPos = texture(gPosition, fragmentUV).rgb;
    vec3 Normal = texture(gPosition, fragmentUV).rgb;
    vec3 Albedo = texture(gSpecular, fragmentUV).rgb;
    float Specular = texture(gSpecular, fragmentUV).a;

    color = texture(imageTexture, fragmentUV);
}
