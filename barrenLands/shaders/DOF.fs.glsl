#version 330


in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform float uZNear;
uniform float uZFar;

float windowWidth = 1200;
float windowHeight = 1000;


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
        float COC;
        /*
        float viewDepth = worldSpaceZ(uTexture2);
        float focus = 50;
        if( viewDepth < focus )
            COC = clamp( abs( (viewDepth - uZNear) / focus ), 0.0, 1.0);
        else
            COC = clamp( abs( (viewDepth - uZNear) / uZFar ), 0.0, 1.0);

*/
        float depth = linearizeDepth(uTexture2);
        float endFocus = 0.5;
        if (depth > endFocus)
            COC = clamp( abs((depth - endFocus)/ (1 - endFocus)), 0.0, 1.0);
        else
            COC = 0;


        vec3 initialColor = texture(uTexture1, vTexCoords).xyz; /*+ (vec3(linearizeDepth()))*0.6*/ // print depth
        vec3 blurredColor = texture(uTexture0, vTexCoords).xyz;

        fFragColor = (1-COC) * initialColor + COC * blurredColor /*+ COC * vec3(linearizeDepth(uTexture2))*0.4*/;
        //fFragColor = blurredColor;
        //fFragColor = vec3(COC);


}
