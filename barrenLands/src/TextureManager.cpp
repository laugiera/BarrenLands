//
// Created by Lou Landry on 16/01/2018.
//

#include "TextureManager.hpp"

TextureManager::TextureManager(const glimac::FilePath &appPath) : appPath(appPath) {
    //createTextures();
}

void TextureManager::createTextures() {
    glcustom::Texture *  test_texture1 = new glcustom::Texture(
            appPath.dirPath() + "textures/" + "HatchPattern-final.png");
    glcustom::Texture * test_texture2 = new glcustom::Texture(appPath.dirPath() + "textures/" + "653306852.jpg");
    textures.push_back(test_texture1);
    textures.push_back(test_texture2);

    glcustom::Texture *  skybox = new glcustom::Texture( appPath.dirPath() + "textures",GL_TEXTURE_CUBE_MAP );
    textures.push_back(skybox);

    //moisture map
    NoiseManager noise(1200);
    float** humidite = noise.getElevationMap(Tools::nbSub +1, Tools::nbSub +1);
    std::vector<float> moistureVector;
    for(int i = 0; i < Tools::nbSub +1; i++){
        for(int j = 0 ; j < Tools::nbSub +1; j++){
            moistureVector.push_back(humidite[i][j]);
        }
    }
    glcustom::Texture * moisture = new glcustom::Texture(Tools::nbSub +1, Tools::nbSub +1, moistureVector.data(), GL_RED);
    textures.push_back(moisture);
}

const std::vector<glcustom::Texture *> &TextureManager::getTextures() const {
    return textures;
}

glcustom::Texture* TextureManager::getSkyboxTexture(){
    return textures[2];
}
