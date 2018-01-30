//
// Created by Lou Landry on 29/01/2018.
//

#include <Texture.hpp>
#include "FBO.hpp"

glcustom::FBO::FBO() {
    glGenFramebuffers(1,&m_id);
}

glcustom::FBO::~FBO() {
    glDeleteFramebuffers(1, &m_id);
}

void glcustom::FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void glcustom::FBO::debind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

glcustom::Texture glcustom::FBO::attachColorTexture(float width, float height) {
    glcustom::Texture originalColor = glcustom::Texture(width, height, nullptr , GL_RGB);
    originalColor.bind(GL_TEXTURE_2D);
    glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, originalColor.getM_id(), 0
    );
    return originalColor;
}

glcustom::Texture glcustom::FBO::attachDepthTexture(float width, float height) {
    glcustom::Texture originalDepth = glcustom::Texture(width, height, nullptr , GL_DEPTH_COMPONENT);
    originalDepth.bind(GL_TEXTURE_2D);
    glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, originalDepth.getM_id(), 0
    );
    return originalDepth;
}

void glcustom::FBO::checkComplete() {
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "framebuffer instancing failed " << std::endl;
    }
}

void glcustom::FBO::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


