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

    _vertices.emplace_back(glm::vec3(1,-1,0), glm::normalize(glm::vec3(1,-1,0)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(0,-1,1), glm::normalize(glm::vec3(0,-1,1)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(-1,-1,0), glm::normalize(glm::vec3(-1,-1,0)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(0, 1, -1), glm::normalize(glm::vec3(0, 1, -1)), glm::vec2(1,1));

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


    std::vector<glimac::ShapeVertex> testVertices;

    std::vector<glimac::ShapeVertex>::iterator it = vertices.begin();

    int i = 0;
    while (i<vertices.size()){
        std::vector<glimac::ShapeVertex> face;
        for(int j = 0; j<3; j++){
            face.push_back(vertices[i]);
            i++;
        }
        subdivideFace(face);
        testVertices.insert(testVertices.end(), face.begin(), face.end());
    }
    /*

    std::vector<glimac::ShapeVertex> face;

    face.push_back(vertices[0]);
    face.push_back(vertices[1]);
    face.push_back(vertices[2]);
    subdivideFace(face);
    vertices.insert( vertices.end(), face.begin(), face.end());


    face.clear();
    face.push_back(vertices[3]);
    face.push_back(vertices[4]);
    face.push_back(vertices[5]);
    subdivideFace(face);

    vertices.insert( vertices.end(), face.begin(), face.end());

*/

    vertices = testVertices;


}
void RoundRock::generateIndices(){
    indices.clear();
    /*
    indices = {
            0,1,2,
            1,2,3,
            2,3,0,
            3,0,1
    };
     */
}
void RoundRock::generateNormals(){}

void RoundRock::subdivideFace(std::vector<glimac::ShapeVertex> &_vertices) { //prend un vecteur de 3 vertices

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


