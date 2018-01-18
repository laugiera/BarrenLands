#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords_vs;

out vec3 fFragColor;

uniform sampler2D uTexture0;
uniform vec3 uColor;

vec3 multiplyTexture(vec3 color, vec4 textureAlpha) {
    textureAlpha = textureAlpha * 0.3;
    color.x = color.x + 0.2;
    return color - textureAlpha.xyz;
}

void main() {
        fFragColor = multiplyTexture(uColor , texture(uTexture0, vTexCoords_vs));
}
