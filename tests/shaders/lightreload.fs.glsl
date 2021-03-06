#version 330 core

// Entrées du shader
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 VPosition;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 MV;
uniform sampler2D uTexture;
uniform sampler2D uTexture2;
uniform sampler2D uMoistureTexture;
uniform int uSubDiv;
uniform vec4 Light_cameraspace;

vec3 multiplyTexture(vec3 color, vec4 textureAlpha) {
    textureAlpha = textureAlpha * 0.3;
    color.x = color.x + 0.2;
    return color - textureAlpha.xyz;
}

vec3 toundra_neige = vec3(200.f/255.f, 250.f/255.f, 245.f/255.f);
vec3 toundra = vec3(168.f/255.f, 212.f/255.f, 206.f/255.f);
vec3 roche = vec3(150.f/255.f, 150.f/255.f, 150.f/255.f);
vec3 toundra_herbe = vec3(153.f/255.f, 153.f/255.f, 51.f/255.f);
vec3 herbe = vec3(153.f/255.f, 204.f/255.f, 0.f/255.f);
vec3 savane = vec3(255.f/255.f, 153.f/255.f, 0.f/255.f);
vec3 craquele = vec3(255.f/255.f, 153.f/255.f, 102.f/255.f);
vec3 sable = vec3(255.f/255.f, 255.f/255.f, 153.f/255.f);

vec3 sableTexture = multiplyTexture(sable, texture(uTexture2, UV));
vec3 toundraNeigeTexture = multiplyTexture(toundra_neige, texture(uTexture, UV));

float height = VPosition.y;
float moisture = (texture(uMoistureTexture, UV/uSubDiv)).x;

vec3 assignColor() {
if (height < 0.25){
    if (moisture < 2.f/6.f){
    return sableTexture;
    } else {
    return herbe;
    }

} else if (height < 0.5){
    if (moisture < 2.f/6.f){
        return craquele;
    } else if (moisture < 5.f/6.f){
        return savane;
    } else {
        return herbe;
    }

} else if (height < 0.75){
    if (moisture < 2.f/6.f){
        return roche;
    } else if (moisture < 4.f/6.f){
        return toundra;
    } else {
        return toundra_herbe;
    }
} else {
    if (moisture < 2.f/6.f){
        return roche;
    } else if (moisture < 3.f/6.f){
        return toundra;
    } else {
        return toundraNeigeTexture;
    }

}
}

void main() {
   // Light emission properties
   	// You probably want to put them as uniforms
   	vec3 LightColor = vec3(1,0.2,0);
   	float LightPower = 1.0f;

   	// Material properties
   	vec3 MaterialDiffuseColor = assignColor();
   	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
   	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);


   	// Normal of the computed fragment, in camera space
   	vec3 n = normalize( Normal_cameraspace );
   	// Direction of the light (from the fragment to the light)
   	vec3 l = normalize( Light_cameraspace.xyz );
   	// Cosine of the angle between the normal and the light direction,
   	// clamped above 0
   	//  - light is at the vertical of the triangle -> 1
   	//  - light is perpendicular to the triangle -> 0
   	//  - light is behind the triangle -> 0
   	float cosTheta = clamp( dot( n,l ), 0,1 );

   	// Eye vector (towards the camera)
   	vec3 E = normalize(EyeDirection_cameraspace);
   	// Direction in which the triangle reflects the light
   	vec3 R = reflect(-l,n);
   	// Cosine of the angle between the Eye vector and the Reflect vector,
   	// clamped to 0
   	//  - Looking into the reflection -> 1
   	//  - Looking elsewhere -> < 1
   	float cosAlpha = clamp( dot( E,R ), 0,1 );

  	color =
   		// Ambient : simulates indirect lighting
   		MaterialAmbientColor +
   		// Diffuse : "color" of the object
   		MaterialDiffuseColor * LightColor * LightPower * cosTheta +
   		// Specular : reflective highlight, like a mirror
   		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5);

}

