//
// Created by Etienne on 31/01/2018.
//

//
// Created by natshez on 18/01/2018.
//

#include "Sapin.hpp"

Sapin::Sapin() : ProceduralFeuillage(){
    generateVertices();
    generateIndices();
    //position = glm::vec3(NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat());
    //position *= 3;
    //generateNormals();

}
Sapin::~Sapin(){}

void Sapin::generateVertices(){

    vertices.clear();

    std::vector<glimac::ShapeVertex> _vertices;


    _vertices.emplace_back(glm::normalize(glm::vec3(0,-1,0)), glm::normalize(glm::vec3(0,-1,0)), glm::vec2(1,1));

    _vertices.emplace_back(glm::vec3(cos(2*3.14/6),-1,sin(2*3.14/6)), glm::vec3(cos(2*3.14/6),-1,sin(2*3.14/6)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(4*3.14/6),-1,sin(4*3.14/6)), glm::vec3(cos(4*3.14/6),-1,sin(4*3.14/6)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(6*3.14/6),-1,sin(6*3.14/6)), glm::vec3(cos(6*3.14/6),-1,sin(6*3.14/6)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(8*3.14/6),-1,sin(8*3.14/6)), glm::vec3(cos(8*3.14/6),-1,sin(8*3.14/6)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(10*3.14/6),-1,sin(10*3.14/6)), glm::vec3(cos(10*3.14/6),-1,sin(10*3.14/6)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(12*3.14/6),-1,sin(12*3.14/6)), glm::vec3(cos(12*3.14/6),-1,sin(12*3.14/6)), glm::vec2(1,1));

    _vertices.emplace_back(glm::normalize(glm::vec3(0, 8, 0)), glm::normalize(glm::vec3(0, 4, 0)), glm::vec2(1,1));


    center = glm::vec3(0);

    //DISQUE
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));

    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));

    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));

    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));

    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));

    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));

    //CONE
    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));

    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));

    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));

    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));

    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));

    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));

}



void Sapin::addInstance(const glm::vec3 &position, const Color &biomeColor) {
    Color trueColor = chooseColor(biomeColor);
    glm::mat4 transfo(1.f);
    transfo =  getRandomScale() * getRandomRotation() * transfo;
    instances.push_back(new Instance(transfo, position,trueColor));
}




