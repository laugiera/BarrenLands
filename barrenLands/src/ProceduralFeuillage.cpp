//
// Created by natshez on 18/01/2018.
//

#include "ProceduralFeuillage.hpp"

ProceduralFeuillage::ProceduralFeuillage() : ProceduralObject(){
    generateVertices();
    generateIndices();
    //position = glm::vec3(NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat(), NoiseManager::getInstance().getRandomFloat());
    //position *= 3;
    generateNormals();

}
ProceduralFeuillage::~ProceduralFeuillage(){}

void ProceduralFeuillage::generateVertices(){

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

    _vertices.emplace_back(glm::vec3(0,-1,0), glm::vec3(0,-1,0), glm::vec2(1,1));
    //_vertices.emplace_back(glm::vec3(cos(2*3.14/3),-1,sin(2*3.14/3)),glm::vec3(cos(2*3.14/3),-1,sin(2*3.14/3)), glm::vec2(1,1));
    //_vertices.emplace_back(glm::vec3(cos(-2*3.14/3),-1,sin(-2*3.14/3)), glm::vec3(cos(-2*3.14/3),-1,sin(-2*3.14/3)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(0 + 2*3.14/10),-0.5,sin(0 + 2*3.14/10)), glm::vec3(cos(0 + 2*3.14/10),-0.5,sin(0 + 2*3.14/10)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(2*3.14/5 + 2*3.14/10),-0.5,sin(2*3.14/5 + 2*3.14/10)), glm::vec3(cos(2*3.14/5 + 2*3.14/10),-0.5,sin(2*3.14/5 + 2*3.14/10)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(4*3.14/5 + 2*3.14/10),-0.5,sin(4*3.14/5 + 2*3.14/10)), glm::vec3(cos(4*3.14/5 + 2*3.14/10),-0.5,sin(4*3.14/5 + 2*3.14/10)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(6*3.14/5 + 2*3.14/10),-0.5,sin(6*3.14/5 + 2*3.14/10)), glm::vec3(cos(6*3.14/5 + 2*3.14/10),-0.5,sin(6*3.14/5 + 2*3.14/10)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(8*3.14/5 + 2*3.14/10),-0.5,sin(8*3.14/5 + 2*3.14/10)), glm::vec3(cos(8*3.14/5 + 2*3.14/10),-0.5,sin(8*3.14/5 + 2*3.14/10)), glm::vec2(1,1));

    _vertices.emplace_back(glm::vec3(cos(0),0.7,sin(0)), glm::vec3(cos(0),0.5,sin(0)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(2*3.14/5),0.7,sin(2*3.14/5)), glm::vec3(cos(2*3.14/5),0.5,sin(2*3.14/5)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(4*3.14/5),0.7,sin(4*3.14/5)), glm::vec3(cos(4*3.14/5),0.5,sin(4*3.14/5)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(6*3.14/5),0.7,sin(6*3.14/5)), glm::vec3(cos(6*3.14/5),0.5,sin(6*3.14/5)), glm::vec2(1,1));
    _vertices.emplace_back(glm::vec3(cos(8*3.14/5),0.7,sin(8*3.14/5)), glm::vec3(cos(8*3.14/5),0.5,sin(8*3.14/5)), glm::vec2(1,1));

    _vertices.emplace_back(glm::vec3(0, 1.5, 0), glm::vec3(0, 2, 0), glm::vec2(1,1));

    center = glm::vec3(0);
    /*for(int i = 0; i<_vertices.size(); i++){
        center.x += _vertices[i].position.x / _vertices.size();
        center.y += _vertices[i].position.y / _vertices.size();
        center.z += _vertices[i].position.z /_vertices.size();
    }*/

    /*for(int i = 0; i<_vertices.size(); i++){
        glm::vec3 pos = glm::normalize(_vertices[i].position - center);
        _vertices[i].position = center + pos;
        //std::cout << "vertex : " << i << " : " << _vertices[i].position << std::endl;
    }*/

    //std::cout << std::endl;

    /////BAS
    //face1
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));

    //face2
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));

    //face3
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));

    //face4
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));

    //face5
    vertices.push_back(glimac::ShapeVertex(_vertices[0]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));

    /////HAUT
    //face1
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));
    vertices.push_back(glimac::ShapeVertex(_vertices[11]));
    vertices.push_back(glimac::ShapeVertex(_vertices[7]));

    //face2
    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[11]));
    vertices.push_back(glimac::ShapeVertex(_vertices[8]));

    //face3
    vertices.push_back(glimac::ShapeVertex(_vertices[8]));
    vertices.push_back(glimac::ShapeVertex(_vertices[11]));
    vertices.push_back(glimac::ShapeVertex(_vertices[9]));

    //face4
    vertices.push_back(glimac::ShapeVertex(_vertices[9]));
    vertices.push_back(glimac::ShapeVertex(_vertices[11]));
    vertices.push_back(glimac::ShapeVertex(_vertices[10]));

    //face5
    vertices.push_back(glimac::ShapeVertex(_vertices[10]));
    vertices.push_back(glimac::ShapeVertex(_vertices[11]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));


    /////CONTOURHAUT
    //face1
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));

    //face2
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[8]));
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));

    //face3
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[9]));
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));

    //face4
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));
    vertices.push_back(glimac::ShapeVertex(_vertices[10]));
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));

    //face5
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));


    /////CONTOURBAS
    //face1
    vertices.push_back(glimac::ShapeVertex(_vertices[1]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));
    vertices.push_back(glimac::ShapeVertex(_vertices[7]));

    //face2
    vertices.push_back(glimac::ShapeVertex(_vertices[2]));
    vertices.push_back(glimac::ShapeVertex(_vertices[7]));
    vertices.push_back(glimac::ShapeVertex(_vertices[8]));

    //face3
    vertices.push_back(glimac::ShapeVertex(_vertices[3]));
    vertices.push_back(glimac::ShapeVertex(_vertices[8]));
    vertices.push_back(glimac::ShapeVertex(_vertices[9]));

    //face4
    vertices.push_back(glimac::ShapeVertex(_vertices[4]));
    vertices.push_back(glimac::ShapeVertex(_vertices[9]));
    vertices.push_back(glimac::ShapeVertex(_vertices[10]));

    //face5
    vertices.push_back(glimac::ShapeVertex(_vertices[5]));
    vertices.push_back(glimac::ShapeVertex(_vertices[10]));
    vertices.push_back(glimac::ShapeVertex(_vertices[6]));

    subdivideObject(vertices, 2);
    smooth(vertices, 3);
}
void ProceduralFeuillage::generateIndices(){
    indices.clear();
}
void ProceduralFeuillage::generateNormals() {
    //ProceduralRock::generateNormals();
}

void ProceduralFeuillage::subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    //prend un vecteur de 3 vertices : une face
    glm::vec3 subDiv1, subDiv2, subDiv3, normal1, normal2, normal3;
    float deux = 2;
    //prend les milieux de chaques cotés
    subDiv1 = (_vertices[1].position - _vertices[0].position) /deux + _vertices[0].position;
    subDiv2 = (_vertices[2].position - _vertices[1].position) /deux + _vertices[1].position;
    subDiv3 = (_vertices[0].position - _vertices[2].position) /deux + _vertices[2].position;

    //calcule les vecteurs allant du centre de l'object à ces nouveaux points
    normal1 = glm::normalize(subDiv1 - center);
    normal2 = glm::normalize(subDiv2 - center);
    normal3 = glm::normalize(subDiv3 - center);

    //pousse les nouveaux point le long des vecteurs trouvé précédemment jusqu'à ce qu'ils soint situés à une distance 1 du centre
    subDiv1 = subDiv1 + (normal1 - (subDiv1-center)) / deux;
    subDiv2 = subDiv2 + (normal2 - (subDiv2-center)) / deux;
    subDiv3 = subDiv3 + (normal3 - (subDiv3-center)) / deux;

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

void ProceduralFeuillage::subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
    if(nbRecurse <= 0){
        return;
    }

    int i = 0;

    //RECUPERATION DES SUBDIVS + des indices des triangles
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

glm::vec3 ProceduralFeuillage::getRandomPosition(const glm::vec3 &position) {
    return position;
}

glm::mat4 ProceduralFeuillage::getRandomRotation() {
    return glm::rotate(glm::mat4(1.f), glm::radians(180*NoiseManager::getInstance().getRandomFloat()), glm::vec3(1,1,0));
}


glm::mat4 ProceduralFeuillage::getRandomScale() {
    return glm::scale(glm::mat4(1.f), glm::vec3(0.7+0.3*NoiseManager::getInstance().getRandomFloat(),0.7+0.3*NoiseManager::getInstance().getRandomFloat(),0.7+0.3*NoiseManager::getInstance().getRandomFloat()));
}

/**
 * Adds a instance of an object
 * Adds its position and color to the positions and colors attributs after having modified them
 * @param position
 * @param biomeColor
 */
void ProceduralFeuillage::addInstance(const glm::vec3 &position, const Color &biomeColor) {
    Color trueColor = chooseColor(biomeColor);
    glm::mat4 transfo(1.f);
    transfo =  getRandomScale() * getRandomRotation() * transfo;
    instances.push_back(new Instance(transfo, position,trueColor));
}


int ProceduralFeuillage::find(std::vector<glm::vec3> &tab, glm::vec3 object){
    //Chercher un objet
    int i;
    for(i=0; i<tab.size(); ++i){
        if(tab[i] == object){
            return i;
        }
    }
    return -1;
}




void ProceduralFeuillage::smooth(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse) {
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
        subdivs[i] = subdivs[i] + (normal)*0.05f;    //0.1f*float(1/10*(3-nbRecurse)) ;
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
    smooth(_vertices, nbRecurse-1);
}





