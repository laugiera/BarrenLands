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
    glm::vec3 truePosition = position;
    if(!tronc || !feuillage){
        throw std::runtime_error("Il n'y a pas de tronc ou de feuillage défini");
    } else {
        truePosition.y = getHauteur(position);
        tronc->addInstance(truePosition, biomeColor);
        Color colorFeuille(biomeColor); colorFeuille.green(0.1); colorFeuille.blue(0.1); colorFeuille.randomSimilarColor(0.05);
        glm::vec3 posFeuillage = glm::vec3(truePosition.x, truePosition.y + tronc->getHeight(), truePosition.z);
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
        float epsilon = 70,  ecartX = 0, ecartZ = 0;
        int i = 5;
        glm::vec3 posFeuillage;
        glm::vec3 globalScale = glm::vec3(1, 0.3, 1);

    while (i<tronc->instances.size()){
            ecartX = (tronc->instances[i-1]->position.x + tronc->instances[i-2]->position.x + tronc->instances[i-3]->position.x + tronc->instances[i-4]->position.x +
                      tronc->instances[i-5]->position.x+ tronc->instances[i]->position.x)/6;
            ecartZ = (tronc->instances[i-1]->position.z + tronc->instances[i-2]->position.z + tronc->instances[i-3]->position.z + tronc->instances[i-4]->position.z +
                      tronc->instances[i-5]->position.z+ tronc->instances[i]->position.z)/6;
            if(ecartX < epsilon){
                tronc->instances[i-1]->position.x = tronc->instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-2]->position.x = tronc->instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-3]->position.x = tronc->instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-4]->position.x = tronc->instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-5]->position.x = tronc->instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat());

                tronc->instances[i-1]->position.y =  getHauteur(tronc->instances[i-1]->position);
                tronc->instances[i-2]->position.y =  getHauteur(tronc->instances[i-2]->position);
                tronc->instances[i-3]->position.y =  getHauteur(tronc->instances[i-3]->position);
                tronc->instances[i-4]->position.y =  getHauteur(tronc->instances[i-4]->position);
                tronc->instances[i-5]->position.y =  getHauteur(tronc->instances[i-5]->position);
            }
            if(ecartZ < epsilon){
                tronc->instances[i-1]->position.z = tronc->instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-2]->position.z = tronc->instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-3]->position.z = tronc->instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-4]->position.z = tronc->instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat());
                tronc->instances[i-5]->position.z = tronc->instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat());

                tronc->instances[i-1]->position.y =  getHauteur(tronc->instances[i-1]->position);
                tronc->instances[i-2]->position.y =  getHauteur(tronc->instances[i-2]->position);
                tronc->instances[i-3]->position.y =  getHauteur(tronc->instances[i-3]->position);
                tronc->instances[i-4]->position.y =  getHauteur(tronc->instances[i-4]->position);
                tronc->instances[i-5]->position.y =  getHauteur(tronc->instances[i-5]->position);
            }
            i+=6;
            for (int j = 0; j < tronc->instances.size(); ++j) {
                posFeuillage = glm::vec3(tronc->instances[j]->position.x, tronc->instances[j]->position.y  + tronc->getHeight(),  tronc->instances[j]->position.z);
                posFeuillage = globalScale * posFeuillage;
                feuillage->instances[j]->position = posFeuillage;
            }
        }
}



