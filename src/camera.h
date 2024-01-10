#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PITCH_DEFAULT 0.0f
#define YAW_DEFAULT -90.0f
#define ROLL_DEFAULT 0.0f

#define SENS_DEFAULT 0.08f
#define SPEED_DEFAULT 2.5f

#define FOV_DEFAULT 45.0f
#define ASPECT_DEFAULT 16.0f / 9.0f
#define NEAR_DEFAULT 0.1f
#define FAR_DEFAULT 100.0f

#define POS_DEFAULT glm::vec3(0.0f, 0.0f, 0.0f)
#define UP_DEFAULT glm::vec3(0.0f, 1.0f, 0.0f)
#define FRONT_DEFAULT glm::vec3(0.0f, 0.0f, -1.0f)
#define RIGHT_DEFAULT glm::vec3(1.0f, 0.0f, 0.0f)

// camera = view matrix
// perspective camera just adds a projection matrix so that there need be no inheritance


class Camera 
{
public:
    enum MoveDirection
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
public:
    Camera(float fov = FOV_DEFAULT, float aspect = ASPECT_DEFAULT, float near = NEAR_DEFAULT, float far = FAR_DEFAULT);
    ~Camera() = default;

    void Move(MoveDirection direction, float deltaTime);
    void PointAt(float xoffset, float yoffset);
    
    void SetPosition(glm::vec3 position);
    void SetPosition(float x, float y, float z);
    glm::vec3 GetPosition();

    float GetFov();
    void SetFov(float fov);

    float GetAspectRatio();
    void SetAspectRatio(float aspectRatio);
    void SetAspectRatio(float width, float height);
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
private:
    void CalculateCameraVectors();
private:
    float m_Speed = SPEED_DEFAULT;
    float m_Sensitivity = SENS_DEFAULT;

    float m_Pitch = PITCH_DEFAULT;
    float m_Yaw = YAW_DEFAULT;
    float m_Roll = ROLL_DEFAULT;

    glm::vec3 m_Position = POS_DEFAULT;

    glm::vec3 m_Front = FRONT_DEFAULT;
    glm::vec3 m_Up = UP_DEFAULT;
    glm::vec3 m_Right = RIGHT_DEFAULT;
    glm::vec3 m_WorldUp = UP_DEFAULT;

    float m_Fov = FOV_DEFAULT;
    float m_AspectRatio = ASPECT_DEFAULT;
    float m_Near = NEAR_DEFAULT;
    float m_Far = FAR_DEFAULT;
};