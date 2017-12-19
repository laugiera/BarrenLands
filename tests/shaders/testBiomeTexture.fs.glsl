#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords_vs;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

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


vec3 assignColor() {
if (vTexCoords_vs.y < 0.25){
    if (vTexCoords_vs.x < 2.f/6.f){
    return sableTexture;
    } else {
    return herbe;
    }

} else if (vTexCoords_vs.y < 0.5){
    if (vTexCoords_vs.x < 2.f/6.f){
        return craquele;
    } else if (vTexCoords_vs.x < 5.f/6.f){
        return savane;
    } else {
        return herbe;
    }

} else if (vTexCoords_vs.y < 0.75){
    if (vTexCoords_vs.x < 2.f/6.f){
        return roche;
    } else if (vTexCoords_vs.x < 4.f/6.f){
        return toundra;
    } else {
        return toundra_herbe;
    }
} else {
    if (vTexCoords_vs.x < 2.f/6.f){
        return roche;
    } else if (vTexCoords_vs.x < 3.f/6.f){
        return toundra;
    } else {
        return toundraNeigeTexture;
    }

}
}




void main() {
    fFragColor = assignColor();
}
