#include "../include/CameraManager.hpp"
#include "../include/Tools.hpp"

CameraManager::CameraManager(){
    //_position = glm::vec3(0,0,0);
    Tools::windowHeight +2 ;
    _camera1 = TrackballCamera();
    _camera2 = FreeflyCamera();
    _camera2.rotateLeft(180.0);
    _choice = 1;
}

CameraManager::CameraManager(glm::vec3 position)
        : _position(position)
{
    _camera1 = TrackballCamera(position);
    _camera2 = FreeflyCamera(position);
    _camera2.rotateLeft(180.0);
    _choice = 1;
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
        _position = _camera2.getPosition();
    }
}

void CameraManager::moveFront(float t){
    if(_choice == 1){
        _camera2.moveFront(t);
        _position = _camera2.getPosition();
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


//Déplacement ++
void CameraManager::moveLeft(float t, int nbrSub, float width, float scale, float posy){
    if(_choice == 1){
        _camera2.moveLeft(t);
        _camera2.setPositionY(posy*scale);
        _position = _camera2.getPosition();
    }
    if(_position.x < -width*nbrSub*scale/2.0 ||
       _position.x > width*nbrSub*scale/2.0 ||
       _position.z + 10 < -width*nbrSub*scale/2.0 ||
       _position.z + 10 > width*nbrSub*scale/2.0){
        _camera2.moveLeft(-t);
        _position = _camera2.getPosition();
    }
}

void CameraManager::moveFront(float t, int nbrSub, float width, float scale, float posy){
    if(_choice == 1){
        _camera2.moveFront(t);
        _camera2.setPositionY(posy*scale);
        _position = _camera2.getPosition();
    }
    if(_position.x < -width*nbrSub*scale/2.0 ||
       _position.x > width*nbrSub*scale/2.0 ||
       _position.z + 10 < -width*nbrSub*scale/2.0 ||
       _position.z + 10 > width*nbrSub*scale/2.0){
        _camera2.moveFront(-t);
        _position = _camera2.getPosition();
    }
}