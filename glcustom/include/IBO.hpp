//
// Created by Lou Landry on 16/12/2017.
//
#define GLEW_STATIC
#ifndef BARRENLANDS_IBO_HPP
#define BARRENLANDS_IBO_HPP

#include <Buffer.hpp>
#include <vector>

namespace glcustom {
    class IBO : public Buffer {
    public:
        IBO();

        virtual ~IBO();

        template <typename type>
        void fillBuffer(const std::vector<type> &indices) {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(type), indices.data(), GL_STATIC_DRAW);
            debind();
        }

        void bind();

        void debind();

        GLuint getM_id() const;
    };
}

#endif //BARRENLANDS_IBO_HPP
