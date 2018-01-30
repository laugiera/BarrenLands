//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/RenderObject.hpp"

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
    //std::cout << "render object created" << std::endl;
}

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
    verticesCount = vertices.size();
    indices = _indices;
    //si les indices n'ont pas étés renseignés, remplir le tableau d'indices avec les indices des vertices (de 0 à nbVertices-1)
    glcustom::VBO vbo;
    vbo.fillBuffer(vertices);
    if(indices.empty()){
        vao.fillBuffer(vertices, &vbo);
    } else {
        glcustom::IBO ibo;
        ibo.fillBuffer(indices);
        vao.fillBuffer(vertices, &vbo, &ibo);
    }



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

void RenderObject::alterModelMatrix(const glm::mat4 &transfos) {
    modelMatrix =  modelMatrix * transfos;
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
        if(texture) {
            texture->bind(GL_TEXTURE_2D, textureUnit + i);
            program->sendUniformTextureUnit("uTexture" + std::to_string(i), i);
            i++;
        }
    }
}
/**
 * debindTextures()
 */
void RenderObject::debindTextures() {
    for(glcustom::Texture * texture : textures){
        if(texture){
            texture->debind(GL_TEXTURE_2D);
        }
    }
}
/**
 * sendUniforms()
 * send MV, MVP, normals uniforms, and uColor uniform
 * @param glm::mat4  viewMatrix
 */
void RenderObject::sendUniforms(const glm::mat4 &viewMatrix) {
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = Tools::projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);
    program->sendUniformMat4("uNormal", normals);

    program->sendUniformVec3("uColor", glm::vec3(color->getVec3()));


}
/**
 * render()
 * render the object by using it's own GPU Program, sending it's own uniforms and binding it's own textures
 * @param viewMatrix
 */
void RenderObject::render(const glm::mat4 &viewMatrix, const  std::vector<Instance*> &instances) {
    program->use();
    bindTextures();
    vao.bind();
    if(instances.size()!=0){
        for (int i = 0; i < instances.size(); ++i) {
            sendUniforms(viewMatrix);
            this->setColor(&instances[i]->getColor());
            this->transform(instances[i]->position, 0, glm::vec3(0, 1, 0), glm::vec3(1));
            this->alterModelMatrix(instances[i]->getTransfo());
            if(indices.empty()){
                glDrawArrays(GL_TRIANGLES, 0, verticesCount);
            } else {
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            }
        }
    }
    else {
        sendUniforms(viewMatrix);
        if(indices.empty()){
            glDrawArrays(GL_TRIANGLES, 0, verticesCount);
        } else {
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        }
    }
    vao.debind();
    debindTextures();

}


