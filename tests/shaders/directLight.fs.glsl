#version 330 core

// Entrées du shader
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 MV;
uniform vec4 LightPosition_worldspace;
uniform sampler2D uTexture;
uniform sampler2D uTexture2;


vec3 toundra_neige = vec3(200.f/255.f, 250.f/255.f, 245.f/255.f) + + (texture(uTexture, UV)).xyz;
vec3 toundra = vec3(168.f/255.f, 212.f/255.f, 206.f/255.f);
vec3 roche = vec3(150.f/255.f, 150.f/255.f, 150.f/255.f) + (texture(uTexture, UV)).xyz;
vec3 toundra_herbe = vec3(153.f/255.f, 153.f/255.f, 51.f/255.f);
vec3 herbe = vec3(153.f/255.f, 204.f/255.f, 0.f/255.f);
vec3 savane = vec3(255.f/255.f, 153.f/255.f, 0.f/255.f);
vec3 craquele = vec3(255.f/255.f, 153.f/255.f, 102.f/255.f);
vec3 sable = vec3(255.f/255.f, 255.f/255.f, 153.f/255.f) + (texture(uTexture2, UV)).xyz;


vec3 assignColor() {
    if (UV.y < 0.25){
        if (UV.x < 2.f/6.f){
        return sable;
        } else {
        return herbe;
        }

    } else if (UV.y < 0.5){
        if (UV.x < 2.f/6.f){
            return craquele;
        } else if (UV.x < 5.f/6.f){
            return savane;
        } else {
            return herbe;
        }

    } else if (UV.y < 0.75){
        if (UV.x < 2.f/6.f){
            return roche;
        } else if (UV.x < 4.f/6.f){
            return toundra;
        } else {
            return toundra_herbe;
        }
    } else {
        if (UV.x < 2.f/6.f){
            return roche;
        } else if (UV.x < 3.f/6.f){
            return toundra;
        } else {
            return toundra_neige;
        }
    }
}


void main() {
   // Light emission properties
   	// You probably want to put them as uniforms
   	vec3 LightColor = vec3(1,0.8,0.5);
   	float LightPower = 20.0f;

   	// Material properties
   	vec3 MaterialDiffuseColor = assignColor();
   	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
   	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

   	// Distance to the light
   	float distance = length( LightPosition_worldspace.xyz - Position_worldspace );

   	// Normal of the computed fragment, in camera space
   	vec3 n = normalize( Normal_cameraspace );
   	// Direction of the light (from the fragment to the light)
   	vec3 l = normalize( LightDirection_cameraspace );
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
   		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
   		// Specular : reflective highlight, like a mirror
   		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
}

