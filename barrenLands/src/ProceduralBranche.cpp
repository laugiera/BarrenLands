#include "ProceduralBranche.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralBranche::ProceduralBranche(): ProceduralObject(){
    vertices.clear();
    indices.clear();

    //Initialisation
    height = 3*NoiseManager::getInstance().getRandomFloat() +3;
    radius1 = 0.2*NoiseManager::getInstance().getRandomFloat()+0.1;
    radius2 = 0.1*NoiseManager::getInstance().getRandomFloat()+0.05;
    nbrSub = 6*NoiseManager::getInstance().getRandomFloat()+4;
    generateVertices();
    generateNormals();
}

ProceduralBranche::~ProceduralBranche() {}

void ProceduralBranche::generateVertices(){
    int i;
    //Triangles de la face du bas
    for(i=0; i<nbrSub; ++i){
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x, position.y, position.z),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*i*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
    }

    //Triangles de la face du haut
    for(i=0; i<nbrSub; ++i){
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x, position.y+height, position.z),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*i*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
    }

    //Triangle du cylindre, par 2
    for(i=0; i<nbrSub; ++i){
        //Triangle du Haut
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*i*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*i*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        //Triangle du Bas
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*i*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));

    }

}

void ProceduralBranche::generateNormals() {
    for(int i = 0; i< vertices.size(); i += 3){
        glm::vec3 dir1 = vertices[i+1].position - vertices[i].position;
        glm::vec3 dir2 = vertices[i+2].position - vertices[i+1].position;
        glm::vec3 norm = glm::normalize(glm::cross(dir1, dir2));
        vertices[i].normal = norm;
        vertices[i+1].normal = norm;
        vertices[i+2].normal = norm;
    }
}

/**
 * chooseTextures()
 * Redefined to get a rock texture
 * @param textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralBranche::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("rock"));
}

glm::mat4 ProceduralBranche::getRandomScale() {
    return glm::scale(glm::mat4(1.f), glm::vec3(5,5,5));
}
