//
// Created by Lou Landry on 15/01/2018.
//

#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "../include/ProceduralObject.hpp"
/**
 * Constructor
 * generates defaults vertices and indices
 */
ProceduralObject::ProceduralObject() : renderObject(nullptr), position(glm::vec3(0.f)) {
    generateVertices();
    generateIndices();
    //std::cout << "procedural object created" << std::endl;
}
/**
 * Destructor
 */
ProceduralObject::~ProceduralObject() {
    delete renderObject;
}

/**
 * createRenderObject()
 * creates corresponding renderObject and it's GPU Program
 * By default, Element program is used and one random texture from the texture manager is added
 * The color parameter is usefull only if the rendering for the object is not instanciated
 * @param ProgramManager * programManager
 * @param TextureManager * textureManager
 * @param Color * color, default null
 */
void ProceduralObject::createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color *color) {
    if(!renderObject){
        std::vector<glcustom::Texture *> textures = chooseTextures(textureManager);
        renderObject = new RenderObject(programManager->getElementProgram(), textures, color);
        renderObject->fillData(vertices, indices);
    }
}
/**
 * draw()
 * render one object for each entry in the positions vector
 * applies a random rotation and scale that can be defined for each class
 * @param glm::mat4  viewMatrix
 */
void ProceduralObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    if(renderObject) {
        for (int i = 0; i < instances.size(); i++) {
            renderObject->setColor(&instances[i]->getColor());
            renderObject->transform(instances[i]->position, 0, glm::vec3(0, 1, 0), glm::vec3(1));
            renderObject->alterModelMatrix(instances[i]->getTransfo());
            renderObject->render(viewMatrix);
        }
    }

}

/**
 * Adds a instance of an object
 * Adds its position and color to the positions and colors attributs after having modified them
 * @param position
 * @param biomeColor
 */
void ProceduralObject::addInstance(const glm::vec3 &position, const Color &biomeColor) {
    glm::vec3 truePosition = getRandomPosition(position);
    truePosition.y += getHauteur(position);
    Color trueColor = chooseColor(biomeColor);
    glm::mat4 transfo(1.f);
    transfo =  getRandomScale() * getRandomRotation() * transfo;
    instances.push_back(new Instance(transfo, truePosition,trueColor));
}
/********** SETTING RANDOM PARAMETERS OF THE OBJECT **********/

/**
 * Computes a random position from the base position passed to the function
 * Y coordinates must be defaulted to 0 to allow for later modification with the getHauteur function
 * If Y is different than 0 an offset will be created and the object will not be on the ground (but that can be on purpose)
 *
 * @param position
 * @return
 */
glm::vec3 ProceduralObject::getRandomPosition(const glm::vec3 &position) {
    //gérer l'alléatoire par rapport aux coordonnées de la vertex;
    glm::vec3 truePosition = position;
    truePosition.y = 0; //default configuration, can be overloaded with different settings;
    return truePosition;
}

/**
 * Computes a random rotation for the object in the world space
 * @return
 */
glm::mat4 ProceduralObject::getRandomRotation() {
    return glm::rotate(glm::mat4(1.f), glm::radians(NoiseManager::getInstance().getRandomFloat()), glm::vec3(0,1,0));
}

/**
 * Computes a random scale for the object in the world space
 * @return
 */
glm::mat4 ProceduralObject::getRandomScale() {
    return glm::scale(glm::mat4(1.f), glm::vec3(0.2));
}

/**
 * Alter the positions vector attribut as a whole to allow custom repartition of the objects
 * Will affect all the object of this type on the map
 */
void ProceduralObject::scatter() {
    //gérer la répartition du vecteur de positions;
    //if three x or z positions ar near each other, then we group them
    float epsilon = 20,  ecartX = 0, ecartZ = 0;
    int i = 2;
    while (i<instances.size()){
        ecartX = (instances[i-1]->position.x + instances[i-2]->position.x + instances[i]->position.x)/3;
        ecartZ = (instances[i-1]->position.x + instances[i-2]->position.x + instances[i]->position.x)/3;
        if(ecartX < epsilon){
            instances[i-1]->position.x = instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-1]->position.y =  getHauteur(instances[i-1]->position);
            instances[i-2]->position.x = instances[i]->position.x  - (NoiseManager::getInstance().getRandomFloat());
            instances[i-2]->position.y =  getHauteur(instances[i-2]->position);
        }
        if(ecartZ < epsilon){
            instances[i-1]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat()*1.5);
            instances[i-1]->position.y =  getHauteur(instances[i-1]->position);
            instances[i-2]->position.z = instances[i]->position.z  - (NoiseManager::getInstance().getRandomFloat());
            instances[i-2]->position.y =  getHauteur(instances[i-2]->position);
        }
        i+=3;
    }
}

/**
 * Computes a color for the object from the color passed as parameter
 * @param _color
 * @return a pointer
 */
Color *ProceduralObject::chooseColor(Color *_color) {
    if(!_color){
        return new Color;
    } else {
        return new Color(_color);
    }
}
/**
 * Computes a color for the object from the color passed as parameter
 * @param _color
 * @return a color
 */
Color ProceduralObject::chooseColor(const Color &_c) {
    return _c;
}
/**
 * chooseTextures()
 * return an random texture from textureManager; by default it's a sand texture
 * @param TextureManager * textureManager
 * @return
 */
std::vector<glcustom::Texture *> ProceduralObject::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("sand"));
}




/********** FINDING THE HEIGHT AND ORIENTATION OF THE GROUND BENEATH AN OBJECT **********/

float ProceduralObject::getHauteur(const glm::vec3 &_position) {
    //Récupérations des coordonnées de la map
    float** terrain = NoiseManager::getInstance().heightMap;
    std::vector<glm::vec3> tab;
    int i;
    int j;
    for(i=0; i<Tools::nbSub+1; ++i){
        for(j=0; j<Tools::nbSub+1; j++){
            tab.push_back(glm::vec3(-Tools::width*Tools::nbSub/2.0+j*Tools::width, terrain[i][j], -Tools::width*Tools::nbSub/2.0+i*Tools::width));
        }
    }

    int caseI =0;
    int caseJ =0;
    float hauteur = 0;
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    glm::vec3 v4;
        caseI = int((_position.z) + Tools::width*Tools::nbSub/2);
        caseJ = int((_position.x) + Tools::width*Tools::nbSub/2);

        v1 = tab[caseI*(Tools::nbSub+1) + caseJ];
        v2 = tab[caseI*(Tools::nbSub+1) + caseJ + 1];
        v3 = tab[(caseI+1)*(Tools::nbSub+1) + caseJ];
        v4 = tab[(caseI+1)*(Tools::nbSub+1) + caseJ + 1];

        if(inTriangle(v1, v2, v3, glm::vec3(_position.x, 0, _position.z)) == 1){
            hauteur = determinerY(v1, v2, v3, glm::vec3(_position.x, 0, _position.z));
        }
        else if(inTriangle(v2, v3, v4, glm::vec3(_position.x, 0, _position.z)) == 1){
            hauteur = determinerY(v2, v3, v4, glm::vec3(_position.x, 0, _position.z));
        }
        else{
            hauteur = v1.y;
        }
    return hauteur;
}

int ProceduralObject::inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B, const glm::vec3 &_position){
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

float ProceduralObject::determinerY(glm::vec3 O, glm::vec3 A, glm::vec3 B, const glm::vec3 &_position){
    float a = (A.y - O.y)*(B.z - O.z) - (A.z - O.z)*(B.y - O.y);
    float b = (B.x - O.x)*(A.z - O.z) - (A.x - O.x)*(B.z - O.z);
    float c = (A.x - O.x)*(B.y - O.y) - (B.x - O.x)*(A.y - O.y);
    float d= -O.x*a - O.y*b - O.z*c;
    //std::cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << " res = " << (-a*_position.x/Tools::scale - c*_position.z/Tools::scale - d)/b << std::endl;
    return (-a*_position.x - c*_position.z - d)/b;
}

glm::vec3 ProceduralObject::getNormale(){
    //Récupérations des coordonnées de la map
    float** terrain = NoiseManager::getInstance().heightMap;
    std::vector<glm::vec3> tab;
    int i;
    int j;
    for(i=0; i<Tools::nbSub+1; ++i){
        for(j=0; j<Tools::nbSub+1; j++){
            tab.push_back(glm::vec3(-Tools::width*Tools::nbSub/2.0+j*Tools::width, terrain[i][j], -Tools::width*Tools::nbSub/2.0+i*Tools::width));
        }
    }

    int caseI;
    int caseJ;
    glm::vec3 normale;

    caseI = (position.z) + Tools::width*Tools::nbSub/2;
    caseJ = (position.x) + Tools::width*Tools::nbSub/2;

    glm::vec3 v1 = tab[caseI*(Tools::nbSub+1) + caseJ];
    glm::vec3 v2 = tab[caseI*(Tools::nbSub+1) + caseJ + 1];
    glm::vec3 v3 = tab[(caseI+1)*(Tools::nbSub+1) + caseJ];
    glm::vec3 v4 = tab[(caseI+1)*(Tools::nbSub+1) + caseJ + 1];

    if(inTriangle(v1, v2, v3, position) == 1){
        glm::vec3 dir1 = v2 - v1;
        glm::vec3 dir2 = v3 - v1;
        normale = glm::cross(dir2, dir1);
    }
    else {
        glm::vec3 dir1 = v2 - v3;
        glm::vec3 dir2 = v4 - v3;
        normale = glm::cross(dir2, dir1);
    }

    return normale;
}





/********** HANDLING OBJECT GEOMETRY **********/

/**
 * generateVertices()
 * Cube
 */
void ProceduralObject::generateVertices() {
    vertices.clear();
    //FACE AVANT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,0,1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,0,1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,0,1), glm::vec2(1,1)));
    //Face ARRIERE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,0,-1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)));
    //FACE GAUCHE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(-1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(-1,0,0), glm::vec2(1,0)));
    //FACE DROITE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(1,0,0), glm::vec2(1,0)));
    //FACE HAUT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,1,0), glm::vec2(1,0)));
    //FACE BAS
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,-1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,-1,0), glm::vec2(1,0)));
}
/**
 * generateIndices()
 *
 */
void ProceduralObject::generateIndices() {
    indices.clear();
    uint32_t _indices[] =
            {
                    0,1,2,
                    0,2,3,
                    4,5,6,
                    4,6,7,
                    8,9,10,
                    8,10,11,
                    12,13,14,
                    12,14,15,
                    16,17,18,
                    16,18,19,
                    20,21,22,
                    20,22,23
            };

    indices = std::vector<uint32_t>(_indices, _indices + sizeof(_indices) / sizeof(uint32_t));

}
/**
 * generateNormals()
 * Empty for the base model
 */
void ProceduralObject::generateNormals() {

}
/**
 * Subdivides all the faces of an object any number of time
 * @param _vertices
 * @param nbRecurse
 */
void ProceduralObject::subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    if(nbRecurse <= 0){
        return;
    }
    std::vector<glimac::ShapeVertex> subdividedObject;
    int i = 0;
    while (i<_vertices.size()){
        std::vector<glimac::ShapeVertex> face;
        for(int j = 0; j<3; j++){
            face.push_back(_vertices[i]);
            i++;
        }
        subdivideFace(face);
        subdividedObject.insert(subdividedObject.end(), face.begin(), face.end());
    }
    _vertices.clear();
    _vertices = subdividedObject;
    subdivideObject(_vertices, nbRecurse-1);
}
/**
 * Default subdivision algorithm :
 * one triangle outputs to 4 triangles
 * New vertices stay on the face and are not pushed toxars the exterior
 * @param _vertices
 * @param nbRecurse
 */
void ProceduralObject::subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    //prend un vecteur de 3 vertices
    glm::vec3 subDiv1, subDiv2, subDiv3;
    float deux = 2;
    subDiv1 = (_vertices[1].position - _vertices[0].position) /deux + _vertices[0].position;
    subDiv2 = (_vertices[2].position - _vertices[1].position) /deux + _vertices[1].position;
    subDiv3 = (_vertices[0].position - _vertices[2].position) /deux + _vertices[2].position;

    glimac::ShapeVertex v1(glm::vec3(subDiv1),
                           glm::vec3(glm::normalize(subDiv1)),
                           glm::vec2(1,1)
    );


    glimac::ShapeVertex v2(glm::vec3(subDiv2),
                           glm::vec3(glm::normalize(subDiv2)),
                           glm::vec2(1,1)
    );

    glimac::ShapeVertex v3(glm::vec3(subDiv3),
                           glm::vec3(glm::normalize(subDiv3)),
                           glm::vec2(1,1)
    );

    std::vector<glimac::ShapeVertex> __vertices;

    __vertices.emplace_back(_vertices[0]);
    __vertices.emplace_back(v1);
    __vertices.emplace_back(v3);

    __vertices.emplace_back(v1);
    __vertices.emplace_back(v3);
    __vertices.emplace_back(v2);

    __vertices.emplace_back(v3);
    __vertices.emplace_back(v2);
    __vertices.emplace_back(_vertices[2]);

    __vertices.emplace_back(v2);
    __vertices.emplace_back(v1);
    __vertices.emplace_back(_vertices[1]);

    _vertices.clear();
    _vertices = __vertices;


}
/**
 *  getVertices()
 * @return all the vertices
 */
const std::vector<glimac::ShapeVertex> &ProceduralObject::getVertices() const {
    return vertices;
}
/**
 * getIndices()
 * @return all the indices
 */
const std::vector<uint32_t> &ProceduralObject::getIndices() const {
    return indices;
}







