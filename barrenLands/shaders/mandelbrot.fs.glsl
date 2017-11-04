#version 330

in vec4 vLocalPosition;

out vec3 fFragColor;

vec2 complexSqr(vec2 c){
    return vec2( (c.x * c.x)-(c.y * c.y) , 2 * c.x * c.y);
}

vec3 mandelbrotColor(vec2 c) {
    int nMax = 100;
    vec2 suiteC = vec2(0,0);
    for(int i = 0; i< nMax; i++) {
         suiteC += complexSqr(suiteC) + c ;
         if ( length(suiteC) > 2 ) {
            if (float(i)/nMax > 0.4) {
                return vec3(1, 0.4, 0.4)*float(i)/nMax;
            }
            return vec3(0.7*float(i)/nMax, 0, float(i)/nMax);
         }
    }
    return vec3(0.3,0,0);
}

void main() {
    fFragColor = mandelbrotColor(vLocalPosition.xy);
}