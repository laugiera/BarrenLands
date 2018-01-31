//
// Created by natshez on 18/01/2018.
//

#include "SharpedRock.hpp"
#include <algorithm>

SharpedRock::SharpedRock() : ProceduralRock(){
    generateVertices();
    generateIndices();
    //position = glm::vec3(NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat());
    //position *= 3;
    generateNormals();

}
SharpedRock::~SharpedRock(){}
void SharpedRock::generateVertices(){

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

    _vertices.emplace_back(glm::vec3(2,-3,0), glm::vec3(1,-1,0), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(2*cos(2*3.14/3),-3,2*sin(2*3.14/3)),glm::vec3(cos(2*3.14/3),-1,sin(2*3.14/3)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(2*cos(-2*3.14/3),-3,2*sin(-2*3.14/3)), glm::vec3(cos(-2*3.14/3),-1,sin(-2*3.14/3)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(5*cos(2*3.14/3), 3, 5*sin(2*3.14/3)), glm::vec3(cos(2*3.14/3), 1, sin(2*3.14/3)), glm::vec2(1,1));


    /*for(int i = 0; i<_vertices.size(); i++){
        center.x += _vertices[i].position.x / _vertices.size();
        center.y += _vertices[i].position.y / _vertices.size();
        center.z += _vertices[i].position.z /_vertices.size();
    }*/

    center = glm::vec3(0);

    /*for(int i = 0; i<_vertices.size(); i++){
        glm::vec3 pos = glm::normalize(_vertices[i].position - center);
        _vertices[i].position = center + pos;
        //std::cout << "vertex : " << i << " : " << _vertices[i].position << std::endl;
    }*/

    //std::cout << std::endl;


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

    //subdivideObject(vertices, 3); //PLANTE QUI PIQUE
    subdivideObject(vertices, 3); //ANIMAL ETRANGE
    smooth(vertices, 1);

}
void SharpedRock::generateIndices(){
    indices.clear();
}
void SharpedRock::generateNormals() {
    ProceduralRock::generateNormals();
}


void SharpedRock::subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    if(nbRecurse <= 0){
        return;
    }

    int i = 0;

    /*RECUPERATION DES SUBDIVS + des indices des triangles*/
    i = 0;
    std::vector<glm::vec3> subdivs;
    std::vector<int> indice;
    glm::vec3 subDiv1, subDiv2, subDiv3;
    int nbrSub = 0;
    while(i<_vertices.size()){
        float deux = 2;
        subDiv1 = (_vertices[i+1].position + _vertices[i].position) /deux ;
        subDiv2 = (_vertices[i+2].position + _vertices[i+1].position) /deux ;
        subDiv3 = (_vertices[i].position + _vertices[i+2].position) /deux ;

        int pos1, pos2, pos3;

        pos1 = find(subdivs, subDiv1);
        pos2 = find(subdivs, subDiv2);
        pos3 = find(subdivs, subDiv3);

        if(pos1 == -1){
            subdivs.push_back(subDiv1);
            pos1 = nbrSub;
            ++nbrSub;
        }
        if(pos2 == -1){
            subdivs.push_back(subDiv2);
            pos2 = nbrSub;
            ++nbrSub;
        }
        if(pos3 == -1){
            subdivs.push_back(subDiv3);
            pos3 = nbrSub;
            ++nbrSub;
        }
        indice.push_back(pos1);
        indice.push_back(pos2);
        indice.push_back(pos3);

        i += 3;
    }

    //On déplace les subdivisions et on fait les ShapeVertex
    std::vector<glimac::ShapeVertex> subFinal;
    for(i=0; i< subdivs.size(); ++i){
        glm::vec3 normal = subdivs[i] - center;
        subdivs[i] = subdivs[i] + (normal)*float(NoiseManager::getInstance().getRandomFloat()/4+0.1) ; //FLOWER
        // subdivs[i] = subdivs[i] + (normal)*float(NoiseManager::getInstance().getRandomFloat()/4) ;
        glimac::ShapeVertex v1(glm::vec3(subdivs[i]),
                               glm::vec3(normal),
                               glm::vec2(1,1)
        );
        subFinal.emplace_back(v1);
    }
    std::vector<glimac::ShapeVertex> __vertices;
    //On refait tous les triangles proprement
    for(i=0; i<indice.size(); i+=3){
        __vertices.emplace_back(_vertices[i]);
        __vertices.emplace_back(subFinal[indice[i]]);
        __vertices.emplace_back(subFinal[indice[i+2]]);

        __vertices.emplace_back(subFinal[indice[i]]);
        __vertices.emplace_back(subFinal[indice[i+1]]);
        __vertices.emplace_back(subFinal[indice[i+2]]);

        __vertices.emplace_back(subFinal[indice[i]]);
        __vertices.emplace_back(_vertices[i+1]);
        __vertices.emplace_back(subFinal[indice[i+1]]);

        __vertices.emplace_back(subFinal[indice[i+1]]);
        __vertices.emplace_back(_vertices[i+2]);
        __vertices.emplace_back(subFinal[indice[i+2]]);
    }
    //std::cout << subdivs.size() << std::endl;
    //std::cout << indice.size() << std::endl;
    _vertices.clear();
    _vertices = __vertices;
    //_vertices = subdividedObject;
    subdivideObject(_vertices, nbRecurse-1);
}

Color *SharpedRock::chooseColor(Color *_color) {
    Color * alteredColor;
    if(_color == nullptr){
        alteredColor = new Color();
    }
    else{
        alteredColor = new Color(_color);
    }
    alteredColor->red(0.1);
    alteredColor->lighten(NoiseManager::getInstance().getRandomFloat()/10.f);
    //alteredColor->randomSimilarColor(0.1);
    return alteredColor;
}






int SharpedRock::find(std::vector<glm::vec3> &tab, glm::vec3 object){
    //Chercher un objet
    int i;
    for(i=0; i<tab.size(); ++i){
        if(tab[i] == object){
            return i;
        }
    }
    return -1;
}




void SharpedRock::smooth(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    if(nbRecurse <= 0){
        return;
    }

    int i = 0;

    /*RECUPERATION DES SUBDIVS + des indices des triangles*/
    i = 0;
    std::vector<glm::vec3> subdivs;
    std::vector<int> indice;
    glm::vec3 subDiv1, subDiv2, subDiv3;
    int nbrSub = 0;
    while(i<_vertices.size()){
        float deux = 2;
        subDiv1 = (_vertices[i+1].position + _vertices[i].position) /deux ;
        subDiv2 = (_vertices[i+2].position + _vertices[i+1].position) /deux ;
        subDiv3 = (_vertices[i].position + _vertices[i+2].position) /deux ;

        int pos1, pos2, pos3;

        pos1 = find(subdivs, subDiv1);
        pos2 = find(subdivs, subDiv2);
        pos3 = find(subdivs, subDiv3);

        if(pos1 == -1){
            subdivs.push_back(subDiv1);
            pos1 = nbrSub;
            ++nbrSub;
        }
        if(pos2 == -1){
            subdivs.push_back(subDiv2);
            pos2 = nbrSub;
            ++nbrSub;
        }
        if(pos3 == -1){
            subdivs.push_back(subDiv3);
            pos3 = nbrSub;
            ++nbrSub;
        }
        indice.push_back(pos1);
        indice.push_back(pos2);
        indice.push_back(pos3);

        i += 3;
    }

    //On déplace les subdivisions et on fait les ShapeVertex
    std::vector<glimac::ShapeVertex> subFinal;
    for(i=0; i< subdivs.size(); ++i){
        glm::vec3 normal = subdivs[i] - center;
        //subdivs[i] = subdivs[i] + (normal)*float(NoiseManager::getInstance().getRandomFloat()*0.001) ;
        subdivs[i] = subdivs[i] + (normal)*0.1f;    //0.1f*float(1/10*(3-nbRecurse)) ;
        glimac::ShapeVertex v1(glm::vec3(subdivs[i]),
                               glm::vec3(normal),
                               glm::vec2(1,1)
        );
        subFinal.emplace_back(v1);
    }
    std::vector<glimac::ShapeVertex> __vertices;
    //On refait tous les triangles proprement
    for(i=0; i<indice.size(); i+=3){
        _vertices[i].position = _vertices[i].position + _vertices[i].normal*0.05f;
        _vertices[i+1].position = _vertices[i+1].position + _vertices[i+1].normal*0.05f;
        _vertices[i+2].position = _vertices[i+2].position + _vertices[i+2].normal*0.05f;

        __vertices.emplace_back(_vertices[i]);
        __vertices.emplace_back(subFinal[indice[i]]);
        __vertices.emplace_back(subFinal[indice[i+2]]);

        __vertices.emplace_back(subFinal[indice[i]]);
        __vertices.emplace_back(subFinal[indice[i+1]]);
        __vertices.emplace_back(subFinal[indice[i+2]]);

        __vertices.emplace_back(subFinal[indice[i]]);
        __vertices.emplace_back(_vertices[i+1]);
        __vertices.emplace_back(subFinal[indice[i+1]]);

        __vertices.emplace_back(subFinal[indice[i+1]]);
        __vertices.emplace_back(_vertices[i+2]);
        __vertices.emplace_back(subFinal[indice[i+2]]);
    }
    //std::cout << subdivs.size() << std::endl;
    //std::cout << indice.size() << std::endl;
    _vertices.clear();
    _vertices = __vertices;
    //_vertices = subdividedObject;
    subdivideObject(_vertices, nbRecurse-1);
}


glm::mat4 SharpedRock::getRandomRotation() {
    return glm::rotate(glm::mat4(1.f), glm::radians(50*NoiseManager::getInstance().getRandomFloat()), glm::vec3(0,1,0));
}

glm::mat4 SharpedRock::getRandomScale() {
    return glm::scale(glm::mat4(1.f), glm::vec3(NoiseManager::getInstance().getRandomFloat()/5));
}