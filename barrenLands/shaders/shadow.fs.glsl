#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0; //shadowMap Light
uniform sampler2D uTexture1; //depthMap Camera
uniform sampler2D uTexture2; // beauty map Camera

void main() {
        float visibility = 1.0;
        if ( texture( uTexture0, vTexCoords.xy ).z  <  texture( uTexture1, vTexCoords.xy ).z){
            visibility = 0.5;
        }
        fFragColor = texture(uTexture2, vTexCoords).xyz *  visibility;

}