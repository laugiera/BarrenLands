#include "ProceduralTree.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralTree::ProceduralTree(): ProceduralObject(){
    vertices.clear();
    indices.clear();
    tronc = new ProceduralBranche();
    feuillage = new ProceduralFeuillage();
    glm::vec3 posFeuillage = glm::vec3(position.x, position.y + tronc->getHeight(), position.z);
    feuillage->setPosition(posFeuillage);

}

ProceduralTree::~ProceduralTree() {
    delete feuillage;
    delete tronc;
}

void ProceduralTree::generateVertices(){

}

/**
 * createRenderObject()
 * Redefined to uses it's own renderObject and GPU Program
 * Will be common to all rocks
 * @param ProgramManager * programManager
 * @param TextureManager * textureManager
 * @param Color * color, default null
 */
void ProceduralTree::createRenderObject(ProgramManager *programManager, TextureManager *textureManager,  Color * color){
    tronc->createRenderObject(programManager, textureManager,  color);
    Color colorFeuille(0,1,0);
    feuillage->createRenderObject(programManager, textureManager,  &colorFeuille);
}
/**
 * chooseTextures()
 * Redefined to get a rock texture
 * @param textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralTree::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("rock")); //A CHANGER ?
}
/**
 * static setPositions()
 * @param objects
 */
void ProceduralTree::setPositions(std::vector<ProceduralObject *> objects){

}

void ProceduralTree::draw(const glm::mat4 &viewMatrix) {
    tronc->draw(viewMatrix);
    feuillage->draw(viewMatrix);
}
