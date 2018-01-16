#ifndef FREEFLY_CAMERA_H
#define FREEFLY_CAMERA_H

#include "glm.hpp"

class FreeflyCamera {
private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    void computeDirectionVectors();

public:
    FreeflyCamera();
    FreeflyCamera(glm::vec3 position);
    void moveLeft(float t);
    void moveFront(float t);

    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::vec3 getPosition() const;

    glm::mat4 getViewMatrix() const;
};

#endif //FREEFLY_CAMERA_H
