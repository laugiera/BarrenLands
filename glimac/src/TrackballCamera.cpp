#include <glimac/TrackballCamera.hpp>

TrackballCamera::TrackballCamera() {
    m_fDistance = 5;
    m_fAngleX = m_fAngleY = 0;
}

void TrackballCamera::moveFront(float delta)
{
    m_fDistance += delta;

}

void TrackballCamera::rotateLeft(float degrees)
{
    m_fAngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees)
{
    m_fAngleX += degrees;
}

glm::vec3 TrackballCamera::getPosition(){
    return m_position;
}

void TrackballCamera::setPosition(glm::vec3 position){
    m_position = position;
}

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(m_position.x, m_position.y, m_position.z-m_fDistance));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));
    return viewMatrix;
}
