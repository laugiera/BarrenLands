#include <include/NoiseManager.hpp>
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

/**
 * moveLeft()
 * @param float t
 */
//Déplacement ++++
void CameraManager::moveLeft(float t){
    float** terrain = NoiseManager::getInstance().heightMap;
    int i;
    int j;

    if(_choice == 1){
        int caseCamI = _position.z/Tools::scale + Tools::width*Tools::nbSub/2;
        int caseCamJ = _position.x/Tools::scale + Tools::width*Tools::nbSub/2;

        glm::vec3 v1 = glm::vec3(-Tools::width*Tools::nbSub/2.0+caseCamJ*Tools::width, terrain[caseCamI][caseCamJ], -Tools::width*Tools::nbSub/2.0+caseCamI*Tools::width);
        glm::vec3 v2 = glm::vec3(-Tools::width*Tools::nbSub/2.0+(caseCamJ+1)*Tools::width, terrain[caseCamI][caseCamJ+1], -Tools::width*Tools::nbSub/2.0+caseCamI*Tools::width);
        glm::vec3 v3 = glm::vec3(-Tools::width*Tools::nbSub/2.0+caseCamJ*Tools::width, terrain[caseCamI+1][caseCamJ], -Tools::width*Tools::nbSub/2.0+(caseCamI+1)*Tools::width);
        glm::vec3 v4 = glm::vec3(-Tools::width*Tools::nbSub/2.0+(caseCamJ+1)*Tools::width, terrain[caseCamI+1][caseCamJ+1], -Tools::width*Tools::nbSub/2.0+(caseCamI+1)*Tools::width);

        _camera2.moveLeft(t);
        if(inTriangle(v1, v2, v3) == 1){
            _camera2.setPositionY((determinerHauteur(v1, v2, v3)+0.5)*Tools::scale);
        }
        if(inTriangle(v2, v3, v4) == 1){
            _camera2.setPositionY((determinerHauteur(v2, v3, v4)+0.5)*Tools::scale);
        }
        _position = _camera2.getPosition();
    }

    int maxX = Tools::width*Tools::nbSub*Tools::scale/2.0;
    //int maxZ = Tools::width*Tools::nbSub*Tools::scale/2.0;

    if(_position.x*_position.x + _position.z*_position.z > (maxX-3*Tools::scale)*(maxX-3*Tools::scale)){
        _camera2.moveLeft(-t);
        _position = _camera2.getPosition();
    }

    /*if(_position.y < -5){
        _camera2.moveLeft(-t*3);
        _position = _camera2.getPosition();
    }*/
}

void CameraManager::moveFront(float t){
    float** terrain = NoiseManager::getInstance().heightMap;

    if(_choice == 1){
        int caseCamI = _position.z/Tools::scale + Tools::width*Tools::nbSub/2;
        int caseCamJ = _position.x/Tools::scale + Tools::width*Tools::nbSub/2;

        glm::vec3 v1 = glm::vec3(-Tools::width*Tools::nbSub/2.0+caseCamJ*Tools::width, terrain[caseCamI][caseCamJ], -Tools::width*Tools::nbSub/2.0+caseCamI*Tools::width);
        glm::vec3 v2 = glm::vec3(-Tools::width*Tools::nbSub/2.0+(caseCamJ+1)*Tools::width, terrain[caseCamI][caseCamJ+1], -Tools::width*Tools::nbSub/2.0+caseCamI*Tools::width);
        glm::vec3 v3 = glm::vec3(-Tools::width*Tools::nbSub/2.0+caseCamJ*Tools::width, terrain[caseCamI+1][caseCamJ], -Tools::width*Tools::nbSub/2.0+(caseCamI+1)*Tools::width);
        glm::vec3 v4 = glm::vec3(-Tools::width*Tools::nbSub/2.0+(caseCamJ+1)*Tools::width, terrain[caseCamI+1][caseCamJ+1], -Tools::width*Tools::nbSub/2.0+(caseCamI+1)*Tools::width);

        _camera2.moveFront(t);
        if(inTriangle(v1, v2, v3) == 1){
            _camera2.setPositionY((determinerHauteur(v1, v2, v3)+0.5)*Tools::scale);
        }
        if(inTriangle(v2, v3, v4) == 1){
            _camera2.setPositionY((determinerHauteur(v2, v3, v4)+0.5)*Tools::scale);
        }
        _position = _camera2.getPosition();
    }


    int maxX = Tools::width*Tools::nbSub*Tools::scale/2.0;
    //int maxZ = Tools::width*Tools::nbSub*Tools::scale/2.0;

    if(_position.x*_position.x + _position.z*_position.z > (maxX-3*Tools::scale)*(maxX-3*Tools::scale)){
        _camera2.moveFront(-t);
        _position = _camera2.getPosition();
    }
}


int CameraManager::inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B){
    float detPOPA;
    float detPAPB;
    float detPBPO;

    glm::vec2 PO = glm::vec2(O.x - _position.x/Tools::scale, O.z - _position.z/Tools::scale);
    glm::vec2 PA = glm::vec2(A.x - _position.x/Tools::scale, A.z - _position.z/Tools::scale);
    glm::vec2 PB = glm::vec2(B.x - _position.x/Tools::scale, B.z - _position.z/Tools::scale);

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

float CameraManager::determinerHauteur(glm::vec3 O, glm::vec3 A, glm::vec3 B){
    float a = (A.y - O.y)*(B.z - O.z) - (A.z - O.z)*(B.y - O.y);
    float b = (B.x - O.x)*(A.z - O.z) - (A.x - O.x)*(B.z - O.z);
    float c = (A.x - O.x)*(B.y - O.y) - (B.x - O.x)*(A.y - O.y);
    float d= -O.x*a - O.y*b - O.z*c;
    //std::cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << " res = " << (-a*_position.x/Tools::scale - c*_position.z/Tools::scale - d)/b << std::endl;
    return (-a*_position.x/Tools::scale - c*_position.z/Tools::scale - d)/b;
}