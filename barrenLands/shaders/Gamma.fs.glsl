#version 330


in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform float uZNear;
uniform float uZFar;



float worldSpaceZ( sampler2D depthTexture) {
    float zBuffer = texture(depthTexture, vTexCoords).x;
    float zGlSpace = 2.0 * zBuffer - 1.0;
    float zWorldSpace = 2.0 * uZNear * uZFar / (uZFar + uZNear - zGlSpace * (uZFar - uZNear));
    return zWorldSpace;
}

float linearizeDepth(sampler2D depthTexture)
{
    float depth = texture(depthTexture, vTexCoords).x;
    return (2.0 * uZNear) / (uZFar + uZNear - depth * (uZFar - uZNear));
}

void main() {

        vec3 beautyColor = texture(uTexture0, vTexCoords).xyz;
        float depth = linearizeDepth(uTexture1);
        float COC;
        float endFocus = 0.6;
        if (depth > endFocus)
            COC = clamp( abs((depth - endFocus)/ (1 - endFocus)), 0.0, 1.0);
        else
            COC = 0;

        fFragColor = beautyColor + COC * vec3(depth + 0.1, depth, depth + 0.1)*0.2;



}
