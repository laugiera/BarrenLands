//
// Created by natshez on 18/01/2018.
//

#include "FlatRock.hpp"

FlatRock::FlatRock() : ProceduralRock(){}
FlatRock::~FlatRock(){}
//to change after with his own vertices
void FlatRock::generateVertices(){
    ProceduralObject::generateVertices();
}
void FlatRock::generateIndices(){
    ProceduralObject::generateIndices();
}
void FlatRock::generateNormals(){
    ProceduralObject::generateNormals();
}

