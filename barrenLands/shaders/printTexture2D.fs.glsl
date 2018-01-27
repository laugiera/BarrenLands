#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0;


void main() {
        fFragColor = texture(uTexture0, vTexCoords).xyz;

}
