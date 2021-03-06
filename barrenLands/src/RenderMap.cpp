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


unsigned  int RenderMap::biomesNumber = 6;

/**
 * Constructor
 * @param program
 * @param _textures
 */
RenderMap::RenderMap(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures) : RenderObject(program,
                                                                                                              _textures) {

}
/**
 * Uniforms
 * Redefined with map uniforms
 * @param viewMatrix
 */
void RenderMap::sendUniforms(const glm::mat4 &viewMatrix) {
    glm::vec3 colors[] = {
                    sand->getVec3(),
                    grass->getVec3(),
                    toundra->getVec3(),
                    snow->getVec3(),
                    rock->getVec3(),
                    savannah->getVec3()
    };
    program->sendUniform1f("uSubDiv", Tools::nbSub);
    program->sendUniformArrayVec3("uColors",colors,RenderMap::biomesNumber);

    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = Tools::projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));

    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);
    program->sendUniformMat4("uNormal", normals);
}

/**
* render()
* render the object by using it's own GPU Program, sending it's own uniforms and binding it's own textures
* @param viewMatrix
*/
void RenderMap::render(const glm::mat4 &viewMatrix, const  std::vector<Instance*> &instances) {
    program->use();
    bindTextures();
    vao.bind();
    sendUniforms(viewMatrix);
    if(indices.empty()){
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    } else {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    vao.debind();
    debindTextures();

}


