//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_TEXTUREMANAGER_HPP
#define BARRENLANDS_TEXTUREMANAGER_HPP

#include "glimac/FilePath.hpp"
#include "Texture.hpp"
#include "Tools.hpp"
#include "NoiseManager.hpp"

class TextureManager {
public:
    TextureManager(const glimac::FilePath &appPath);
    void createTextures(); //modif pour passer par la lecture d'un fichier avec infos sur textures

    const std::vector<glcustom::Texture *> &getTextures() const;

    //à impémenter, renvoie une texture random dont un des qualificatif est la string demandée (les qualificatif seront fournis lors de l'initialisation par le fichier d'initialisation)
    void getRandomTexture(const std::string & qualifier);

    glcustom::Texture* getSkyboxTexture();

private:
    glimac::FilePath appPath;
    std::vector<glcustom::Texture*> textures;
};


#endif //BARRENLANDS_TEXTUREMANAGER_HPP
