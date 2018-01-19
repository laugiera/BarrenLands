//
// Created by Lou Landry on 15/01/2018.
//

#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "../include/ProceduralObject.hpp"

ProceduralObject::ProceduralObject() : renderObject(nullptr), position(glm::vec3(0.f)) {
    generateVertices();
    generateIndices();
}

ProceduralObject::~ProceduralObject() {
    delete renderObject;
}

/**
 * Creates the vertices for a default cube 2x2x2 centerd on 0,0,0
 * Vector must be cleared to avoid conflicts with redefinitions
 **/
void ProceduralObject::generateVertices() {
    vertices.clear();
    //FACE AVANT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,0,1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,0,1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,0,1), glm::vec2(1,1)));
    //Face ARRIERE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,0,-1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)));
    //FACE GAUCHE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(-1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(-1,0,0), glm::vec2(1,0)));
    //FACE DROITE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(1,0,0), glm::vec2(1,0)));
    //FACE HAUT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,1,0), glm::vec2(1,0)));
    //FACE BAS
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,-1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,-1,0), glm::vec2(1,0)));


}

/**
 * Creates the indices
 */
void ProceduralObject::generateIndices() {
    indices.clear();
    uint32_t _indices[] =
            {
                    0,1,2,
                    0,2,3,
                    4,5,6,
                    4,6,7,
                    8,9,10,
                    8,10,11,
                    12,13,14,
                    12,14,15,
                    16,17,18,
                    16,18,19,
                    20,21,22,
                    20,22,23
            };

    indices = std::vector<uint32_t>(_indices, _indices + sizeof(_indices) / sizeof(uint32_t));

}

/**
 * Generates normals
 */
void ProceduralObject::generateNormals() {
}

/**
 * Creates the render Object associated withe de procedural object
 * Decides which GPU program and textures the render Object is to be instancied with
 * @param programManager
 * @param textureManager
 * @param color
 */
void ProceduralObject::createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color *color) {
    std::vector<glcustom::Texture *> textures = chooseTextures(textureManager);
    renderObject = new RenderObject(programManager->getElementProgram(), textures);
    renderObject->fillData(vertices, indices);
    renderObject->setColor(color);
}


/**
 * Chooses which textures form the texture Manager must be used to render the object
 * @param textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralObject::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("sand"));
}

/**
 * Transform the object and draws it
 * @param viewMatrix
 */
void ProceduralObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0,0,0), 0, glm::vec3(0,1,0), glm::vec3(1,1,1));
    renderObject->render(viewMatrix);
}




