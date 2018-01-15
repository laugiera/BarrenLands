#include "../include/CameraManager.hpp"

glm::vec4 CameraManager::getViewMatrix(){
    if(_choice == 0){
        return _camera1.getViewMatrix();
    }
    else{
        return _camera2.getViewMatrix();
    }
}

void CameraManager::moveLeft(float t){
    _position += glm::vec3(0,t,0);
    _camera1.setPosition(_position);
    _camera2.moveLeft(degrees);
}

void CameraManager::moveFront(float t){
    _position += glm::vec3(t,0,0);
    _camera1.setPosition(_position);
    _camera2.moveFront(degrees);
}

void CameraManager::rotateLeft(float degrees){
    _camera1.rotateLeft(degrees);
    _camera2.rotateLeft(degrees);
}

void CameraManager::rotateUp(float degrees){
    _camera1.rotateUp(degrees);
    _camera2.rotateUp(degrees);
}

void CameraManager::zoom(float t){
    _camera1.moveFront(t);
}
