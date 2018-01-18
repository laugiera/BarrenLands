#ifndef BARRENLANDS_CAMERAMANAGER_HPP
#define BARRENLANDS_CAMERAMANAGER_HPP

#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include "../include/Tools.hpp"

class CameraManager{
public :
    //METHODS

    CameraManager();
    CameraManager(glm::vec3 position);
    glm::mat4 getViewMatrix();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void zoom(float t);

    //Pour le déplacement
    void moveLeft(float t, int nbrSub, float width, float scale, float posy);
    void moveFront(float t, int nbrSub, float width, float scale, float posy);

    //Déplacement ++
    void moveLeft(float t, std::vector<glimac::ShapeVertex> tab);
    void moveFront(float t, std::vector<glimac::ShapeVertex> tab);

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
    //METHOD
    int inTriangle(glimac::ShapeVertex O, glimac::ShapeVertex A, glimac::ShapeVertex B);
    float determinerHauteur(glimac::ShapeVertex O, glimac::ShapeVertex A, glimac::ShapeVertex B);

    //ATTRIBUTS

    glm::vec3 _position;
    TrackballCamera _camera1;
    FreeflyCamera _camera2;
    int _choice;
};

#endif //BARRENLANDS_CAMERAMANAGER_HPP
