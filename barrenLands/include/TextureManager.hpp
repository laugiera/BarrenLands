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
/**
 * Class TextureManager
 * Create and manage all textures in the app
 */
class TextureManager {
public:
    TextureManager(const glimac::FilePath &appPath);

    void createTextures();

    void loadTextures(const std::string &folderPath);

    const std::vector<glcustom::Texture *> getTextures() const;

    glcustom::Texture * getRandomTexture(const std::string &qualifier);

private:
    glimac::FilePath appPath;

    std::map<glcustom::Texture *, std::string> textures;
};


#endif //BARRENLANDS_TEXTUREMANAGER_HPP
