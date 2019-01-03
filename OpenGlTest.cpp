#include <iostream>
//#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
#include <stb_image.h>

#include <cstdlib>
#include <pthread.h>
#include <vector>

// 1px  = -0.0025f
// 10px = 0.025f

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Checks input to see if escape key is pressed
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void *testCLI(void* uselessInt)
{
    int qwerty;
    std::cout << "qwerty = ";
    std::cin >> qwerty;
}

int main()
{

    // Initiates GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creates a window object
    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);

    // Checks if window is successfully created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Ensures other functions works on the window object created
    glfwMakeContextCurrent(window);

    // Readjusts viewport on window adjustment
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Loads GLAD library
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader ourShader( "../vertexShader.glsl", "../fragmentShader.glsl");

    // Vertices to define the points of our triangle
    std::vector<float> vertices = {
            // Background Grid
            1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner
            1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner
            -1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left corner
            -1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top left corner

            0.975f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
            0.975f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

            1.0f, 0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
            -1.0f, 0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

            -0.975f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
            -0.975f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

            -1.0f, -0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
            1.0f, -0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

            // Dividing Bar
            0.5125f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 12
            0.4875f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            0.5125f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.4875f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    };

    unsigned int indices[] = {
            // Background Grid
            0,1,4,
            5,4,1,
            6,3,7,
            6,3,0,
            8,3,9,
            9,3,2,
            10,2,1,
            11,1,10,

            // Dividing Bar
            12, 14, 13,
            13, 15, 14
    };

    float vertices2[] = {
            // Background Grid
            0.2625f,  0.7625f, 0.0f,   0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f,0.0f,0.0f, // top right
            0.2625f, -0.7625f, 0.0f,   0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7625f, -0.7625f, 0.0f,  0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom let
            -0.7625f,  0.7625f, 0.0f,  0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left

            // Row 1
            -0.7375f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 2
            -0.7375f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 3
            -0.7375f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 4
            -0.7375f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 5
            -0.7375f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 6
            -0.7375f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Sinhas
            -0.6875f,  0.6875f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  0.02f,0.02f,0.0f,// top left
            -0.5625f,  0.6875f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  0.02f,0.02f,0.0f,// top right
            -0.5625f,  0.5625f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  0.02f,0.02f,0.0f,// bottom right
            -0.6875f,  0.5625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.01f, 0.01f, 0.02f,0.02f,0.0f,// bottom left

            -0.6875f,  0.6875f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.02f   ,-0.02f,0.0f,// top left
            -0.5625f,  0.6875f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.02f   ,-0.02f,0.0f,// top right
            -0.5625f,  0.5625f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.02f   ,-0.02f,0.0f,// bottom right
            -0.6875f,  0.5625f, 0.0f,  0.0f, 0.0f, 1.0f,   0.01f, 0.01f, 0.02f ,-0.02f,0.0f,// bottom left
            };

    unsigned int indices2[] = {
            0,1,3,
            1,2,3,

            // Row 1
            4,5,6,
            6,7,4,

            8,9,10,
            10,11,8,

            12,13,14,
            14,15,12,

            16,17,18,
            18,19,16,

            // Row 2
            20,21,22,
            22,23,20,

            24,25,26,
            26,27,24,

            28,29,30,
            30,31,28,

            32,33,34,
            34,35,32,

            // Row 3
            36,37,38,
            38,39,36,

            40,41,42,
            42,43,40,

            44,45,46,
            46,47,44,

            48,49,50,
            50,51,48,

            // Row 4
            52,53,54,
            54,55,52,

            56,57,58,
            58,59,56,

            60,61,62,
            62,63,60,

            64,65,66,
            66,67,64,

            // Row 5
            68,69,70,
            70,71,68,

            72,73,74,
            74,75,72,

            76,77,78,
            78,79,76,

            80,81,82,
            82,83,80,

            // Row 6
            84,85,86,
            86,87,84,

            88,89,90,
            90,91,88,

            92,93,94,
            94,95,92,

            96,97,98,
            98,99,96,

            // First Sinha
            100,101,102,
            102,103,100,

            // Second Sinha
            104,105,106,
            106,107,104,
    };

    // Creating a vertex buffer object and vertex array object.
    unsigned int VBO, VAO, EBO, VBO2, VAO2, EBO2;


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
//    glEnableVertexAttribArray(3);

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("../NuclearMrinaank_Icon_SinhaDefault.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindVertexArray(0);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindTexture(GL_TEXTURE_2D, texture1);


    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);


        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, (float)glfwGetTime()*2, glm::vec3(0.0, 0.0, 1.0));

        // Uses program
        ourShader.use();

        GLint transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));



        // Appends data from VAO
        glBindVertexArray(VAO);

        // Draws the stuff
//        std::cout << sizeof(indices)/ sizeof(indices[0]) * 3;
        glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(indices[0]) * 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glBindVertexArray(VAO2);

        glDrawElements(GL_TRIANGLES, sizeof(indices2)/ sizeof(indices2[0]) * 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}