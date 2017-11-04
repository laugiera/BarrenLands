#version 330

layout(location = 0) in vec2 aVertexPosition;


out vec4 vLocalPosition;


void main() {
    vLocalPosition = vec4(aVertexPosition.xy, 0,1);
    gl_Position = vec4(aVertexPosition, 0, 1);
}