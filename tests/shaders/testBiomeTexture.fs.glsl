#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords_vs;
in vec3 vPosition_o;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;
uniform sampler2D uMoistureTexture;
uniform int uSubDiv;

out vec3 fFragColor;

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

vec3 sableTexture = multiplyTexture(sable, texture(uTexture2, vTexCoords_vs));
vec3 toundraNeigeTexture = multiplyTexture(toundra_neige, texture(uTexture, vTexCoords_vs));

float height = vPosition_o.y;
float moisture = (texture(uMoistureTexture, vTexCoords_vs/uSubDiv)).x;
//float moisture = 0.5;

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
    fFragColor = assignColor();
    //fFragColor = vec3(moisture, moisture, moisture);
    /*
    if(length(vTexCoords_vs) < 0.1){
        fFragColor = vec3(1,1,1);
    } else if (length(vTexCoords_vs) > 0.9 && length(vTexCoords_vs) < 1.1 ){
       fFragColor = vec3(1,0,0);
   }
    else {
    fFragColor = vec3(0,0,0);
    }
    */
}
