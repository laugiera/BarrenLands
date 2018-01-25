#include "ProceduralTree.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralTree::ProceduralTree(): ProceduralObject(), tronc(nullptr), feuillage(nullptr){
    vertices.clear();
    indices.clear();
    //tronc = new ProceduralBranche();
    tronc = ElementManager::getInstance().createProceduralBranche();
    //feuillage = new ProceduralFeuillage();
    feuillage = ElementManager::getInstance().createProceduralFeuillage();

}

ProceduralTree::~ProceduralTree() {
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
    tronc->createRenderObject(programManager, textureManager, color);
    feuillage->createRenderObject(programManager, textureManager, color);
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

void ProceduralTree::addInstance(const glm::vec3 &position, const Color &biomeColor) {
    if(!tronc || !feuillage){
        throw std::runtime_error("Il n'y a pas de tronc ou de feuillage défini");
    } else {
        tronc->addInstance(position, biomeColor);
        Color colorFeuille(0, 1, 0);
        glm::vec3 posFeuillage = glm::vec3(position.x, position.y + tronc->getHeight(), position.z);
        feuillage->addInstance(posFeuillage, colorFeuille);
    }
}

glm::mat4 ProceduralTree::getRandomScale() {
    return glm::scale(glm::mat4(1.f), glm::vec3(1,1,1));
}
