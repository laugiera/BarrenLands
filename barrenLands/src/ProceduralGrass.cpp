#include "ProceduralGrass.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralGrass::ProceduralGrass(glm::vec3 pos): ProceduralObject(){
    //Récupérations des coordonnées de la map
    float** terrain = NoiseManager::getInstance().getElevationMap(Tools::nbSub+1, Tools::nbSub+1);
    std::vector<glm::vec3> tab;
    int i;
    int j;
    for(i=0; i<Tools::nbSub+1; ++i){
        for(j=0; j<Tools::nbSub+1; j++){
            tab.push_back(glm::vec3(-Tools::width*Tools::nbSub/2.0+j*Tools::width, terrain[i][j], -Tools::width*Tools::nbSub/2.0+i*Tools::width));
        }
    }

    //Initialisation
    vertices.clear();
    indices.clear();
    height = 0.1;
    width = 0.01;
    position = pos;

    //On prépare la répartition des herbes
    std::vector<glm::vec2> rayons;
    for(i=0; i < 20000; ++i){
        rayons.push_back(glm::vec2(NoiseManager::getInstance().getRandomFloat()*10, NoiseManager::getInstance().getRandomFloat()*10));
    }
    int caseI =0;
    int caseJ =0;
    float hauteur = 0;
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    glm::vec3 v4;
    for(int k =0; k<rayons.size(); ++k){
        caseI = (position.z+rayons[k].y) + Tools::width*Tools::nbSub/2;
        caseJ = (position.x+rayons[k].x) + Tools::width*Tools::nbSub/2;

        v1 = tab[caseI*(Tools::nbSub+1) + caseJ];
        v2 = tab[caseI*(Tools::nbSub+1) + caseJ + 1];
        v3 = tab[(caseI+1)*(Tools::nbSub+1) + caseJ];
        v4 = tab[(caseI+1)*(Tools::nbSub+1) + caseJ + 1];


        if(inTriangle(v1, v2, v3, glm::vec3(position.x + rayons[k].x, 0, position.z + rayons[k].y)) == 1){
            hauteur = determinerHauteur(v1, v2, v3, glm::vec3(position.x + rayons[k].x, 0, position.z + rayons[k].y));
        }
        else if(inTriangle(v2, v3, v4, glm::vec3(position.x + rayons[k].x, 0, position.z + rayons[k].y)) == 1){
            hauteur = determinerHauteur(v2, v3, v4, glm::vec3(position.x + rayons[k].x, 0, position.z + rayons[k].y));
        }
        else{
            hauteur = v1.y;
        }
        //std::cout << hauteur << std::endl;
        addGrass(90*NoiseManager::getInstance().getRandomFloat()+90,
                 90*NoiseManager::getInstance().getRandomFloat()+90,
                 90*NoiseManager::getInstance().getRandomFloat()+90,
                 position.x + rayons[k].x,
                 position.z + rayons[k].y,
                 hauteur);
    }
}

ProceduralGrass::~ProceduralGrass() {}

void ProceduralGrass::addGrass(float theta1, float theta2, float theta3, float x, float z, float y){
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x, y, z), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x + width, y, z), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x + height*cos(glm::radians(theta1))/3,y + height*sin(glm::radians(theta1))/3, z), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x + height*cos(glm::radians(theta1))/3 + width*6.0/10.0, y + height*sin(glm::radians(theta1))/3 , z), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x + height*(cos(glm::radians(theta1))+cos(glm::radians(theta2)))/3
            , y + height*(sin(glm::radians(theta1))+sin(glm::radians(theta2)))/3, z), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x + height*(cos(glm::radians(theta1))+cos(glm::radians(theta2)))/3 + width*4.0/10.0
            , y + height*(sin(glm::radians(theta1))+sin(glm::radians(theta2)))/3, z), glm::vec3(0,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(x + height*(cos(glm::radians(theta1))+cos(glm::radians(theta2))+cos(glm::radians(theta3)))/3
            , y + height*(sin(glm::radians(theta1))+sin(glm::radians(theta2))+sin(glm::radians(theta3)))/3, z), glm::vec3(0,0,0), glm::vec2(0,0)));

    int indsize;
    if(indices.size() != 0){
        indsize = indices[indices.size()-1] + 1;
    }
    else{
        indsize = 0;
    }

    indices.push_back(indsize + 0);
    indices.push_back(indsize + 1);
    indices.push_back(indsize + 2);
    indices.push_back(indsize + 1);
    indices.push_back(indsize + 2);
    indices.push_back(indsize + 3);
    indices.push_back(indsize + 2);
    indices.push_back(indsize + 3);
    indices.push_back(indsize + 4);
    indices.push_back(indsize + 3);
    indices.push_back(indsize + 4);
    indices.push_back(indsize + 5);
    indices.push_back(indsize + 4);
    indices.push_back(indsize + 5);
    indices.push_back(indsize + 6);
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


int ProceduralGrass::inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B, glm::vec3 _position){
    float detPOPA;
    float detPAPB;
    float detPBPO;

    glm::vec2 PO = glm::vec2(O.x - _position.x, O.z - _position.z);
    glm::vec2 PA = glm::vec2(A.x - _position.x, A.z - _position.z);
    glm::vec2 PB = glm::vec2(B.x - _position.x, B.z - _position.z);

    detPOPA = PO.x*PA.y - PO.y*PA.x;
    detPAPB = PA.x*PB.y - PA.y*PB.x;
    detPBPO = PB.x*PO.y - PB.y*PO.x;

    if((detPOPA >=0 && detPAPB >=0 && detPBPO >= 0) ||
       (detPOPA <0 && detPAPB <0 && detPBPO < 0)){
        return 1;
    }
    else{
        return 0;
    }
}

float ProceduralGrass::determinerHauteur(glm::vec3 O, glm::vec3 A, glm::vec3 B, glm::vec3 _position){
    float a = (A.y - O.y)*(B.z - O.z) - (A.z - O.z)*(B.y - O.y);
    float b = (B.x - O.x)*(A.z - O.z) - (A.x - O.x)*(B.z - O.z);
    float c = (A.x - O.x)*(B.y - O.y) - (B.x - O.x)*(A.y - O.y);
    float d= -O.x*a - O.y*b - O.z*c;
    //std::cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << " res = " << (-a*_position.x/Tools::scale - c*_position.z/Tools::scale - d)/b << std::endl;
    return (-a*_position.x - c*_position.z - d)/b;
}