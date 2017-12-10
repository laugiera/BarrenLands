//
// Created by Lou Landry on 22/11/2017.
//

#ifndef IMACGL_VBOBUFFER_HPP
#define IMACGL_VBOBUFFER_HPP

#include "Buffer.hpp"

class VBOBuffer : public Buffer {
protected:
    GLuint m_id;
public:
    VBOBuffer();
    ~VBOBuffer();
    void fill(const std::vector<glimac::ShapeVertex> &vertices);
    void bind();
    void debind();

    GLuint getM_id() const;

};


#endif //IMACGL_VBOBUFFER_HPP
