#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords_vs;

out vec3 fFragColor;

void main() {
    fFragColor = normalize(vec3(1.0,vTexCoords_vs.x,vTexCoords_vs.y));
}
