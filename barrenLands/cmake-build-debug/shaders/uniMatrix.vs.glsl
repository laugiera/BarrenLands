# version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

out vec2 vFragTexture;

uniform mat3 uModelMatrice;

mat3 translate(float tx, float ty){
  mat3 M = mat3(1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                tx, ty, 1.0);
  return M;
}

void main() {
    vFragTexture = aVertexTexture;
    //mat3 T = translate(0.5, 0.5);
    //vec3 pos = T * vec3(aVertexPosition, 1);
    //gl_Position = vec4( pos , 1);
    gl_Position = vec4( uModelMatrice* vec3(aVertexPosition, 1), 1);
}