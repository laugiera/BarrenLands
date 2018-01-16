#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 aVertexTexCoords;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 VPosition;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 MV;
uniform vec4 Light_cameraspace;

void main(){

	// return vertex position in camera space
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	VPosition = vertexPosition_modelspace;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( MV * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Normal of the the vertex, in camera space
	Normal_cameraspace = ( MV * vec4(vertexNormal_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	UV = aVertexTexCoords;

}

