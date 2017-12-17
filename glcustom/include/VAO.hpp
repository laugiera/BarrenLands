//
// Created by Lou Landry on 16/12/2017.
//
#define GLEW_STATIC
#ifndef BARRENLANDS_VAO_HPP
#define BARRENLANDS_VAO_HPP

#include <Buffer.hpp>
#include <VBO.hpp>
#include <IBO.hpp>
#include <vector>


namespace glcustom {

    class VAO : public Buffer {
    public:
        VAO();

        virtual ~VAO();

        template <typename type>
        void fillBuffer(const std::vector<type> &vertices, VBO *vbo , IBO *ibo = nullptr) {
            bind();
            if(ibo){
                std::cout << "ibo binded";
                ibo->bind();
            }
            //activate properties
            /*
            idea to automate that : pass as a parameter the gpuprogram with new attributs m_activated_attributs
            also get attribut pointer to content from vbo to get the type and not have to pass vertices
             */
            const GLuint VERTEX_ATTR_POSITION = 0;
            const GLuint VERTEX_ATTR_NORMAL = 1;
            const GLuint VERTEX_ATTR_TEXTURE = 2;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
            vbo->bind();
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*)offsetof(type, position));
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*)offsetof(type, normal));
            glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*)offsetof(type, texCoords));
            vbo->debind();
            /*
            if(ibo){ibo->debind();}
             */
            debind();
        }

        void bind();

        void debind();

        GLuint getM_id() const;
    };
}

#endif //BARRENLANDS_VAO_HPP
