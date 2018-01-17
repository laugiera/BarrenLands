//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_TEXTUREMANAGER_HPP
#define BARRENLANDS_TEXTUREMANAGER_HPP

#include "glimac/FilePath.hpp"
#include "Texture.hpp"
#include "Tools.hpp"
#include "NoiseManager.hpp"
#include <map>

class TextureManager {
public:
    TextureManager(const glimac::FilePath &appPath);
    void createTextures(); //modif pour passer par la lecture d'un fichier avec infos sur textures

    const std::vector<glcustom::Texture *> getTextures() const;

    //à impémenter, renvoie une texture random dont un des qualificatif est la string demandée (les qualificatif seront fournis lors de l'initialisation par le fichier d'initialisation)
    glcustom::Texture * getRandomTexture(const std::string &qualifier);

    void loadTextures(const std::string &folderPath);

private:
    glimac::FilePath appPath;
    //std::vector<glcustom::Texture*> textures;
    std::map<glcustom::Texture *, std::string> textures;
};


#endif //BARRENLANDS_TEXTUREMANAGER_HPP
