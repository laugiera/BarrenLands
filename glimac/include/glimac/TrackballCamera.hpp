#ifndef TRACKBALL_CAMERA_H
#define TRACKBALL_CAMERA_H

#include "glm.hpp"

class TrackballCamera {
private:
    glm::vec3 m_position;
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
public:
    TrackballCamera();
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::mat4 getViewMatrix() const;
};

#endif //TRACKBALL_CAMERA_H
