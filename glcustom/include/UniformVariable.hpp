//
// Created by Lou Landry on 02/12/2017.
//

#ifndef BARRENLANDSMASTER_UNIFORMVARIABLE_HPP
#define BARRENLANDSMASTER_UNIFORMVARIABLE_HPP
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <string>


namespace glcustom {

    //template<typename type>
    class UniformVariable {
    private:
        GLint m_location;
        std::string m_name;
        //type m_value;

    public:
        UniformVariable(GLuint program_location, const std::string &m_name);
    };

}
#endif //BARRENLANDSMASTER_UNIFORMVARIABLE_HPP

