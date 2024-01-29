#version 450

in vec3 vertexPosition;
in vec2 vertexUV;

out vec3 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 Projection; // This is the projection matrix of your camera.
uniform mat4 modelTransform; // Rotation and position of the model

void main() {
    gl_Position = Projection * modelTransform * vec4(vertexPosition, 1.0);
    
    fragmentPosition = vertexPosition;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
