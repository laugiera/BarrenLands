#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 aVertexTexCoords;

// Output data ; will be interpolated for each fragment.
out vec3 vPosition_modelspace;
//out vec3 fPosition_modelspace;
// Values that stay constant for the whole mesh.
uniform mat4 uMVP;
uniform mat4 uMV;

void main(){

	// return vertex position in camera space

	gl_Position =  (uMVP * vec4(vertexPosition_modelspace,1)).xyww;
	vPosition_modelspace = vertexPosition_modelspace;
	//vPosition_modelspace = normalize(vertexPosition_modelspace - vec3(0));

}
