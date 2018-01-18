//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_COLOR_HPP
#define BARRENLANDS_COLOR_HPP


class Color {
public:
    Color();

    Color(float r);

    Color(float g, float b, float a);

    Color(float r, float g, float b, float a);

    inline float sanitize255(float f){
        return (f>1)? f/255.f : f;
    }

    void darken(float intensity);

    void lighten(float intensity);


private:
    float r;
    float g;
    float b;
    float a;

};


#endif //BARRENLANDS_COLOR_HPP
