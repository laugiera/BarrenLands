//
// Created by natshez on 18/01/2018.
//

#include "RoundRock.hpp"

RoundRock::RoundRock() : ProceduralRock(){
    generateVertices();
    generateIndices();
}
RoundRock::~RoundRock(){}
void RoundRock::generateVertices(){

    vertices.clear();

    std::vector<glimac::ShapeVertex> _vertices;


    for(int i = 0; i<4; i++){
        glm::vec3 randomVec(NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat());
        _vertices.push_back(glimac::ShapeVertex(
                glm::vec3(glm::normalize(randomVec)),
                glm::vec3(glm::normalize(randomVec)),
                glm::vec2(1,1)
        ));
    }

    /*
    _vertices.emplace_back(glm::normalize(glm::vec3(1,-1,0)), glm::normalize(glm::vec3(1,-1,0)), glm::vec2(1,1)NoiseManager::getInstance().getRandomFloat());
    _vertices.emplace_back(glm::normalize(glm::vec3(0,-1,1)), glm::normalize(glm::vec3(0,-1,1)), glm::vec2(1,1));
    _vertices.emplace_back(glm::normalize(glm::vec3(-1,-1,0)), glm::normalize(glm::vec3(-1,-1,0)), glm::vec2(1,1));
    _vertices.emplace_back(glm::normalize(glm::vec3(0, 1, -1)), glm::normalize(glm::vec3(0, 1, -1)), glm::vec2(1,1));
    */

    for(int i = 0; i<4; i++){
        NoiseManager::getInstance().getRandomFloat();
        center.x += _vertices[i].position.x / 4;
        center.y += _vertices[i].position.y / 4;
        center.z += _vertices[i].position.z /4;
    }

    generateNormals();

    //face1
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));

    //face2
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));

    //face3
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));

    //face4
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));

    subdivideObject(vertices, 2);


}
void RoundRock::generateIndices(){
    indices.clear();
}
void RoundRock::generateNormals() {
    for(int i = 0; i< vertices.size(); i++){
        vertices[i]. normal = glm::normalize(vertices[i].position - center);
    }
}

void RoundRock::subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    //prend un vecteur de 3 vertices
    glm::vec3 subDiv1, subDiv2, subDiv3, normal1, normal2, normal3;
    float deux = 2;
    subDiv1 = (_vertices[1].position - _vertices[0].position) /deux + _vertices[0].position;
    subDiv2 = (_vertices[2].position - _vertices[1].position) /deux + _vertices[1].position;
    subDiv3 = (_vertices[0].position - _vertices[2].position) /deux + _vertices[2].position;

    normal1 = glm::normalize(subDiv1 - center);
    normal2 = glm::normalize(subDiv2 - center);
    normal3 = glm::normalize(subDiv3 - center);

    subDiv1 = subDiv1 + (normal1-subDiv1) / deux;
    subDiv2 = subDiv2 + (normal2-subDiv2) / deux;
    subDiv3 = subDiv3 + (normal3-subDiv3) / deux;


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




