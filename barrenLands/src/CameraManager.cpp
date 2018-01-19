#include "../include/CameraManager.hpp"

/**
 * CameraManager()
 * constructor of the two camera. Initialize current camera to trackball camera
 */
CameraManager::CameraManager(){
    _position = glm::vec3(0,0,0);
    //Tools::windowHeight +2 ;
    _camera1 = TrackballCamera();
    _camera2 = FreeflyCamera();
    _camera2.rotateLeft(180.0);
    _choice = 1;
}
/**
 * CameraManager()
 * onstructor with position
 * @param glm::vec3 position
 */
CameraManager::CameraManager(glm::vec3 position)
        : _position(position)
{
    _camera1 = TrackballCamera(position);
    _camera2 = FreeflyCamera(position);
    _camera2.rotateLeft(180.0);
    _choice = 1;
}
/**
 * getViewMatrix()
 * @return glm::mat4
 */
glm::mat4 CameraManager::getViewMatrix(){
    glm::mat4 MobelMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,-10.f));
    MobelMatrix = glm::scale(MobelMatrix , glm::vec3(Tools::scale,Tools::scale,Tools::scale));
    if(_choice == 0){
        //return glm::translate(_camera1.getViewMatrix(),glm::vec3(-1)*_camera2.getPosition());
        _camera1.setPosition(glm::vec3(-1)*_camera2.getPosition());
        return _camera1.getViewMatrix()*MobelMatrix;
    }
    else{
        return _camera2.getViewMatrix()*MobelMatrix;
    }
}
/**
 * moveLeft()
 * @param float t
 */
void CameraManager::moveLeft(float t){
    if(_choice == 1){
        _camera2.moveLeft(t);
        _position = _camera2.getPosition();
    }
}
/**
 * moveFront()
 * @param t
 */
void CameraManager::moveFront(float t){
    if(_choice == 1){
        _camera2.moveFront(t);
        _position = _camera2.getPosition();
    }
}
/**
 * rotateLeft()
 * @param degrees
 */
void CameraManager::rotateLeft(float degrees){
    if(_choice == 0){
        _camera1.rotateLeft(degrees);
    }
    else{
        _camera2.rotateLeft(-1*degrees);
    }
}
/**
 * rotateUp()
 * @param degrees
 */
void CameraManager::rotateUp(float degrees){
    if(_choice == 0){
        _camera1.rotateUp(degrees);
    }
    else{
        _camera2.rotateUp(-1*degrees);
    }
}
/**
 * zoom()
 * @param t
 */
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


//Déplacement ++++
void CameraManager::moveLeft(float t, std::vector<glimac::ShapeVertex> tab){
    if(_choice == 1){
        int caseCamI = _position.z/Tools::scale + Tools::width*Tools::nbSub/2;
        int caseCamJ = _position.x/Tools::scale + Tools::width*Tools::nbSub/2;
        _camera2.moveLeft(t);
        if(inTriangle(tab[caseCamI*(Tools::nbSub+1)+caseCamJ], tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ]) == 1){
            _camera2.setPositionY((determinerHauteur(tab[caseCamI*(Tools::nbSub+1)+caseCamJ], tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ])+0.5)*Tools::scale);
        }
        if(inTriangle(tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ+1]) == 1){
            _camera2.setPositionY((determinerHauteur(tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ+1])+0.5)*Tools::scale);
        }
        _position = _camera2.getPosition();
    }
    if(_position.x < -Tools::width*Tools::nbSub*Tools::scale/2.0 ||
       _position.x > Tools::width*Tools::nbSub*Tools::scale/2.0 ||
       _position.z + 10 < -Tools::width*Tools::nbSub*Tools::scale/2.0 ||
       _position.z + 10 > Tools::width*Tools::nbSub*Tools::scale/2.0){
        _camera2.moveLeft(-t);
        _position = _camera2.getPosition();
    }
}

void CameraManager::moveFront(float t, std::vector<glimac::ShapeVertex> tab){
    if(_choice == 1){
        int caseCamI = _position.z/Tools::scale + Tools::width*Tools::nbSub/2;
        int caseCamJ = _position.x/Tools::scale + Tools::width*Tools::nbSub/2;
        _camera2.moveFront(t);
        if(inTriangle(tab[caseCamI*(Tools::nbSub+1)+caseCamJ], tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ]) == 1){
            _camera2.setPositionY((determinerHauteur(tab[caseCamI*(Tools::nbSub+1)+caseCamJ], tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ])+0.5)*Tools::scale);
        }
        else if(inTriangle(tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ+1]) == 1){
            _camera2.setPositionY((determinerHauteur(tab[caseCamI*(Tools::nbSub+1)+caseCamJ+1], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ], tab[(caseCamI+1)*(Tools::nbSub+1)+caseCamJ+1])+0.5)*Tools::scale);
        }
        else{
            _camera2.setPositionY((tab[caseCamI*(Tools::nbSub+1)+caseCamJ].position.y+2)*Tools::scale);
        }
        _position = _camera2.getPosition();
    }
    if(_position.x < -Tools::width*Tools::nbSub*Tools::scale/2.0 ||
       _position.x > Tools::width*Tools::nbSub*Tools::scale/2.0 ||
       _position.z + 10 < -Tools::width*Tools::nbSub*Tools::scale/2.0 ||
       _position.z + 10 > Tools::width*Tools::nbSub*Tools::scale/2.0){
        _camera2.moveFront(-t);
        _position = _camera2.getPosition();
    }
}


int CameraManager::inTriangle(glimac::ShapeVertex O, glimac::ShapeVertex A, glimac::ShapeVertex B){
    float detPOPA;
    float detPAPB;
    float detPBPO;

    glm::vec2 PO = glm::vec2(O.position.x - _position.x/Tools::scale, O.position.z - _position.z/Tools::scale);
    glm::vec2 PA = glm::vec2(A.position.x - _position.x/Tools::scale, A.position.z - _position.z/Tools::scale);
    glm::vec2 PB = glm::vec2(B.position.x - _position.x/Tools::scale, B.position.z - _position.z/Tools::scale);

    detPOPA = PO.x*PA.y - PO.y*PA.x;
    detPAPB = PA.x*PB.y - PA.y*PB.x;
    detPBPO = PB.x*PO.y - PB.y*PO.x;

    if((detPOPA >=0 && detPAPB >=0 && detPBPO >= 0) ||
       (detPOPA <0 && detPAPB <0 && detPBPO < 0)){
        return 1;
    }
    else{
        return 0;
    }
}

float CameraManager::determinerHauteur(glimac::ShapeVertex O, glimac::ShapeVertex A, glimac::ShapeVertex B){
    float a = (A.position.y - O.position.y)*(B.position.z - O.position.z) - (A.position.z - O.position.z)*(B.position.y - O.position.y);
    float b = (B.position.x - O.position.x)*(A.position.z - O.position.z) - (A.position.x - O.position.x)*(B.position.z - O.position.z);
    float c = (A.position.x - O.position.x)*(B.position.y - O.position.y) - (B.position.x - O.position.x)*(A.position.y - O.position.y);
    float d= -O.position.x*a - O.position.y*b - O.position.z*c;
    //std::cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << " res = " << (-a*_position.x/Tools::scale - c*_position.z/Tools::scale - d)/b << std::endl;
    return (-a*_position.x/Tools::scale - c*_position.z/Tools::scale - d)/b;
}