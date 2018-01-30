//
// Created by Lou Landry on 29/01/2018.
//

#ifndef BARRENLANDS_FBO_HPP
#define BARRENLANDS_FBO_HPP

#include "Buffer.hpp"
#include "Texture.hpp"

namespace glcustom {

    class FBO : public Buffer {

    public:
        FBO();

        virtual ~FBO();

        void bind();

        void debind();

        glcustom::Texture attachColorTexture(float width, float height);

        glcustom::Texture attachDepthTexture(float width, float height);

        void checkComplete();

        void clear();

    };

}

#endif //BARRENLANDS_FBO_HPP
