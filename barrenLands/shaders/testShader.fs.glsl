#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords_vs;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
        fFragColor = (texture(uTexture, vTexCoords_vs)).xyz;
}
