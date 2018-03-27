#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0;

float linearizeDepth(sampler2D depthTexture)
{
    float uZNear = 0.1;
    float uZFar = 2000;
    float depth = texture(depthTexture, vTexCoords).x;
    return (2.0 * uZNear) / (uZFar + uZNear - depth * (uZFar - uZNear));
}

void main() {
        fFragColor = texture(uTexture0, vTexCoords).xyz;
        //fFragColor = vec3(linearizeDepth(uTexture0));

}
