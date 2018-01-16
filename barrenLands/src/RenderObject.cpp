//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/RenderObject.hpp"


RenderObject::~RenderObject() {

}

void RenderObject::fillData(std::vector<glimac::ShapeVertex> vertices, std::vector<uint32_t> _indices) {
    indices = _indices;
    //si les indices n'ont pas étés renseignés, remplir le tableau d'indices avec les indices des vertices (de 0 à nbVertices-1)
    if(indices.empty()){
        for(int i = 0; i < vertices.size(); i++){
            //indices.push_back(i);
        }
    }
    //glcustom::VBO vbo;
    vbo.fillBuffer(vertices);
    //glcustom::IBO ibo;
    ibo.fillBuffer(indices);
    vao.fillBuffer(vertices, &vbo, &ibo);
}

void RenderObject::render(const glm::mat4 &viewMatrix) {
    program->use();
    //proj matrix à externaliser
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Tools::windowWidth/Tools::windowHeight, 0.1f, 500.f);
    modelMatrix = glm::mat4(1.0);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);
    program->sendUniformMat4("uNormal", normals);


    if(texture){
        texture->bind();
        program->sendUniformTextureUnit("uTexture", 0);
    }
    /*
    program->sendUniformVec3("uKd",glm::vec3(1.0));
    program->sendUniformVec3("uKs",glm::vec3(1.0));
    program->sendUniform1f("uShininess", 64);
     */
    program->sendUniformVec3("uColor", glm::vec3(0.5, 0.5, 0.5));
    /*
    globalLeft.sendLightUniforms(program);
    globalRight.sendLightUniforms(program);
    playerLight.sendLightUniforms(program);
    */
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.debind();

    if(texture)
        texture->debind();

}

RenderObject::RenderObject(glcustom::GPUProgram *program, glcustom::Texture *texture)
        : program(program), texture(texture), vao(), vbo(), ibo() {}

void RenderObject::transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                             const glm::vec3 &scale) {
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::translate(transformation, translate);
    transformation = glm::rotate(transformation,glm::radians(angle),axesRotation);
    transformation = glm::scale(transformation,scale);
    modelMatrix = transformation;
}
