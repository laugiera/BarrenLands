//
// Created by natshez on 17/01/2018.
//

#include "CubeMapTexture.hpp"
#define  GLEW_STATIC

bool CubemapTexture::Load()
{
    glGenTextures(1, &m_textureObj);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    std::string texturePath;

    std::unique_ptr<glimac::Image> temp = nullptr;
    glimac::Image * img = nullptr;
    std::vector<GLenum> types = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    for (unsigned int i = 0 ; i < types.size() ; i++) {
        temp = glimac::loadImage(texturePath+m_fileNames[i]);
        img = temp.get();
        if(!temp)
            throw std::runtime_error("Texture failed to load");

        glTexImage2D(types[i], 0, GL_RGB,img->getWidth() ,img->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img->getPixels());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    }
    delete img;

    return true;
}

void CubemapTexture::Bind(GLenum TextureUnit)
{
//    glActiveTexture(TextureUnit);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}

CubemapTexture::CubemapTexture(const std::string& Directory,
               const std::string& PosXFilename,
               const std::string& NegXFilename,
               const std::string& PosYFilename,
               const std::string& NegYFilename,
               const std::string& PosZFilename,
               const std::string& NegZFilename){
    m_fileNames[0]=PosXFilename;
    m_fileNames[1]=NegXFilename;
    m_fileNames[2]=PosYFilename;
    m_fileNames[3]=NegYFilename;
    m_fileNames[4]=PosZFilename;
    m_fileNames[5]=NegZFilename;
}

