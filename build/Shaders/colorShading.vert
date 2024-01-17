#version 450

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec3 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 Projection; // This is the projection matrix of your camera.

void main() {
    gl_Position = Projection * vec4(vertexPosition, 1.0);
    
    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
