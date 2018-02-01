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
    TextureManager();

    ~TextureManager(){
/*        for (std::map<glcustom::Texture *, std::string>::iterator i = textures.begin(); i != textures.end(); ++i) {
            delete (i);
        }*/
    }

    void createTextures();

    void loadTextures(const std::string &folderPath);

    const std::vector<glcustom::Texture *> getTextures() const;

    glcustom::Texture * getRandomTexture(const std::string &qualifier);

    void addTexture(glcustom::Texture * t, const std::string name);
    

private:
    std::map<glcustom::Texture *, std::string> textures;
};


#endif //BARRENLANDS_TEXTUREMANAGER_HPP
