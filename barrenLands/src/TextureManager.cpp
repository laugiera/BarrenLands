//
// Created by Lou Landry on 16/01/2018.
//

#include "TextureManager.hpp"
/**
 * Construtor
 * @param appPath
 */
TextureManager::TextureManager()  {
    createTextures();
    loadTextures(Tools::appPath + "textures/");

}
/**
 * createTextures
 */
void TextureManager::createTextures() {

    //skybox
    glcustom::Texture *  skybox = new glcustom::Texture( Tools::appPath + "textures",GL_TEXTURE_CUBE_MAP );
    textures[skybox]="skybox";

    glcustom::Texture *  menuSeed1 = new glcustom::Texture( Tools::appPath + "textures/menu/seed1.png",GL_TEXTURE_2D );
    glcustom::Texture *  menuSeed2 = new glcustom::Texture( Tools::appPath + "textures/menu/seed2.png",GL_TEXTURE_2D );
    glcustom::Texture *  menuSeed3 = new glcustom::Texture( Tools::appPath + "textures/menu/seed3.png",GL_TEXTURE_2D );

    textures[menuSeed1]="menuSeed1";
    textures[menuSeed2]="menuSeed2";
    textures[menuSeed3]="menuSeed3";

    glcustom::Texture *  menuPause1 = new glcustom::Texture( Tools::appPath + "textures/menu/menuPause1.png",GL_TEXTURE_2D );
    glcustom::Texture *  menuPause2 = new glcustom::Texture( Tools::appPath + "textures/menu/menuPause2.png",GL_TEXTURE_2D );
    glcustom::Texture *  menuPause3 = new glcustom::Texture( Tools::appPath + "textures/menu/menuPause3.png",GL_TEXTURE_2D );
    glcustom::Texture *  menuPause4 = new glcustom::Texture( Tools::appPath + "textures/menu/menuPause4.png",GL_TEXTURE_2D );

    textures[menuPause1]="menuPause1";
    textures[menuPause2]="menuPause2";
    textures[menuPause3]="menuPause3";
    textures[menuPause4]="menuPause4";

}
/**
 * addTextures
 */
void TextureManager::addTexture(glcustom::Texture * t, const std::string name){
    textures[t] = name;
}
/**
 * getTextures
 * @return std::vector<glcustom::Texture *>
 */
const std::vector<glcustom::Texture *> TextureManager::getTextures() const {
    std::vector<glcustom::Texture *> _textures;
    std::map<glcustom::Texture *, std::string>::const_iterator it;
    for(it = textures.begin(); it!=textures.end(); it++){
        _textures.push_back(it->first);
    }

    return _textures;
}
/**
 * loadTextures()
 * @param folderPath
 */
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
/**
 * getRandomTexture()
 * @param std::string qualifier / name
 * @return glcustom::Texture *
 */
glcustom::Texture * TextureManager::getRandomTexture(const std::string &qualifier) {
    std::vector<glcustom::Texture *> _textures;
    std::map<glcustom::Texture *, std::string>::const_iterator it;
    for(it = textures.begin(); it!=textures.end(); it++){
        if(it->second == qualifier){
            _textures.push_back(it->first);
        }
    }
    if(!_textures.empty()){
        int randomIndex = 0; //use noise to choose random int
        randomIndex = int (abs(NoiseManager::getInstance().getRandomFloat()*10)) % _textures.size();
        return _textures[randomIndex];
    }
    return nullptr;
}
