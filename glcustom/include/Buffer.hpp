//
// Created by Lou Landry on 22/11/2017.
//

#ifndef IMACGL_BUFFER_HPP
#define IMACGL_BUFFER_HPP

#include <glimac/common.hpp>
#include <OpenGL/OpenGL.h>
#include <iostream>


class Buffer {
protected:
    GLuint m_id;
public:
    template <typename type>
    void fillBuffer(const std::vector<type> &elements){
        std::cerr << "Buffer::fillBuffer method has not been implemented in child class" ;
    }
    virtual void bind() = 0;
    virtual void debind() = 0;

};


#endif //IMACGL_BUFFER_HPP
