#include "SapinTree.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

SapinTree::SapinTree(): ProceduralTree(), tronc(nullptr), sapin(nullptr){
    vertices.clear();
    indices.clear();
    tronc = ElementManager::getInstance().createProceduralBranche();
    sapin = ElementManager::getInstance().createProceduralSapin();
    std::cout << sapin->instances.size() << std::endl;
}

SapinTree::~SapinTree() {
}

void SapinTree::generateVertices(){

}

/**
 * createRenderObject()
 * Redefined to uses it's own renderObject and GPU Program
 * Will be common to all rocks
 * @param ProgramManager * programManager
 * @param TextureManager * textureManager
 * @param Color * color, default null
 */
void SapinTree::createRenderObject(ProgramManager *programManager, TextureManager *textureManager,  Color * color){
    tronc->createRenderObject(programManager, textureManager, color);
    sapin->createRenderObject(programManager, textureManager, color);
}


void SapinTree::addInstance(const glm::vec3 &position, const Color &biomeColor) {

    float scale = 0.25;
    if(!tronc || !sapin){
        throw std::runtime_error("Il n'y a pas de tronc ou de feuillage défini");
    } else {
        glm::vec3 truePosition = getRandomPosition(position);
        truePosition.y += getHauteur(position);
        Color colorTronc(0.5,0.5,0.5); colorTronc.randomSimilarColor(0.05);
        tronc->addInstance(truePosition, colorTronc);
        Color colorFeuille(biomeColor); colorFeuille.green(0.1); colorFeuille.blue(0.1); colorFeuille.randomSimilarColor(0.05);
        float heightScale = scale * tronc->getHeight();
        glm::vec3 posFeuillage = glm::vec3(position.x, truePosition.y + heightScale, position.z);
        sapin->addInstance(posFeuillage, colorFeuille);
    }
}

//
// Created by Etienne on 31/01/2018.
//

void SapinTree::scatter() {
    //gérer la répartition du vecteur de positions;
    //if three x or z positions ar near each other, then we group them
    float epsilon = 30,  ecartX = 0, ecartZ = 0, decalage = 10;
    int i = 5;
    glm::vec3 posFeuillage;
    float heightScale = 0.25 *  tronc->getHeight();
    while (i<tronc->instances.size()){
        ecartX = (tronc->instances[i-1]->position.x + tronc->instances[i-2]->position.x + tronc->instances[i-3]->position.x + tronc->instances[i-4]->position.x +
                  tronc->instances[i-5]->position.x+ tronc->instances[i]->position.x)/6;
        ecartZ = (tronc->instances[i-1]->position.z + tronc->instances[i-2]->position.z + tronc->instances[i-3]->position.z + tronc->instances[i-4]->position.z +
                  tronc->instances[i-5]->position.z+ tronc->instances[i]->position.z)/6;
        if(ecartX < epsilon){
            tronc->instances[i-1]->position.x = tronc->instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat()*decalage);
            tronc->instances[i-2]->position.x = tronc->instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat()*decalage);
            tronc->instances[i-3]->position.x = tronc->instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat()*decalage);
            tronc->instances[i-4]->position.x = tronc->instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat()*decalage);
            tronc->instances[i-5]->position.x = tronc->instances[i]->position.x   - (NoiseManager::getInstance().getRandomFloat()*decalage);

            tronc->instances[i-1]->position.y =  getHauteur(tronc->instances[i-1]->position)- abs(NoiseManager::getInstance().getRandomFloat()*3);
            tronc->instances[i-2]->position.y =  getHauteur(tronc->instances[i-2]->position)- abs(NoiseManager::getInstance().getRandomFloat()*3);
            tronc->instances[i-3]->position.y =  getHauteur(tronc->instances[i-3]->position)- abs(NoiseManager::getInstance().getRandomFloat()*3);
            tronc->instances[i-4]->position.y =  getHauteur(tronc->instances[i-4]->position)- abs(NoiseManager::getInstance().getRandomFloat()*3);
            tronc->instances[i-5]->position.y =  getHauteur(tronc->instances[i-5]->position)- abs(NoiseManager::getInstance().getRandomFloat()*3);
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
            posFeuillage = glm::vec3(tronc->instances[j]->position.x, tronc->instances[j]->position.y  + heightScale,  tronc->instances[j]->position.z);
            //posFeuillage = globalScale * posFeuillage;
            sapin->instances[j]->position = posFeuillage;
        }
    }
}