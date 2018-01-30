#version 330 core

// Entrées du shader
// Interpolated values from the vertex shaders
in vec2 uV;
in vec3 vPosition;
in vec3 normal_cameraspace;
in vec3 eyeDirection_cameraspace;
in float uMoisture;
in vec3 shadowCoord;
in vec4 gl_FragCoord;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D uTexture0;  //sable
uniform sampler2D uTexture1; //neige
uniform sampler2D uTexture2; //shadowMap
uniform float uSubDiv;

uniform vec4 uLightDirSun;
uniform float uLightIntensitySun;
uniform vec3 uLightColorSun;
uniform vec4 uLightDirMoon;
uniform float uLightIntensityMoon;
uniform vec3 uLightColorMoon;

uniform vec3 uColors[6];

float getVisibility(){
    float visibility = 1.0;
    if ( texture( uTexture2, shadowCoord.xy ).z  <  shadowCoord.z){
        visibility = 0.2;
    }
    return visibility;
}

vec3 multiplyTexture(vec3 color, vec4 textureAlpha) {
    textureAlpha = textureAlpha * 0.3;
    return color - textureAlpha.xyz;
}

float primaryCoef( float variable, float intervalLength){
    float coef = min(1.f , intervalLength * intervalLength - abs( 1 / intervalLength * ( variable - intervalLength)));
    coef = clamp(-coef, 0.f, 1.f);
    return coef ;
}

vec3 sableTexture = multiplyTexture(uColors[0], texture(uTexture0, uV));
vec3 toundraNeigeTexture = multiplyTexture(uColors[3], texture(uTexture1, uV));

float height = vPosition.y;
//float uMoisture = (texture(uTexture0, uV/uSubDiv)).x;


vec3 assignColor() {
    vec3 color, colorLow, colorMiddle, colorHigh, colorVeryHigh;
    float coef1;
    float coef2;

    if (height < 1){

        if (uMoisture < 0.1){
        coef1 = primaryCoef(uMoisture, 0.1);
        coef2 = 1.f - coef1;
        colorLow = coef1 * sableTexture + coef2 * uColors[1];
        //return sableTexture; //sable
        } else {
         colorLow= uColors[1]; //grass
        }

        coef1 = primaryCoef(height/10, 0.1);
        //coef1 = clamp(coef1*10, 0, 1);
        coef2 = 1.f - coef1;
        color = coef1 * colorLow + coef2 * uColors[5];
        //color = colorLow;
        //color = vec3(coef1);


    } else if (height < 2){
        if (uMoisture < 1){
            coef1 = primaryCoef(uMoisture, 0.25);
            coef2 = 1.f - coef1;
            colorMiddle = coef1 * uColors[5] + coef2 * uColors[1];
            //color = vec3(coef1);

            colorMiddle =  uColors[5]; //savana
        } else {
            coef1 = primaryCoef(uMoisture, 0.25);
            coef2 = 1.f - coef1;
            colorMiddle = coef1 * uColors[5] + coef2 * uColors[1];
            //color = vec3(coef1);
            //return uColors[1]; //grass
        }

        color = colorMiddle;

    } else if (height < 5){
        if (uMoisture < 0.1){
            coef1 = primaryCoef(uMoisture, 0.1);
            coef2 = 1.f - coef1;
            colorHigh = coef1 * uColors[4] + coef2 * uColors[2];
            //return uColors[4]; //rock
        } else  {
            colorHigh = uColors[2]; //toundra
        }

        coef1 = primaryCoef(height/20, 0.1);
        coef1 = clamp(coef1*3, 0, 1);
        coef2 = 1.f - coef1;
        color = coef1 * colorHigh + coef2 * uColors[5];
        //color = vec3(coef1);
        //color = colorHigh;
    } else {
            colorVeryHigh = toundraNeigeTexture; //snow
            color = colorVeryHigh;
    }
    //color = vec3(coef1);
    return color;
}

vec3 getLightColor(vec3 lightColor, float lightPower, vec3 direction){

   	// Material properties
   	vec3 materialDiffuseColor = assignColor();
   	vec3 materialAmbientColor = vec3(0.1,0.1,0.1) * materialDiffuseColor;
   	vec3 materialSpecularColor = vec3(0.3,0.3,0.3);

   	float visibility = getVisibility();

   	// Normal of the computed fragment, in camera space
   	vec3 n = normalize( normal_cameraspace );
   	// Direction of the light (from the fragment to the light)
   	vec3 l = normalize( direction.xyz );
   	// Cosine of the angle between the normal and the light direction,
   	// clamped above 0
   	//  - light is at the vertical of the triangle -> 1
   	//  - light is perpendicular to the triangle -> 0
   	//  - light is behind the triangle -> 0
   	float cosTheta = clamp( dot( n,l ), 0,1 );
   	// Eye vector (towards the camera)
   	vec3 E = normalize(eyeDirection_cameraspace);
   	// Direction in which the triangle reflects the light
   	vec3 R = reflect(-l,n);
   	// Cosine of the angle between the Eye vector and the Reflect vector,
   	// clamped to 0
   	//  - Looking into the reflection -> 1
   	//  - Looking elsewhere -> < 1
   	float cosAlpha = clamp( dot( E,R ), 0,1 );

  	vec3 color =
   		// Ambient : simulates indirect lighting
   		materialAmbientColor +
   		// Diffuse : "color" of the object
   		visibility * materialDiffuseColor * lightColor * lightPower * cosTheta +
   		// Specular : reflective highlight, like a mirror
   		visibility * materialSpecularColor * lightColor * lightPower * pow(cosAlpha,5);

   	return color;

}
float linearizeDepth()
{   float uZNear = 0.1;
    float uZFar = 2000.f;
    float depth = texture(uTexture2, gl_FragCoord.xy.xy).z;
    return (2.0 * uZNear) / (uZFar + uZNear - depth * (uZFar - uZNear));
}

void main() {
     color = //getLightColor(uLightColorMoon,uLightIntensityMoon,uLightDirMoon.xyz) +
       getLightColor(uLightColorSun,uLightIntensitySun,uLightDirSun.xyz);
 //      color = vec3(linearizeDepth());
}




