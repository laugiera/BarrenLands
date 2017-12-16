//
// Created by Lou Landry on 22/11/2017.
//

#ifndef IMACGL_VBOBUFFER_HPP
#define IMACGL_VBOBUFFER_HPP

#include "Buffer.hpp"

namespace glcustom{

    class VBO : public Buffer {
    protected:
        //std::vector<type> m_content;
    public:
        VBO();

        ~VBO();

        template <typename type>
        void fillBuffer(const std::vector<type> &vertices) {
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(type), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void bind();

        void debind();

        GLuint getM_id() const;

    };

}


#endif //IMACGL_VBOBUFFER_HPP
