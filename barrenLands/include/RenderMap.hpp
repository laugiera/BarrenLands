//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_RENDERMAP_HPP
#define BARRENLANDS_RENDERMAP_HPP

#include "RenderObject.hpp"
/**
 * Class RenderMap
 * Derived from RenderObject
 * Also manage biomes colors for the biomes created in the corresponding ProceduralMap class
 */
class RenderMap : public RenderObject{
public:
    RenderMap(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures);
    ~RenderMap(){
        delete RenderMap::sand;
        delete RenderMap::grass;
        delete RenderMap::toundra;
        delete RenderMap::snow;
        delete RenderMap::rock;
        delete RenderMap::savannah;

    }
    void render(const glm::mat4 &viewMatrix, const  std::vector<Instance*> &instances);
    void sendUniforms(const glm::mat4 &viewMatrix);


    /**BIOMES COLORS**/
    static Color *sand;
    static Color *grass;
    static Color *toundra;
    static Color *snow;
    static Color *rock;
    static Color *savannah;
    static unsigned  int biomesNumber;



};



#endif //BARRENLANDS_RENDERMAP_HPP
