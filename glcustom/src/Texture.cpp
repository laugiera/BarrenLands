//
// Created by Lou Landry on 18/12/2017.
//

#include "Texture.hpp"

glcustom::Texture::Texture(const std::string filePath) : m_texture_unit(GL_TEXTURE0), m_id() {
    try{
        load(filePath);
    } catch (std::runtime_error &e){
        e.what();
    }
}

glcustom::Texture::~Texture() {

}

void glcustom::Texture::load(const std::string filePath) {
    std::unique_ptr<glimac::Image> img = glimac::loadImage(filePath);
    if(!img) {
        throw std::runtime_error("Texture failed to load");
    }
    glGenTextures(1, &m_id);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    debind();

}

void glcustom::Texture::bind(GLenum textureUnit) {
    m_texture_unit = textureUnit;
    glActiveTexture(m_texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void glcustom::Texture::debind() {
    glActiveTexture(m_texture_unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}


