//
// Created by Michael Chen on 10/12/2018.
//

#ifndef NUCLEARMRINAANK_GRAPHICSMANAGER_H
#define NUCLEARMRINAANK_GRAPHICSMANAGER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
//#include "PlayerManager.h"
//#include "Grid.h"
#include <stb_image.h>
#include <vector>

class Grid;
class PlayerManager;

class GraphicsManager
{
public:

    GraphicsManager();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);

    void renderWindow();
    void renderClient();
    void renderMainMenu();
    void renderPlayer();

    void bindTexture(unsigned int TEXaddress);

    GLFWwindow* getWindow();

    void concludeRendering();

    void bindVertex(unsigned int* VAOaddress);
    static void renderExternalData(std::vector<unsigned int> EBOdata);
    void renderExternalData(std::vector<unsigned int> EBOdata, int elements);
    void unbindVertex();

    void updateGridColour(int currentPlayer, Grid* grid);

    std::vector<float> clientVertices;
    std::vector<float> menuVertices;

    void assignBufferData(unsigned int* VAOaddress, std::vector<float> VBOdata ,unsigned int* VBOaddress,std::vector<unsigned int> EBOdata,unsigned int* EBOaddress);
    void assignBufferData(unsigned int* VAOaddress, std::vector<float> VBOdata ,unsigned int* VBOaddress,std::vector<unsigned int> EBOdata,unsigned int* EBOaddress, unsigned int* TEXaddress);

    void updateBufferData(unsigned int* VAOaddress, unsigned int* bufferAddress, std::vector<float> updatedData);
//    void updateBufferData(unsigned int* bufferAddress, std::vector<unsigned int> updatedData);

//    static void gridClickHandler(GLFWwindow *window, int button, int action, int mods);

    void handleGridClick(Grid grid, PlayerManager* playerManagerPtr);
    int  handleMenuClick();
    int  handlePlayerClick();


private:
    GLFWwindow* window;
    Shader* ourShader;

    std::vector<unsigned int> clientIndices;
    std::vector<unsigned int> menuIndices;

    unsigned int clientVAO, clientVBO, clientEBO;
    unsigned int menuVAO, menuVBO, menuEBO, menuTEX;
    unsigned int playerTEX;
};


#endif //NUCLEARMRINAANK_GRAPHICSMANAGER_H
