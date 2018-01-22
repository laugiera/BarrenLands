//
// Created by natshez on 18/01/2018.
//

#include "ProceduralRock.hpp"
/** Constructor and destructor**/
ProceduralRock::ProceduralRock(): ProceduralObject(){
    //generateVertices();
    //generateIndices();
}
ProceduralRock::~ProceduralRock() {}
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
    //TO CHANGE
    //renderObject = new RenderRock(programManager->getElementProgram(), textures,color); // to change if program is different
    renderObject = new RenderObject(programManager->getElementProgram(), textures, color);
    renderObject->fillData(vertices, indices);
    //renderObject->setColor(color);
}
/**
 * chooseTextures()
 * Redefined to get a rock texture
 * @param textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralRock::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("rock"));
}
/**
 * static setPositions()
 * @param objects
 */
void ProceduralRock::setPositions(std::vector<ProceduralObject *> objects){

}