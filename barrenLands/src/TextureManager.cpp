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
}

const std::vector<glcustom::Texture *> &TextureManager::getTextures() const {
    return textures;
}
