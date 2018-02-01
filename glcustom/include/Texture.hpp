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
        Texture(const std::string filePath, const GLenum type = GL_TEXTURE_2D);

        Texture(GLsizei width, GLsizei height, const GLvoid * data, GLenum format);

        virtual ~Texture();

        void load2D(const std::string filePath);

        void create2D(GLsizei width, GLsizei height, const GLvoid * data, GLenum format);

        void bind(const GLenum type,GLenum textureUnit = GL_TEXTURE0);

        void debind(const GLenum type);

        GLuint getM_id() const;


        std::vector<glimac::Image *> loadSkyboxFile(const std::vector<std::string> filePath);
        void loadSkybox(const std::string texturePath);
        void setupCubeMap( const GLvoid *xpos, const GLvoid *xneg, const GLvoid *ypos, const GLvoid *yneg, const GLvoid *zpos, const GLvoid *zneg, GLsizei width, GLsizei height);
        /*
        void setParameter() -> do a functeur with gltexparameter function
        reprendre structure load;
        */
    };
}

#endif //BARRENLANDS_TEXTURE_HPP
