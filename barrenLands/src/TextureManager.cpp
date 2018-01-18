//
// Created by Lou Landry on 16/01/2018.
//

#include "TextureManager.hpp"

TextureManager::TextureManager(const glimac::FilePath &appPath) : appPath(appPath) {
    createTextures();
    loadTextures(appPath.dirPath() + "textures/");

}

void TextureManager::createTextures() {


    glcustom::Texture *  skybox = new glcustom::Texture( appPath.dirPath() + "textures",GL_TEXTURE_CUBE_MAP );
    textures[skybox]="skybox";

    //moisture map
    float** humidite = NoiseManager::getInstance().getElevationMap(Tools::nbSub +1, Tools::nbSub +1);
    std::vector<float> moistureVector;
    for(int i = 0; i < Tools::nbSub +1; i++){
        for(int j = 0 ; j < Tools::nbSub +1; j++){
            moistureVector.push_back(humidite[i][j]);
        }
    }
    glcustom::Texture * moisture = new glcustom::Texture(Tools::nbSub +1, Tools::nbSub +1, moistureVector.data(), GL_RED);
    textures[moisture] = "moisture";
}

const std::vector<glcustom::Texture *> TextureManager::getTextures() const {
    std::vector<glcustom::Texture *> _textures;
    std::map<glcustom::Texture *, std::string>::const_iterator it;
    for(it = textures.begin(); it!=textures.end(); it++){
        _textures.push_back(it->first);
    }

    return _textures;
}

void TextureManager::loadTextures(const std::string &folderPath) {
    std::string filePath = folderPath + "/textures.txt";
    try {
        std::vector<std::string> lines = Tools::load(filePath);
        for (std::string &line : lines) {
            std::vector<std::string> data = Tools::stringToVector(line, ";");
            glcustom::Texture *texture = new glcustom::Texture(folderPath + "/" + data[0]);
            textures[texture] = Tools::sanitizeInput(data[1]);

        }
    } catch (std::exception * e){
        std::cerr << "loading of textures failed : " << e->what() << std::endl;
    }
}

glcustom::Texture * TextureManager::getRandomTexture(const std::string &qualifier) {
    std::vector<glcustom::Texture *> _textures;
    std::map<glcustom::Texture *, std::string>::const_iterator it;
    for(it = textures.begin(); it!=textures.end(); it++){
        if(it->second == qualifier){
            _textures.push_back(it->first);
        }
    }
    if(_textures.empty()){
        int randomIndex = 0; //use noise to choose random int
        return _textures[randomIndex];
    }
    return _textures[0];
}
