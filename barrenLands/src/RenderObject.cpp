//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/RenderObject.hpp"

/**
 * Destructor
 */
RenderObject::~RenderObject() {
    delete color;
}
/**
 * fillData()
 * fills vbo, ibo and vao buffers
 * @param std::vector<glimac::ShapeVertex> vertices
 * @param std::vector<uint32_t> _indices
 */
void RenderObject::fillData(std::vector<glimac::ShapeVertex> vertices, std::vector<uint32_t> _indices) {
    indices = _indices;
    //si les indices n'ont pas étés renseignés, remplir le tableau d'indices avec les indices des vertices (de 0 à nbVertices-1)
    if(indices.empty()){
        for(uint32_t i = 0; i < vertices.size(); i++){
            indices.push_back(i);
        }
    }
    glcustom::VBO vbo;
    vbo.fillBuffer(vertices);
    glcustom::IBO ibo;
    ibo.fillBuffer(indices);
    vao.fillBuffer(vertices, &vbo, &ibo);
}
/**
 * Constructor
 * @param glcustom::GPUProgram * program
 * @param std::vector<glcustom::Texture *> textures
 * @param Color * _color
 */
RenderObject::RenderObject(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures,  Color *_color)
        : program(program), textures(textures), vao(), color(nullptr){
    if(_color){
        color = new Color(_color);
    } else color = new Color(); //default value
}
/**
 * transform()
 * Applies transformation to the modelMatrix
 * @param translate
 * @param angle
 * @param axesRotation
 * @param scale
 */
void RenderObject::transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                             const glm::vec3 &scale) {
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::translate(transformation, translate);
    transformation = glm::rotate(transformation,glm::radians(angle),axesRotation);
    transformation = glm::scale(transformation,scale);
    modelMatrix = transformation;
}
/**
 * bindTextures()
 * bind all textures (GL_TEXTURE_2D) and send them as uniforms
 * \!/ uniform name will be "uTexture" + number of the unit on wich it is binded
 */
void RenderObject::bindTextures() {
    int textureUnit = GL_TEXTURE0;
    int i = 0;
    for(glcustom::Texture * texture : textures){
        texture->bind(GL_TEXTURE_2D, textureUnit+i);
        program->sendUniformTextureUnit("uTexture" + std::to_string(i), i);
        i++;
    }
}
/**
 * debindTextures()
 */
void RenderObject::debindTextures() {
    for(glcustom::Texture * texture : textures){
        texture->debind(GL_TEXTURE_2D);
    }
}
/**
 * sendUniforms()
 * send MV, MVP, normals uniforms, and uColor uniform
 * @param glm::mat4  viewMatrix
 */
void RenderObject::sendUniforms(const glm::mat4 &viewMatrix) {
    //proj matrix à externaliser
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Tools::windowWidth/Tools::windowHeight, 0.1f, 1500.f);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);
    program->sendUniformMat4("uNormal", normals);

    program->sendUniformVec3("uColor", glm::vec3(color->getVec3()));
    /*
    program->sendUniformVec3("uKd",glm::vec3(1.0));
    program->sendUniformVec3("uKs",glm::vec3(1.0));
    program->sendUniform1f("uShininess", 64);
     */

}
/**
 * render()
 * render the object by using it's own GPU Program, sending it's own uniforms and binding it's own textures
 * @param viewMatrix
 */
void RenderObject::render(const glm::mat4 &viewMatrix) {
    program->use();
    sendUniforms(viewMatrix);
    bindTextures();
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.debind();
    debindTextures();
}
