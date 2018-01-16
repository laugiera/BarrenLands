//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALMAP_HPP
#define BARRENLANDS_PROCEDURALMAP_HPP

#include "ProceduralObject.hpp"
#include "NoiseManager.hpp"

class ProceduralMap : public ProceduralObject{
public:
    ProceduralMap(NoiseManager *noise);
    void generateVertices(NoiseManager *noise);
    void generateIndices();
private:
    std::vector<glcustom::Texture*> textures;

};


#endif //BARRENLANDS_PROCEDURALMAP_HPP
