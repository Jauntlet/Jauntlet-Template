#version 450
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gSpecular;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{
    gPosition = FragPos;
    gNormal = normalize(Normal);
    gSpecular.rgb = texture(texture_diffuse, TexCoords).rgb;
    gSpecular.a = texture(texture_specular, TexCoords).r;
}