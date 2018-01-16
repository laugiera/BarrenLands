#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords_vs;

out vec3 fFragColor;

uniform vec3 uColor;

void main() {
    if(vPosition_vs.x < 0.5 && vPosition_vs.y <0.5){
        fFragColor = vec3(0,1,0);
    }

}
