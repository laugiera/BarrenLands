//
// Created by natshez on 18/01/2018.
//

#include "ProceduralRock.hpp"
/** Constructor and destructor**/
ProceduralRock::ProceduralRock(): ProceduralObject(){
    //generateVertices();
    //generateIndices();
}
ProceduralRock::~ProceduralRock() {
}
/**
 * createRenderObject()
 * Redefined to uses it's own renderObject and GPU Program
 * Will be common to all rocks
 * @param ProgramManager * programManager
 * @param TextureManager * textureManager
 * @param Color * color, default null
 */
void ProceduralRock::createRenderObject(ProgramManager *programManager, TextureManager *textureManager,  Color * color){
    std::vector<glcustom::Texture *> textures = chooseTextures(textureManager);

    renderObject = new RenderObject(programManager->getElementProgram(), textures, chooseColor(color));
    renderObject->fillData(vertices, indices);
}


void ProceduralRock::generateNormals() {
    for(int i = 0; i< vertices.size(); i += 3){
        glm::vec3 dir1 = vertices[i+1].position - vertices[i].position;
        glm::vec3 dir2 = vertices[i+2].position - vertices[i+1].position;
        glm::vec3 norm = glm::normalize(glm::cross(dir1, dir2));
        vertices[i].normal = norm;
        vertices[i+1].normal = norm;
        vertices[i+2].normal = norm;
    }
}

Color *ProceduralRock::chooseColor(Color *_color) {
    Color * alteredColor = new Color(_color);
    //alteredColor->randomSimilarColor(0.1);
    return alteredColor;
}

