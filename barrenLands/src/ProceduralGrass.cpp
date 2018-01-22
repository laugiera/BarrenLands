#include "ProceduralGrass.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralGrass::ProceduralGrass(): ProceduralObject(){
    vertices.clear();
    indices.clear();
    height = 9;
    width = 0.5;
    theta1 = 90*NoiseManager::getInstance().getRandomFloat()+90;
    theta2 = 90*NoiseManager::getInstance().getRandomFloat()+90;
    theta3 = 90*NoiseManager::getInstance().getRandomFloat()+90;
    std::cout << "theta 1 : " << theta1 << "theta 2 : " << theta2 << "theta 3 : " << theta3 << std::endl;
    generateVertices();
    generateIndices();
}

ProceduralGrass::~ProceduralGrass() {}


void ProceduralGrass::generateVertices() {
    vertices.push_back(glimac::ShapeVertex(glm::vec3(0, 0, 0), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(width, 0, 0), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(height*cos(glm::radians(theta1))/3, height*sin(glm::radians(theta1))/3, 0), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(height*cos(glm::radians(theta1))/3 + width*6.0/10.0, height*sin(glm::radians(theta1))/3 , 0), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(height*(cos(glm::radians(theta1))+cos(glm::radians(theta2)))/3
            , height*(sin(glm::radians(theta1))+sin(glm::radians(theta2)))/3, 0), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(height*(cos(glm::radians(theta1))+cos(glm::radians(theta2)))/3 + width*4.0/10.0
            , height*(sin(glm::radians(theta1))+sin(glm::radians(theta2)))/3, 0), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(height*(cos(glm::radians(theta1))+cos(glm::radians(theta2))+cos(glm::radians(theta3)))/3
            , height*(sin(glm::radians(theta1))+sin(glm::radians(theta2))+sin(glm::radians(theta3)))/3, 0), glm::vec3(0,0,0), glm::vec2(0,0)));
}

void ProceduralGrass::generateIndices() {
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
}


/**
 * createRenderObject()
 * Redefined to uses it's own renderObject and GPU Program
 * Will be common to all rocks
 * @param ProgramManager * programManager
 * @param TextureManager * textureManager
 * @param Color * color, default null
 */
void ProceduralGrass::createRenderObject(ProgramManager *programManager, TextureManager *textureManager,  Color * color){
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
std::vector<glcustom::Texture *> ProceduralGrass::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("rock"));
}
/**
 * static setPositions()
 * @param objects
 */
void ProceduralGrass::setPositions(std::vector<ProceduralObject *> objects){

}