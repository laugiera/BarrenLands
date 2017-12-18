//
// Created by Lou Landry on 18/12/2017.
//
#define GLEW_STATIC
#ifndef BARRENLANDS_TEXTURE_HPP
#define BARRENLANDS_TEXTURE_HPP

#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <stdexcept>


namespace glcustom {

    class Texture {
    private:
        GLenum m_texture_unit;
        GLuint m_id;
    public:
        Texture(const std::string filePath);

        virtual ~Texture();

        void load(const std::string filePath);

        void bind(GLenum textureUnit = GL_TEXTURE0);

        void debind();
        /*
        void setParameter() -> do a functeur with gltexparameter function
        reprendre structure load;
        */
    };
}

#endif //BARRENLANDS_TEXTURE_HPP
