#ifndef BARRENLANDS_CAMERAMANAGER_HPP
#define BARRENLANDS_CAMERAMANAGER_HPP

#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include "../include/Tools.hpp"

/**
 * Class CameraManager
 * manage two different cameras (freefly and trackball) and tells wich one is the current camera
 */
class CameraManager{
public :
    //METHODS

    CameraManager();
    CameraManager(glm::vec3 position);
    glm::mat4 getViewMatrix();
    glm::mat4 getYRotationMatrix();


    //Déplacement ++
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void zoom(float t);

    //Pour le déplacement
    void moveLeft(float t, int nbrSub, float width, float scale, float posy);
    void moveFront(float t, int nbrSub, float width, float scale, float posy);



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
    int inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B);
    float determinerHauteur(glm::vec3 O, glm::vec3 A, glm::vec3 B);

    //ATTRIBUTS

    glm::vec3 _position;
    TrackballCamera _camera1;
    FreeflyCamera _camera2;
    int _choice;
};

#endif //BARRENLANDS_CAMERAMANAGER_HPP
