//
// Created by Michael Chen on 10/12/2018.
//

#ifndef NUCLEARMRINAANK_GRAPHICSMANAGER_H
#define NUCLEARMRINAANK_GRAPHICSMANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
#include <stb_image.h>

class GraphicsManager
{
public:

    GraphicsManager();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);
    void render();
    GLFWwindow* getWindow();

private:
    GLFWwindow* window;
    Shader* ourShader;
};


#endif //NUCLEARMRINAANK_GRAPHICSMANAGER_H
