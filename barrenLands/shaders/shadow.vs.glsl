#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

out vec2 vTexCoords;

void main() {
    vTexCoords = aVertexTexCoords;

    gl_Position = vec4(aVertexPosition, 1.0);


}