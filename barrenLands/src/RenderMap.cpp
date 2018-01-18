//
// Created by Lou Landry on 16/01/2018.
//

#include "RenderMap.hpp"

/**BIOMES COLORS**/
Color *RenderMap::sand = new Color(255.f/255.f, 255.f/255.f, 153.f/255.f);
Color *RenderMap::grass = new Color(153.f/255.f, 204.f/255.f, 0.f/255.f);
Color *RenderMap::toundra = new Color(168.f/255.f, 212.f/255.f, 206.f/255.f);
Color *RenderMap::snow = new Color(200.f/255.f, 250.f/255.f, 245.f/255.f);
Color *RenderMap::rock = new Color(150.f/255.f, 150.f/255.f, 150.f/255.f);
Color *RenderMap::savannah = new Color(255.f/255.f, 153.f/255.f, 0.f/255.f);

unsigned  int biomesNumber = 6;

RenderMap::RenderMap(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures) : RenderObject(program,
                                                                                                              _textures) {

}


void RenderMap::sendUniforms(const glm::mat4 &viewMatrix) {
    program->sendUniform1f("uSubDiv", Tools::nbSub);
    program->sendUniformArrayVec3("uColors",{

    },RenderMap::biomesNumber);
    RenderObject::sendUniforms(viewMatrix);
}
