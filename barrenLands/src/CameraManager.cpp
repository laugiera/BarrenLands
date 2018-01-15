#include "../include/CameraManager.hpp"

CameraManager::CameraManager(){
    //_position = glm::vec3(0,0,0);
    _camera1 = TrackballCamera();
    _camera2 = FreeflyCamera();
    _camera2.rotateLeft(180.0);
    _choice = 0;
}

glm::mat4 CameraManager::getViewMatrix(){
    if(_choice == 0){
        //return glm::translate(_camera1.getViewMatrix(),glm::vec3(-1)*_camera2.getPosition());
        _camera1.setPosition(glm::vec3(-1)*_camera2.getPosition());
        return _camera1.getViewMatrix();
    }
    else{
        return _camera2.getViewMatrix();
    }
}

void CameraManager::moveLeft(float t){
    if(_choice == 1){
        _camera2.moveLeft(t);
    }
}

void CameraManager::moveFront(float t){
    if(_choice == 1){
        _camera2.moveFront(t);
    }
}

void CameraManager::rotateLeft(float degrees){
    if(_choice == 0){
        _camera1.rotateLeft(degrees);
    }
    else{
        _camera2.rotateLeft(-1*degrees);
    }
}

void CameraManager::rotateUp(float degrees){
    if(_choice == 0){
        _camera1.rotateUp(degrees);
    }
    else{
        _camera2.rotateUp(-1*degrees);
    }
}

void CameraManager::zoom(float t){
    _camera1.moveFront(t);
}
