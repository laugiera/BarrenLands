#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat4 uNormal;

out vec3 vPosition_vs;
out vec3 vNormal_vs;
out vec2 vTexCoords_vs;


void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vPosition_vs = vec3(uMV * vertexPosition);
    vNormal_vs = vec3(uNormal * vertexNormal);
    vTexCoords_vs = aVertexTexCoords;

    gl_Position = uMVP * vertexPosition;
    gl_Position =  vertexPosition;

    /*
    vPosition_vs = vec3(mat4(1) * mat4(0) * vertexPosition);
    vNormal_vs = vec3(uNormal * vertexNormal);
    gl_Position = uMVP * vertexPosition;
    */

}
