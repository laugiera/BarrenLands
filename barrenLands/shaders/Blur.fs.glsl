#version 330
#define M_PI 3.1415926535897932384626433832795


in vec2 vTexCoords;
in vec4 gl_FragCoord ;

out vec3 fFragColor;

uniform sampler2D uTexture0;
uniform float uZNear;
uniform float uZFar;
uniform int uSampleCount;
uniform vec3 uDirection;

vec4 blur9(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.3846153846) * direction;
  vec2 off2 = vec2(3.2307692308) * direction;
  color += texture(image, uv) * 0.2270270270;
  color += texture(image, uv + (off1 / resolution)) * 0.3162162162;
  color += texture(image, uv - (off1 / resolution)) * 0.3162162162;
  color += texture(image, uv + (off2 / resolution)) * 0.0702702703;
  color += texture(image, uv - (off2 / resolution)) * 0.0702702703;
  return color;
}


void main() {
        ivec2 direction = ivec2(uDirection.xy);
        float weight = 1.0 / (uSampleCount * 2.0);
        vec3 color = vec3(0.0, 0.0, 0.0);
        for(int i=-uSampleCount;i<=uSampleCount;++i)
        {
        ivec2 coord = ivec2(gl_FragCoord.xy) + i*direction;
        color += texelFetch(uTexture0, coord, 0).xyz * weight;
        }
        fFragColor = color;
        vec2 resolution = vec2(1200, 1000);
        fFragColor = blur9(uTexture0, vTexCoords.xy, resolution , uDirection.xy).xyz;

}
