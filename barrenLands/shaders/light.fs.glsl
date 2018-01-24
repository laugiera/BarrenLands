#version 330 core

// Entrées du shader
// Interpolated values from the vertex shaders
in vec2 uV;
in vec3 vPosition;
in vec3 normal_cameraspace;
in vec3 eyeDirection_cameraspace;
in float uMoisture;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform float uSubDiv;

uniform vec4 uLightDirSun;
uniform float uLightIntensitySun;
uniform vec3 uLightColorSun;
uniform vec4 uLightDirMoon;
uniform float uLightIntensityMoon;
uniform vec3 uLightColorMoon;

uniform vec3 uColors[6];

vec3 multiplyTexture(vec3 color, vec4 textureAlpha) {
    textureAlpha = textureAlpha * 0.3;
    return color - textureAlpha.xyz;
}

vec3 sableTexture = multiplyTexture(uColors[0], texture(uTexture1, uV));
vec3 toundraNeigeTexture = multiplyTexture(uColors[3], texture(uTexture2, uV));

float height = vPosition.y;
//float uMoisture = (texture(uTexture0, uV/uSubDiv)).x;


vec3 assignColor() {
if (height < 1){
    if (uMoisture <= 0.1){
    return sableTexture; //sable
    } else {
        return uColors[1]; //grass
    }

} else if (height < 2){
    if (uMoisture < 0.5){
        return uColors[5]; //savana
    } else {
        return uColors[1]; //grass
    }

} else if (height < 5){
    if (uMoisture < 0.1){
        return uColors[4]; //rock
    } else  {
        return uColors[2]; //toundra
    }
} else {
        return toundraNeigeTexture; //snow
}
}

vec3 getLightColor(vec3 lightColor, float lightPower, vec3 direction){

   	// Material properties
   	vec3 materialDiffuseColor = assignColor();
   	vec3 materialAmbientColor = vec3(0.1,0.1,0.1) * materialDiffuseColor;
   	vec3 materialSpecularColor = vec3(0.3,0.3,0.3);

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
   		materialDiffuseColor * lightColor * lightPower * cosTheta +
   		// Specular : reflective highlight, like a mirror
   		materialSpecularColor * lightColor * lightPower * pow(cosAlpha,5);

   	return color;

}

void main() {
    color = getLightColor(uLightColorMoon,uLightIntensityMoon,uLightDirMoon.xyz)
    + getLightColor(uLightColorSun,uLightIntensitySun,uLightDirSun.xyz);
}




