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

        Texture(GLsizei width, GLsizei height, const GLvoid * data, GLenum format);

        virtual ~Texture();

        void load(const std::string filePath);

        void create2D(GLsizei width, GLsizei height, const GLvoid * data, GLenum format);

        void bind(GLenum textureUnit = GL_TEXTURE0);

        void debind();

        GLuint getM_id() const;
        /*
        void setParameter() -> do a functeur with gltexparameter function
        reprendre structure load;
        */
    };
}

#endif //BARRENLANDS_TEXTURE_HPP
