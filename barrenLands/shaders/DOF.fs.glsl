#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;


void main() {
        fFragColor = texture(uTexture1, vTexCoords).xyz;

}
