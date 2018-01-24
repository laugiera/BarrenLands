//
// Created by natshez on 18/01/2018.
//

#include "CrystalRock.hpp"

CrystalRock::CrystalRock() : ProceduralRock(){
    generateVertices();
    generateIndices();
    generateNormals();
}

CrystalRock::~CrystalRock(){}

//to change after with his own vertices
void CrystalRock::generateVertices(){
    vertices.clear();

    std::vector<glimac::ShapeVertex> _vertices;

    /*
    for(int i = 0; i<4; i++){
        glm::vec3 randomVec(NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat());
        _vertices.push_back(glimac::ShapeVertex(
                glm::vec3(glm::normalize(randomVec)),
                glm::vec3(glm::normalize(randomVec)),
                glm::vec2(1,1)
        ));
    }
*/

    _vertices.emplace_back(glm::vec3(-0.2,-0.2,0), glm::vec3(0,0,0), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(0,-0.2,0.2), glm::vec3(0,0,0), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(-0.2,-0.2,0), glm::vec3(0,0,0), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(0, 4, 0), glm::vec3(0,0,0), glm::vec2(1,1));


    for(int i = 0; i<_vertices.size(); i++){
        center.x += _vertices[i].position.x / _vertices.size();
        center.y += _vertices[i].position.y / _vertices.size();
        center.z += _vertices[i].position.z /_vertices.size();
    }

    for(int i = 0; i<_vertices.size(); i++){
        glm::vec3 pos;
        if(glm::distance(_vertices[i].position, center) > 1){
            pos = glm::normalize(_vertices[i].position - center);
        } else {
            pos = _vertices[i].position - center;
        }
        center = glm::vec3(0,0,0);
        _vertices[i].position = center + pos;
        std::cout << "vertex : " << i << " : " << _vertices[i].position << std::endl;
    }

    std::cout << std::endl;


    //face1
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));

    //face2
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));

    //face3
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));

    //face4
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));

    subdivideObject(vertices, 4);
}
void CrystalRock::generateIndices(){
    indices.clear();
}
void CrystalRock::generateNormals(){
    ProceduralRock::generateNormals();
}

void CrystalRock::subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    //prend un vecteur de 3 vertices : une face
    glm::vec3 subDiv1, subDiv2, subDiv3, normal1, normal2, normal3;
    float deux = 2, quatre = 4;
    //prend les milieux de chaques cotés
    subDiv1 = (_vertices[1].position - _vertices[0].position) /deux + _vertices[0].position;
    subDiv2 = (_vertices[2].position - _vertices[1].position) /deux + _vertices[1].position;
    subDiv3 = (_vertices[0].position - _vertices[2].position) /deux + _vertices[2].position;

    //calcule les vecteurs allant du centre de l'object à ces nouveaux points
    normal1 = glm::normalize(subDiv1 - center);
    normal2 = glm::normalize(subDiv2 - center);
    normal3 = glm::normalize(subDiv3 - center);

    //pousse les nouveaux point le long des vecteurs trouvé précédemment jusqu'à ce qu'ils soint situés à une distance 1 du centre
    subDiv1 = subDiv1 + (normal1 - (subDiv1-center)) / (deux * nbRecurse);
    subDiv2 = subDiv2 + (normal2 - (subDiv2-center)) / (deux * nbRecurse);
    subDiv3 = subDiv3 + (normal3 - (subDiv3-center)) / (deux * nbRecurse);

    //crée des vertex à partir des nouveaux points
    glimac::ShapeVertex v1(glm::vec3(subDiv1),
                           glm::vec3(normal1),
                           glm::vec2(1,1)
    );

    glimac::ShapeVertex v2(glm::vec3(subDiv2),
                           glm::vec3(normal2),
                           glm::vec2(1,1)
    );

    glimac::ShapeVertex v3(glm::vec3(subDiv3),
                           glm::vec3(normal3),
                           glm::vec2(1,1)
    );

    //crée 4 faces pour remplacer le face d'origine
    std::vector<glimac::ShapeVertex> __vertices;

    __vertices.emplace_back(_vertices[0]);
    __vertices.emplace_back(v1);
    __vertices.emplace_back(v3);

    __vertices.emplace_back(v1);
    __vertices.emplace_back(v2);
    __vertices.emplace_back(v3);

    __vertices.emplace_back(v3);
    __vertices.emplace_back(v2);
    __vertices.emplace_back(_vertices[2]);

    __vertices.emplace_back(v2);
    __vertices.emplace_back(v1);
    __vertices.emplace_back(_vertices[1]);

    _vertices.clear();
    _vertices = __vertices;
}

Color *CrystalRock::chooseColor(Color *_color) {
    Color * alteredColor = new Color(_color);
    alteredColor->red(0.2);
    alteredColor->darken(0.3);
    return alteredColor;
}


