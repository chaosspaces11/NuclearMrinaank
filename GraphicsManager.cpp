//
// Created by Michael Chen on 10/12/2018.
//

#include "GraphicsManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
#include <stb_image.h>

GraphicsManager::GraphicsManager()
{
    // Initiates GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creates a window object
    GraphicsManager::window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);

    // Checks if window is successfully created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    // Ensures other functions works on the window object created
    glfwMakeContextCurrent(window);

    // Readjusts viewport on window adjustment
    glfwSetFramebufferSizeCallback(window, GraphicsManager::framebuffer_size_callback);

    // Loads GLAD library
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, 800, 600);
}

void GraphicsManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GraphicsManager::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void GraphicsManager::render()
{
    GraphicsManager::processInput(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwWaitEvents();
}

GLFWwindow* GraphicsManager::getWindow()
{
    return window;
}

//void GraphicsManager::assignShader(Shader ourShader): ourShader(ourShader)
//{
//
//}



