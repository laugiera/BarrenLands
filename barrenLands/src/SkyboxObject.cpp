#include <GPUProgram.hpp>

//
// Created by natshez on 17/01/2018.
//

//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/SkyboxObject.hpp"
/**
 * Constructor
 */
SkyboxObject::SkyboxObject() : ProceduralObject() {
    generateVertices();
    generateIndices();
}
/**
 * Destructor
 */
SkyboxObject::~SkyboxObject() {}
/**
 * createRenderObject()
 * Uses RenderSkybox with Skybox GPU Program
 * @param programManager
 * @param textureManager
 */
void SkyboxObject::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    renderObject = new RenderSkybox(programManager->getSkyboxProgram(), chooseTextures(textureManager));
    renderObject->fillData(vertices, indices);
}
/**
 * chooseTextures()
 * Redefined to get skybox texture
 * @param textureManager
 * @return std::vector<glcustom::Texture *>
 */
std::vector<glcustom::Texture *> SkyboxObject::chooseTextures(TextureManager *textureManager) {
    std::vector<glcustom::Texture *> textures;
    textures.push_back(textureManager->getRandomTexture("skybox"));
    return textures;
}
/**
 * draw()
 * applies transformation to place the skybox and render it
 * @param glm::mat4 viewMatrix
 */
void SkyboxObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0,0,-5), 0, glm::vec3(0,1,0), glm::vec3(100,100,100));
    renderObject->render(viewMatrix);
}


