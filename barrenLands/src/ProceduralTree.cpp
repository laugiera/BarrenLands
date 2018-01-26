#include "ProceduralTree.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralTree::ProceduralTree(): ProceduralObject(), tronc(nullptr), feuillage(nullptr){
    vertices.clear();
    indices.clear();
    tronc = ElementManager::getInstance().createProceduralBranche();
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

    glm::vec3 globalScale = glm::vec3(1, 0.3, 1);

    if(!tronc || !feuillage){
        throw std::runtime_error("Il n'y a pas de tronc ou de feuillage défini");
    } else {
        tronc->addInstance(position, biomeColor);
        Color colorFeuille(biomeColor); colorFeuille.green(0.1); colorFeuille.blue(0.1); colorFeuille.randomSimilarColor(0.05);
        glm::vec3 posFeuillage = glm::vec3(position.x, position.y + tronc->getHeight(), position.z);
        posFeuillage = globalScale * posFeuillage;
        feuillage->addInstance(posFeuillage, colorFeuille);
    }
}

/**
 * Alter the positions vector attribut as a whole to allow custom repartition of the objects
 * Will affect all the object of this type on the map
 */
void ProceduralTree::scatter() {
    //gérer la répartition du vecteur de positions;
    //if three x or z positions ar near each other, then we group them
    float epsilon = 60,  ecartX = 0, ecartZ = 0;
    int i = 5;
    while (i<instances.size()){
        ecartX = (instances[i-1]->position.x + instances[i-2]->position.x + instances[i-3]->position.x + instances[i-4]->position.x +
                instances[i-5]->position.x+ instances[i]->position.x)/6;
        ecartZ = (instances[i-1]->position.z + instances[i-2]->position.z + instances[i-3]->position.z + instances[i-4]->position.z +
                instances[i-5]->position.z+ instances[i]->position.z)/6;
        if(ecartX < epsilon){
            instances[i-1]->position.x = instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-2]->position.x = instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-3]->position.x = instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-4]->position.x = instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-5]->position.x = instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat()*1.5);

            instances[i-1]->position.y =  getHauteur(instances[i-1]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-2]->position.y =  getHauteur(instances[i-2]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-3]->position.y =  getHauteur(instances[i-3]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-4]->position.y =  getHauteur(instances[i-4]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-5]->position.y =  getHauteur(instances[i-5]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
        }
        if(ecartZ < epsilon){
            instances[i-1]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-2]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-3]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-4]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-5]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat()*1.5);

            instances[i-1]->position.y =  getHauteur(instances[i-1]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-2]->position.y =  getHauteur(instances[i-2]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-3]->position.y =  getHauteur(instances[i-3]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-4]->position.y =  getHauteur(instances[i-4]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
            instances[i-5]->position.y =  getHauteur(instances[i-5]->position) - (NoiseManager::getInstance().getRandomFloat()*3);
        }
        i+=6;
    }
}



