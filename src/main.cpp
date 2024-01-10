#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
#include "texture.h"
#include "camera.h"

const float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Camera* activeCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    activeCamera->SetAspectRatio(width, height);
    glViewport(0, 0, width, height);
}  

void GetInput(GLFWwindow* window)
{
    Camera* activeCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        activeCamera->Move(Camera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        activeCamera->Move(Camera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        activeCamera->Move(Camera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        activeCamera->Move(Camera::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* activeCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    static bool firstMouse = true;
    // bbad
    static float lastX = 400.0f;
    static float lastY = 300.0f;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float x_offset = xpos - lastX;
    float y_offset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    activeCamera->PointAt(x_offset, y_offset);
}

int main()
{
    Camera mainCamera;
    mainCamera.SetPosition(0.0f, 0.0f, 5.0f);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWvidmode videoMode = *glfwGetVideoMode(monitor); 


    GLFWwindow* window = glfwCreateWindow(videoMode.width/4, videoMode.height/4, "Labyrinth", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, &mainCamera);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);    
    
    
    Shader lightingShader("shaders/lighting.vert", "shaders/lighting.frag");
    Shader lightShader("shaders/light.vert", "shaders/light.frag");
    //Texture diffuseTex("assets/textures/Painted_Ornament_DIFF.png");
    //Texture specularTex("assets/textures/Painted_Ornament_SPEC.png");
    Texture diffuseTex("assets/textures/Painted_Ornament_DIFF.png");
    Texture specularTex("assets/textures/Painted_Ornament_SPEC.png");

    unsigned VBO, VAO, lightVAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &lightVAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // LIGHT VAO
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        GetInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        /*
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        */
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 

        lightingShader.SetUniform1i("material.diffuse", 0);
        diffuseTex.BindTo(0);

        lightingShader.SetUniform1i("material.specular", 1);
        specularTex.BindTo(1);
        
        //lightingShader.SetUniformMatrix4f("model", model);
        lightingShader.SetUniformMatrix4f("view", mainCamera.GetViewMatrix());
        lightingShader.SetUniformMatrix4f("proj", mainCamera.GetProjectionMatrix());
        lightingShader.SetUniform3f("objColor", 1.0f, 1.0f, 1.0f);
        lightingShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
        
        lightingShader.SetUniform3f("viewPos", mainCamera.GetPosition().x, mainCamera.GetPosition().y, mainCamera.GetPosition().z);
        lightingShader.SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
        lightingShader.SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightingShader.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
        lightingShader.SetUniform1f("material.shininess", 32.0f);

        lightingShader.SetUniform3f("light.position", lightPos.x, lightPos.y, lightPos.z);
        lightingShader.SetUniform3f("light.ambient",  ambientColor.x, ambientColor.y, ambientColor.z);
        lightingShader.SetUniform3f("light.diffuse",  diffuseColor.x, diffuseColor.y, diffuseColor.z); // darken diffuse light a bit
        lightingShader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f); 

        lightingShader.Use();


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(VAO);
        for (unsigned int i = 1; i <= 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i-1]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.SetUniformMatrix4f("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }        
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        lightShader.SetUniformMatrix4f("model", lightModel);
        lightShader.SetUniformMatrix4f("view", mainCamera.GetViewMatrix());
        lightShader.SetUniformMatrix4f("proj", mainCamera.GetProjectionMatrix());
        lightShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);

        lightShader.Use();

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}