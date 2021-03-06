#version 330 core

in vec3 vPosition_modelspace;
// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform samplerCube  uTexture0;
uniform vec4 uSunDir;

float PI = 3.14159265359;

// Author: @samloeschen
// Title: paint archipelago

//Quick exploration in fractal brownian motion and generating oil paint-like forms

#ifdef GL_ES
precision mediump float;
#endif

uniform vec3 uResolution;
uniform float uTime;

//generic random
float random (in vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

//@morgan3D noise
float noise (in vec2 st) {

    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

//could probably reduce octaves but meh
#define octaves 7
float fbm (in vec2 p) {

    float value = 0.0;
    float freq = 1.0;
    float amp = 0.5;

    for (int i = 0; i < octaves; i++) {
        value += amp * (noise((p - vec2(1.0)) * freq));
        freq *= 1.9;
        amp *= 0.6;
    }
    return value;
}

//basically all the fbm warps are offset by big slow sine patterns
//when they diverge/are moving away from each other the fluidity feels faster,
//and when they converge its more chilled out

//I haven't tried animating the fbm scales yet but could be cool?

//TODO: add params to further manipulate color ramps with the domain warping
float pattern(in vec2 p) {
    vec2 offset = vec2(-0.5);

    //generate main peaks/valleys
    vec2 aPos = vec2(sin(uTime * 0.005), sin(uTime * 0.01)) * 6.;
    vec2 aScale = vec2(3.0); //base fbm scale
    float a = fbm(p * aScale + aPos);

    //1st domain warp
    vec2 bPos = vec2(sin(uTime * 0.01), sin(uTime * 0.01)) * 1.;
    vec2 bScale = vec2(0.5); //this scale changes the main distortion density. less = smoky, more = oily
    float b = fbm((p + a) * bScale + bPos);

    //2nd domain warp, yay now its paint. this one creates a bunch of diagonal countours that it wasn't
    //immediately obvious how to remove, but they kind of look like sun shafts so whatever
    vec2 cPos = vec2(-0.6, -0.5) + vec2(sin(-uTime * 0.001), sin(uTime * 0.01)) * 2.;
    vec2 cScale = vec2(2.); //this scale "zooms" the image
    float c = fbm((p + b) * cScale + cPos);
    return c;
}

//iq palette
vec3 palette(in float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.45, 0.25, 0.14);
    vec3 c = vec3(1.0 ,1.0, 1.0);
    vec3 d = vec3(0.0, 0.1, 0.2);
    return a + b * cos(6.28318 * (c * t + d));
}

vec4 proceduralTexture() {
    vec3 p = gl_FragCoord.xyz / uResolution.xyz;
    p.x *= uResolution.x / uResolution.y;
    p = p * vPosition_modelspace.xyz;

    //bring out the orange "islands" more
    float value = pow(pattern(p.xy), 2.);

    //map to palette. right now we are just mapping luminosity
    //could be much more interesting/varied if the domain warping changed the color ramp
    vec3 color = palette(value);
    return vec4(color, 1.0);
}

void main() {
    float step = 0.5;
    float horizon = -0.2;
    vec4 skyColor = vec4(0.05,0.0,0.1,0.1);
    vec4 horizonColor = vec4(0.1, 0.3, 0.5, 1);
    vec4 fogColor = vec4(0.43, 0.66, 0.69, 1.0);
    vec4 sunColor = vec4(0.8, 0.4, 0.2, 1.0);
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
    //color = proceduralTexture();
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
   

    color = texture(uTexture0,vPosition_modelspace);
    skyColor = mix(skyColor, sunColor, uSunDir.y/100.0);
    horizonColor = mix(horizonColor, sunColor, uSunDir.y/100.0);
    //skyColor = vec4(vec3(uSunDir.y/100.0), 1.0); //cool result in black and white
    vec3 pointOnSphere = normalize(vPosition_modelspace.xyz);
    float a = smoothstep(-0.1, 0.3, pointOnSphere.y);
    color = mix(horizonColor, skyColor, a);
    a = smoothstep(-0.2, -0.00, pointOnSphere.y);
    color = mix(fogColor, color, a);
}