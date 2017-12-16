//
// Created by Lou Landry on 16/12/2017.
//

#ifndef BARRENLANDS_VAO_HPP
#define BARRENLANDS_VAO_HPP

#include <Buffer.hpp>
#include <VBO.hpp>
#include <vector>


namespace glcustom {

    class VAO : public Buffer {
    public:
        VAO();

        virtual ~VAO();

        template <typename type>
        void fillBuffer(const std::vector<type> &vertices, VBO &vbo /*, IBO &ibo = 0*/) {
            bind();
            //activate properties
            const GLuint VERTEX_ATTR_POSITION = 0;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            const GLuint VERTEX_ATTR_TEXTURE = 1;
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
            vbo.bind();
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*)offsetof(type, position));
            glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*)offsetof(type, texture));
            vbo.debind();
            debind();
        }

        void bind();

        void debind();

        GLuint getM_id() const;
    };
}

#endif //BARRENLANDS_VAO_HPP
