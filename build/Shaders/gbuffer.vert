#version 450
in vec2 texCoords;
in vec3 fragPos;
in vec3 normal;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

void main()
{
    TexCoords = texCoords;
    FragPos = fragPos;
    Normal = normal;
}