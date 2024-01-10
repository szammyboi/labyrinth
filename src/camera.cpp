#include "camera.h"

Camera::Camera(float fov, float aspect, float near, float far)
    : m_Fov(fov), m_AspectRatio(aspect), m_Near(near), m_Far(far)
{
    CalculateCameraVectors();
}   

void Camera::Move(MoveDirection direction, float deltaTime)
{
    float velocity = m_Speed * deltaTime;
    if (direction == FORWARD)
        m_Position += m_Front * velocity;
    if (direction == BACKWARD)
        m_Position -= m_Front * velocity;
    if (direction == LEFT)
        m_Position -= m_Right * velocity;
    if (direction == RIGHT)
        m_Position += m_Right * velocity;
}

void Camera::PointAt(float xOffset, float yOffset)
{
    xOffset *= m_Sensitivity;
    yOffset *= m_Sensitivity;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    CalculateCameraVectors();
}

void Camera::SetPosition(glm::vec3 position)
{
    m_Position = position;
    //CalculateCameraVectors();
}

void Camera::SetPosition(float x, float y, float z)
{
    m_Position = glm::vec3(x, y, z);
    // CalculateCameraVectors();
}

glm::vec3 Camera::GetPosition()
{
    return m_Position;
}

float Camera::GetFov()
{
    return m_Fov;
}

void Camera::SetFov(float fov)
{
    m_Fov = fov;
}

float Camera::GetAspectRatio()
{
    return m_AspectRatio;
}

void Camera::SetAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
}

void Camera::SetAspectRatio(float width, float height)
{
    m_AspectRatio = width / height;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
}

void Camera::CalculateCameraVectors()
{
    glm::vec3 temp_front;
    temp_front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    temp_front.y = sin(glm::radians(m_Pitch));
    temp_front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

    m_Front = glm::normalize(temp_front);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}