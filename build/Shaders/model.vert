#version 450

in vec3 vertexPosition;
in vec2 vertexUV;

out vec3 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 Projection; // This is the projection matrix of your camera.
uniform vec3 modelPosition; // Position of the model

void main() {
    gl_Position = Projection * vec4(vertexPosition + modelPosition, 1.0);
    
    fragmentPosition = vertexPosition;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
