#ifndef BARRENLANDS_CAMERAMANAGER_HPP
#define BARRENLANDS_CAMERAMANAGER_HPP

#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/glm.hpp>

class CameraManager{
public :
    //METHODS

    glm::vec4 getViewMatrix();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void zoom(float t);


    //GETTER AND SETTER
    glm::vec3 getPosition(){
        return _position;
    }
    void setPosition(glm::vec3 position){
        _position = position;
    }

    int getChoice(){
        return _choice;
    }
    void setChoice(int choice){
        _choice = choice;
    }

private:
    glm::vec3 _position;
    TrackballCamera _camera1;
    FreeflyCamera _camera2;
    int _choice;
};

#endif //BARRENLANDS_CAMERAMANAGER_HPP
