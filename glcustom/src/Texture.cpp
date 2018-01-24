//
// Created by Lou Landry on 18/12/2017.
//

#include "Texture.hpp"
#include <iostream>

glcustom::Texture::Texture(const std::string filePath, const GLenum type) : m_texture_unit(GL_TEXTURE0), m_id() {
    try{
        if(type == GL_TEXTURE_CUBE_MAP)
            loadSkybox(filePath);
        else if (type == GL_TEXTURE_2D)
            load2D(filePath);
    } catch (std::runtime_error &e){
        e.what();
    }
}

glcustom::Texture::Texture(GLsizei width, GLsizei height, const GLvoid *data, GLenum format) : m_texture_unit(GL_TEXTURE0), m_id() {
    create2D(width, height, data, format);
}

glcustom::Texture::~Texture() {

}

void glcustom::Texture::load2D(const std::string filePath) {
    std::unique_ptr<glimac::Image> img = glimac::loadImage(filePath);
    if(!img) {
        throw std::runtime_error("Texture failed to load");
    }
    glGenTextures(1, &m_id);
    bind(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    debind(GL_TEXTURE_2D);


}

std::vector< glimac::Image*> glcustom::Texture::loadSkyboxFile(const std::vector<std::string> filePath){
    std::vector< glimac::Image*> images;
    std::unique_ptr<glimac::Image> image;
    for (int i = 0; i < filePath.size(); ++i) {
        image = glimac::loadImage(filePath[i]);
        if(!image) {
            throw std::runtime_error("Texture failed to load");
        }
        images.push_back(image.get());
    }
    return images;
}

void glcustom::Texture::loadSkybox(const std::string texturePath) {
        // generate a cube-map texture to hold all the sides
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &m_id);
        bind(GL_TEXTURE_CUBE_MAP);

        std::unique_ptr<glimac::Image> xneg,xpos,yneg,ypos,zneg,zpos;
        xneg = glimac::loadImage(texturePath+"/xneg.jpg");
        if(!xneg)
            throw std::runtime_error("Texture failed to load");
        xpos = glimac::loadImage(texturePath+"/xpos.jpg");
        if(!xpos)
            throw std::runtime_error("Texture failed to load");
        yneg = glimac::loadImage(texturePath+"/yneg.jpg");
        if(!yneg)
            throw std::runtime_error("Texture failed to load");
        ypos = glimac::loadImage(texturePath+"/ypos.jpg");
        if(!ypos)
            throw std::runtime_error("Texture failed to load");
        zpos = glimac::loadImage(texturePath+"/zpos.jpg");
        if(!zpos)
            throw std::runtime_error("Texture failed to load");
        zneg = glimac::loadImage(texturePath+"/zneg.jpg");
        if(!zneg)
            throw std::runtime_error("Texture failed to load");


        setupCubeMap(xpos->getPixels(),xneg->getPixels(),ypos->getPixels(),yneg->getPixels(),
                     zpos->getPixels(),zneg->getPixels(),xpos->getWidth(),xpos->getHeight());
        // format cube map texture
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        debind(GL_TEXTURE_CUBE_MAP);

}

void glcustom::Texture::setupCubeMap( const GLvoid *xpos, const GLvoid *xneg, const GLvoid *ypos, const GLvoid *yneg, const GLvoid *zpos, const GLvoid *zneg, GLsizei width, GLsizei height) {

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, xpos);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, xneg);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, ypos);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, yneg);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, zpos);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, zneg);
}

void glcustom::Texture::create2D(GLsizei width, GLsizei height, const GLvoid * data, GLenum format) {
    glGenTextures(1, &m_id);
    bind(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    debind(GL_TEXTURE_2D);

}

void glcustom::Texture::bind(const GLenum type, GLenum textureUnit) {
    m_texture_unit = textureUnit;
    glActiveTexture(m_texture_unit);
    glBindTexture(type, m_id);
}

void glcustom::Texture::debind(const GLenum type) {
    glActiveTexture(m_texture_unit);
    glBindTexture(type, 0);
}

GLuint glcustom::Texture::getM_id() const {
    return m_id;
}


