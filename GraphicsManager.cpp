//
// Created by Michael Chen on 10/12/2018.
//
#include <iostream>
#include "Grid.h"
#include "GraphicsManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
#include <stb_image.h>
#include <vector>

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
    glViewport(0, 0, 800, 800);

    GraphicsManager::clientVertices = {
            // Background Grid
            1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f,   0.0f, 0.0f,  0.0f, 0.0f, 0.0f,// top right corner
            1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom right corner
            -1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom left corner
            -1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top left corner

            0.975f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top right corner gridded
            0.975f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom right corner gridded

            1.0f, 0.975f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top right corner gridded
            -1.0f, 0.975f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom right corner gridded

            -0.975f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top right corner gridded
            -0.975f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom right corner gridded

            -1.0f, -0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top right corner gridded
            1.0f, -0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom right corner gridded

            // Dividing Bar
            0.5125f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// 12
            0.4875f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            0.5125f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.4875f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    GraphicsManager::clientIndices = {
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

    glGenVertexArrays(1, &clientVAO);
    glGenBuffers(1, &clientVBO);
    glGenBuffers(1, &clientEBO);

    glBindVertexArray(clientVAO);

    glBindBuffer(GL_ARRAY_BUFFER, clientVBO);
    glBufferData(GL_ARRAY_BUFFER, clientVertices.size()* sizeof(float), &clientVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, clientEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, clientIndices.size()* sizeof(unsigned int), &clientIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

}

void GraphicsManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GraphicsManager::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
void GraphicsManager::renderWindow()
{
    GraphicsManager::processInput(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsManager::renderClient()
{
    glBindVertexArray(clientVAO);
    glDrawElements(GL_TRIANGLES, clientIndices.size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

GLFWwindow* GraphicsManager::getWindow()
{
    return GraphicsManager::window;
}

void GraphicsManager::assignBufferData(unsigned int* VAOaddress, std::vector<float> VBOdata ,unsigned int* VBOaddress,std::vector<unsigned int> EBOdata,unsigned int* EBOaddress)
{

    glGenVertexArrays(1, VAOaddress);
    glGenBuffers(1, VBOaddress);
    glGenBuffers(1, EBOaddress);

    glBindVertexArray(*VAOaddress);

    glBindBuffer(GL_ARRAY_BUFFER, *VBOaddress);
    glBufferData(GL_ARRAY_BUFFER, VBOdata.size()* sizeof(float), &VBOdata[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBOaddress);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOdata.size()* sizeof(unsigned int), &EBOdata[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
//    glBindVertexArray(2);
}

void GraphicsManager::assignBufferData(unsigned int* VAOaddress, std::vector<float> VBOdata ,unsigned int* VBOaddress,std::vector<unsigned int> EBOdata,unsigned int* EBOaddress, unsigned int TEXaddress)
{
    glGenVertexArrays(1, VAOaddress);
    glGenBuffers(1, VBOaddress);
    glGenBuffers(1, EBOaddress);
    glBindVertexArray(*VAOaddress);

    glBindBuffer(GL_ARRAY_BUFFER, *VBOaddress);
    glBufferData(GL_ARRAY_BUFFER, VBOdata.size()* sizeof(float), &VBOdata[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBOaddress);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOdata.size()* sizeof(unsigned int), &EBOdata[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
//    glBindVertexArray(2);
}

void GraphicsManager::bindVertex(unsigned int* VAOaddress)
{
    glBindVertexArray(*VAOaddress);
}

void GraphicsManager::renderExternalData(std::vector<unsigned int> EBOdata)
{
    glDrawElements(GL_TRIANGLES, EBOdata.size(), GL_UNSIGNED_INT, 0);
}

void GraphicsManager::unbindVertex()
{
    glBindVertexArray(0);
}

void GraphicsManager::concludeRendering()
{
    glfwSwapBuffers(GraphicsManager::window);
    glfwPollEvents();
}

void GraphicsManager::updateGridColour(int currentPlayer, Grid* grid)
{
    std::vector<float> updatedColor;
    switch (currentPlayer)
    {
        default:
        case 1:
            updatedColor = {1.0f, 0.0f, 0.0f};
            break;
        case 2:
            updatedColor = {0.0f, 1.0f, 0.0f};
            break;
        case 3:
            updatedColor = {0.0f, 0.0f, 1.0f};
            break;
        case 4:
            updatedColor = {1.0f, 1.0f, 0.0f};
            break;
    };
    std::vector<float> targetArray = *(grid->getVBOData());
    for (int position = 0; position < 4; position++)
    {
        (targetArray)[position*11 + 3] = updatedColor[0];
        (targetArray)[position*11 + 4] = updatedColor[1];
        (targetArray)[position*11 + 5] = updatedColor[2];
    }

    grid->updateVBO(&targetArray);
    updateBufferData(grid->getVAOAddress(), grid->getVBOAddress(), *(grid->getVBOData()));
};

void GraphicsManager::updateBufferData(unsigned int* VAOaddress,unsigned int* bufferAddress, std::vector<float> updatedData)
{
//    glBindVertexArray(*VAOaddress);
    glBindBuffer(GL_ARRAY_BUFFER,*bufferAddress);
    glBufferData(GL_ARRAY_BUFFER, updatedData.size()*sizeof(float), &updatedData[0], GL_DYNAMIC_DRAW);
};