#version 330 core

in vec3 vPosition_modelspace;
// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform samplerCube  uTexture0;

float PI = 3.14159265359;

void main() {
    float step = 0.5;
    float horizon = -0.2;
    vec4 horizonColor = vec4(0.1, 0.3, 0.5, 1);
    if(vPosition_modelspace.y <= horizon + step +0.1 && vPosition_modelspace.y >= horizon){
        //dégradé horizon
        float y = vPosition_modelspace.y - horizon;
        color = vec4(1-(y / step)) * horizonColor; //linéaire
        //color = vec4(sin(PI * (y +2) /2 / step)) * horizonColor; //sinusoidal
    } else if ( vPosition_modelspace.y < horizon ) {
        color =  horizonColor;
    } else {
        color = texture(uTexture0,vPosition_modelspace);
    }

    /* deuxieme dégradé
    step = 0.2;
    horizonColor.g += 0.1;
    horizonColor.r += 0.1;
    if(vPosition_modelspace.y >= horizon - step && vPosition_modelspace.y <= horizon + step){
        float y = vPosition_modelspace.y + horizon/2;
        float coef = clamp(sin(PI*y/step), 0, 1);
        color = color + coef * abs(horizonColor - color);
    }
    */
    //color = texture(uTexture0,vPosition_modelspace);
}