//
// Created by Lou Landry on 15/01/2018.
//

#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "../include/ProceduralObject.hpp"
/**
 * Constructor
 * generates defaults vertices and indices
 */
ProceduralObject::ProceduralObject() : renderObject(nullptr), position(glm::vec3(0.f)) {
    generateVertices();
    generateIndices();
}
/**
 * Destructor
 */
ProceduralObject::~ProceduralObject() {
    //delete renderObject;
}
/**
 * generateVertices()
 * Cube
 */
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
 * generateIndices()
 *
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
 * generateNormals()
 */
void ProceduralObject::generateNormals() {
}
/**
 * createRenderObject()
 * creates corresponding renderObject and it's GPU Program
 * By default, Element program is used and one random texture from the texture manager is added
 * @param ProgramManager * programManager
 * @param TextureManager * textureManager
 * @param Color * color, default null
 */
void ProceduralObject::createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color *color) {
    std::vector<glcustom::Texture *> textures = chooseTextures(textureManager);
    renderObject = new RenderObject(programManager->getElementProgram(), textures);
    renderObject->fillData(vertices, indices);
    renderObject->setColor(color);
}
/**
 * draw()
 * makes a default transformation on the model matrix
 * render the object
 * @param glm::mat4  viewMatrix
 */
void ProceduralObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0,0,0), 0, glm::vec3(0,1,0), glm::vec3(1,1,1));
    renderObject->render(viewMatrix);
}
/**
 * chooseTextures()
 * return an random texture from textureManager; by default it's a sand texture
 * @param TextureManager * textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralObject::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("sand"));
}

void ProceduralObject::subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    if(nbRecurse == 0){
        return;
    }
    std::vector<glimac::ShapeVertex> subdividedObject;
    int i = 0;
    while (i<_vertices.size()){
        std::vector<glimac::ShapeVertex> face;
        for(int j = 0; j<3; j++){
            face.push_back(_vertices[i]);
            i++;
        }
        subdivideFace(face);
        subdividedObject.insert(subdividedObject.end(), face.begin(), face.end());
    }
    _vertices.clear();
    _vertices = subdividedObject;
    subdivideObject(_vertices, nbRecurse-1);
}

void ProceduralObject::subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    //prend un vecteur de 3 vertices
    glm::vec3 subDiv1, subDiv2, subDiv3;
    float deux = 2;
    subDiv1 = (_vertices[1].position - _vertices[0].position) /deux + _vertices[0].position;
    subDiv2 = (_vertices[2].position - _vertices[1].position) /deux + _vertices[1].position;
    subDiv3 = (_vertices[0].position - _vertices[2].position) /deux + _vertices[2].position;

    glimac::ShapeVertex v1(glm::vec3(subDiv1),
                           glm::vec3(glm::normalize(subDiv1)),
                           glm::vec2(1,1)
    );

    glimac::ShapeVertex v2(glm::vec3(subDiv2),
                           glm::vec3(glm::normalize(subDiv2)),
                           glm::vec2(1,1)
    );

    glimac::ShapeVertex v3(glm::vec3(subDiv3),
                           glm::vec3(glm::normalize(subDiv3)),
                           glm::vec2(1,1)
    );

    std::vector<glimac::ShapeVertex> __vertices;

    __vertices.emplace_back(_vertices[0]);
    __vertices.emplace_back(v1);
    __vertices.emplace_back(v3);

    __vertices.emplace_back(v1);
    __vertices.emplace_back(v3);
    __vertices.emplace_back(v2);

    __vertices.emplace_back(v3);
    __vertices.emplace_back(v2);
    __vertices.emplace_back(_vertices[2]);

    __vertices.emplace_back(v2);
    __vertices.emplace_back(v1);
    __vertices.emplace_back(_vertices[1]);

    _vertices.clear();
    _vertices = __vertices;


}





