#version 330 core

in vec3 uV;
// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform samplerCube  uTexture0;



void main() {
   color = textureCube(uTexture0,uV);
}