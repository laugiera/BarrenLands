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
}
void RoundRock::generateNormals(){}




