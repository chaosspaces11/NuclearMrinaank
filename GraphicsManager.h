//
// Created by Michael Chen on 10/12/2018.
//

#ifndef NUCLEARMRINAANK_GRAPHICSMANAGER_H
#define NUCLEARMRINAANK_GRAPHICSMANAGER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
//#include "Grid.h"
#include <stb_image.h>
#include <vector>

class Grid;

class GraphicsManager
{
public:

    GraphicsManager();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);

    void renderWindow();
    void renderClient();

    GLFWwindow* getWindow();

    void concludeRendering();

    void bindVertex(unsigned int* VAOaddress);
    void renderExternalData(std::vector<unsigned int> EBOdata);
    void renderExternalData(std::vector<unsigned int> EBOdata, int elements);
    void unbindVertex();

    void updateGridColour(int currentPlayer, Grid* grid);

    std::vector<float> clientVertices;

    void assignBufferData(unsigned int* VAOaddress, std::vector<float> VBOdata ,unsigned int* VBOaddress,std::vector<unsigned int> EBOdata,unsigned int* EBOaddress);
    void assignBufferData(unsigned int* VAOaddress, std::vector<float> VBOdata ,unsigned int* VBOaddress,std::vector<unsigned int> EBOdata,unsigned int* EBOaddress, unsigned int* TEXaddress);

    void updateBufferData(unsigned int* VAOaddress, unsigned int* bufferAddress, std::vector<float> updatedData);
//    void updateBufferData(unsigned int* bufferAddress, std::vector<unsigned int> updatedData);

    static void clickHandler(GLFWwindow *window, int button, int action, int mods);

    void checkClick(Grid grid, int player);


private:
    GLFWwindow* window;
    Shader* ourShader;


    std::vector<unsigned int> clientIndices;

    unsigned int clientVAO, clientVBO, clientEBO;
};


#endif //NUCLEARMRINAANK_GRAPHICSMANAGER_H
