#version 330
#define M_PI 3.1415926535897932384626433832795


in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform float uZNear;
uniform float uZFar;

float windowWidth = 1200;
float windowHeight = 1000;


float worldSpaceZ() {
    float zBuffer = texture(uTexture1, vTexCoords).x;
    float zGlSpace = 2.0 * zBuffer - 1.0;
    float zWorldSpace = 2.0 * uZNear * uZFar / (uZFar + uZNear - zGlSpace * (uZFar - uZNear));
    return zWorldSpace;
}

float linearizeDepth()
{
    float depth = texture(uTexture1, vTexCoords).x;
    return (2.0 * uZNear) / (uZFar + uZNear - depth * (uZFar - uZNear));
}

void main() {

        fFragColor = vec3(linearizeDepth()); // print depth
        //fFragColor = texture(uTexture0, vTexCoords).xyz;


}
