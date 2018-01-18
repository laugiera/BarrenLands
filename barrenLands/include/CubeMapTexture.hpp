//
// Created by natshez on 17/01/2018.
//
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glimac/Image.hpp>

#ifndef BARRENLANDS_CUBEMAPTEXTURE_H
#define BARRENLANDS_CUBEMAPTEXTURE_H
class CubemapTexture
{
public:

    CubemapTexture(const std::string& Directory,
                   const std::string& PosXFilename,
                   const std::string& NegXFilename,
                   const std::string& PosYFilename,
                   const std::string& NegYFilename,
                   const std::string& PosZFilename,
                   const std::string& NegZFilename);


    bool Load();

    void Bind(GLenum TextureUnit);

private:

    std::string m_fileNames[6];
    GLuint m_textureObj;
};
#endif //BARRENLANDS_CUBEMAPTEXTURE_H
