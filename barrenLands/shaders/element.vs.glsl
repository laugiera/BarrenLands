#version 330

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 aVertexTexCoords;

// Output data ; will be interpolated for each fragment.
out vec2 uV;
out vec3 vPosition;
out vec3 normal_cameraspace;
out vec3 eyeDirection_cameraspace;
out vec3 shadowCoord;

// Values that stay constant for the whole mesh.
uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat4 uNormal;
uniform mat4 uDepthMVP;

void main(){

	// return vertex position in camera space
	gl_Position =  uMVP * vec4(vertexPosition_modelspace,1);
	vPosition = vertexPosition_modelspace;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( uMV * vec4(vertexPosition_modelspace,1)).xyz;
	eyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Normal of the the vertex, in camera space
	normal_cameraspace = ( uMV * vec4(vertexNormal_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	uV = aVertexTexCoords;

	shadowCoord = (uDepthMVP * vec4(vertexNormal_modelspace,0)).xyz;

}

