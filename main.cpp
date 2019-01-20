#include <iostream>
#include <string>
#include "Cell.h"
#include "Grid.h"
#include "CornerCell.h"
#include "Player.h"
#include "PlayerManager.h"
#include "GraphicsManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"

#include <thread>
#include <chrono>

#include "OpenGLDylib/glm/glm.hpp"
#include "OpenGLDylib/glm/gtc/matrix_transform.hpp"
#include "OpenGLDylib/glm//gtc/type_ptr.hpp"

#include <stb_image.h>

#include <pthread.h>
// Temporary functions:

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

// I don't quite know what to put these under

// Checks if input is an integer
bool isInt(std::string data)
{
    // Number of valid integers starts off as 0.
    int valid = 0;

    // For each character in the string, checks to see if it is an integer, if so increase valid by 1.
    for (int i = 0; i < data.length(); i++)
    {

        if (isdigit(data[i]))
        {
            valid += 1;
        }
    }

    // If valid is equal to the length of the string, every character in the string must be an integer
    return (valid == data.length());
}

// Not gonna lie, this function is a pile of trash, will probably rework later.
// Not gonna comment this, anything blows up chuck me a message
bool ipParser (std::string data)
{
    int length = 0;
    int dots = 0;
    std::string dot = ".";
    const char *dotPtr = dot.c_str();

    std::string temp;
    int intTemp;

    for (int i = 0; i < data.length(); i++)
    {

        if (isdigit(data[i]))
        {
            length += 1;
            temp += data[i];
        }
        else if (data[i] == *dotPtr)
        {
            if (length > 3)
            {
                std::cout << "Invalid IP" << std::endl;
                return false;
            }
            else
            {
                try
                {
                    intTemp = std::stoi(temp);
                }
                catch (std::invalid_argument)
                {
                    std::cout << "Invalid IP" << std::endl;
                    return false;
                }
                length = 0;
                dots += 1;
                temp = "";

                if (intTemp > 255)
                {
                    std::cout << "Invalid IP" << std::endl;
                    return false;
                }

                if (dots > 3)
                {
                    std::cout << "Invalid IP" << std::endl;
                    return false;
                }
            }
        }
        else
        {

            std::cout << "Invalid IP" << std::endl;
            return false;
        }
    }
    if (dots != 3)
    {
        std::cout << "Invalid IP" << std::endl;
        return false;
    }

    try
    {
        intTemp = std::stoi(temp);
    }
    catch (std::invalid_argument)
    {
        std::cout << "Invalid IP" << std::endl;
        return false;
    }
    if (intTemp > 255)
    {
        std::cout << "Invalid IP" << std::endl;
        return false;
    }

    return true;
}

struct ChangeLogger
{
    //
    bool roundProgressed;

    std::vector<std::vector<int>> explodeQueue;

    std::vector<std::vector<int>> coordLogs;



};



void *dataThread()
{
    // Sets up width and height of the grid
//    int gridWidth = 7;
//    int gridHeight = 5;

    // FD of the game winner
    int winner = 0;

    //demo game with single player, selectedX and selectedY are coords of selected cell
//    Grid mainGrid(gridHeight, gridWidth);

//    Grid* mainGridPtr = &(mutualItems1->coreGrid);


//    GraphicsManager* graphicsManagerPtr = (mutualItems1->coreGraphicsManager);
    // Sets up sentinel value for players
    int numPlayers = 0;

    // Default value for whether or not a server is required
    bool server = false;

    // Variables require for selection of game mode
    bool gameModeSelected = false;
    std::string choice;
    int intChoice;

    // Variable storing IP address
    std::string ipAddress;

    // Constantly prompts for a selection
    do
    {
        // Self explanatory
        std::cout << "Please select a game-mode:" << std::endl;
        std::cout << "1. Offline Lobby" << std::endl;
        std::cout << "2. Online Lobby" << std::endl;
        std::cout << ": ";
        std::cin >> choice;

        // Checks if choice is an int
        if (isInt(choice))
        {
            // Converts std::string to int with a separate variable
            intChoice = stoi(choice);

            // Checks if selection is a valid selection
            if (intChoice == 1)
            {
                // A game mode has been selected
                gameModeSelected = true;
            }

            else if (intChoice == 2)
            {
                server = true;
                gameModeSelected = true;
            }
            else
            {
                std::cout << "Invalid number" << std::endl;
            }
        }
        else
        {
            std::cout << "Not a number" << std::endl;
        }
    }

    // Keeps asking for a selection if game mode is not selected
    while (!gameModeSelected);

    if (!server)
    {
        // Requests number of players from user, potentially being moved into player manager constructor.
        std::cout << "Number of players: ";
        std::cin >> numPlayers;
        while (numPlayers < 2 || numPlayers > 4)
        {
            std::cout << "Invalid amount of players. Please reselect" << std::endl;
            std::cout << "Number of players: ";
            std::cin >> numPlayers;
        }

        // Sets up the player manager
        PlayerManager playerManager(numPlayers);
//        mutualItems1->corePlayerManager = &playerManager;

        // Runs until a winner is found
        while (true)
        {
//            mutualItems1->corePlayerManager = playerManager;

//            mutualItems1->coreGraphicsManager = *graphicsManagerPtr;
            // Runs the turn of the player
//            playerManager.iteratePlayer(*mainGridPtr);


            // If it is not the 1st round as the current player should own 0 cells in the first round
            if (!playerManager.getInitialRound())
            {

                // Checks to see if there is a winner
//                if (!((*mainGridPtr).checkWin(playerManager.getPlayers())))
//                {
//
//                    // Sets the winner, -1 is used to return indexing from 1 to 0
//                    winner = playerManager.getCurrentPlayer() - 1;
//
//                    // Fixes index shift
//                    if (winner == 0)
//                    {
//                        winner = 1;
//                    }
//
//                    break;
//                }
            }
        }

        // Draws final display before ending the game
//        (*mainGridPtr).renderDisplay();

        // Outputs the winner
        std::cout << "Player " << winner << " has won!" << std::endl;

        // Code exits
//        return 0;
    }
    else
        // Online multiplayer
    {
        std::cout << "Server mode selected" << std::endl;
        // Runs until a selection has been made
        while (true)
        {
            std::cout << "Would you like to:" << std::endl;
            std::cout << "1. Create a room" << std::endl;
            std::cout << "2. Join a room" << std::endl;
            std::cout << ": ";
            std::cin >> choice;

            // Checks if selection is an integer
            if (isInt(choice))
            {
                intChoice = stoi(choice);

                // Checks if selection is to create a room
                if (intChoice == 1)
                {
                    // Outputs IP
                    std::cout << "IP: ********" << std::endl;
                    break;
                }
                // Checks if selection is to join a room
                else if (intChoice == 2)
                {
                    std::cout << "Enter IP: ";
                    std::cin >> ipAddress;
                    // Checks to see if IP address is in a valid format, if not it asks for a new one
                    while (!ipParser(ipAddress))
                    {
                        std::cout << ":";
                        std::cin >> ipAddress;
                    }
                    // Prints out IP address
                    std::cout << ipAddress << std::endl;
                    break;
                }
                else
                {
                    std::cout << "Invalid number" << std::endl;
                }
            }
            else
            {
                std::cout << "Not a number" << std::endl;
            }
        }

        // Stuff goes here
        std::cout << "Not implemented yet" << std::endl;
//        return NULL;
    }
};

int main()
{

    const int gridWidth = 4;
    const int gridHeight = 6;

    int server = -1;
    int players = -1;

    clock_t roundClockInitial;
    clock_t roundClockFinal;
//    roundClockInitial = clock();

    PlayerManager playerManager(2);
    GraphicsManager graphicsManager;
    Grid grid(gridWidth, gridHeight,graphicsManager);
    Shader ourShader( "../vertexShader.glsl", "../fragmentShader.glsl");

    ChangeLogger dataLog = {.roundProgressed = false, .explodeQueue = {}, .coordLogs = {}};

    GLint transformLoc = glGetUniformLocation(ourShader.ID, "transform");

//    glm::mat4 transformMat = glm::mat4(1.0f);
//    transformMat = glm::rotate(transformMat, 1, glm::vec3(1.0, 0.0, 0.0));

    graphicsManager.assignBufferData((grid).getVAOAddress(), *(grid).getVBOData(), (grid).getVBOAddress(), *(grid).getEBOData(), (grid).getEBOAddress());

    while(!glfwWindowShouldClose(graphicsManager.getWindow()))
    {
        ourShader.use();

        // Renders window
        graphicsManager.renderWindow();


        // If server mode is not yet selected
        if (server == -1)
        {

            // Renders graphics for main menu
            graphicsManager.renderMainMenu();

            // Handles user input
            server = graphicsManager.handleMenuClick();

        }

        // Runs the if loop if server is equal to 0, aka false.
        else if (server == 0)
        {
            if (players == -1)
            {
                graphicsManager.renderPlayer();

                players = graphicsManager.handlePlayerClick();

                if (players > 1 && players < 5)
                {
                    playerManager.setPlayers(players);
                }
                roundClockInitial = clock();
            }
            else
            {
                roundClockFinal = clock();

                // Renders client - Outer white boarder.
                graphicsManager.renderClient();

                // If there is no explosion queued.
                if (dataLog.explodeQueue.size() == 0 && ((float)(roundClockFinal-roundClockInitial)/CLOCKS_PER_SEC) > 0.005)
                {
                    graphicsManager.handleGridClick((grid), &playerManager);
                }
                // Renders grid
                (grid).renderGameGrid(graphicsManager);

                // Checks if player has changed and updates grid colour accordingly
                if (dataLog.roundProgressed)
                {
                    graphicsManager.updateGridColour(playerManager.getCurrentPlayer(), &grid);
                    dataLog.roundProgressed = false;
                }

                // Renders sinhas
                for (int row = 0; row < grid.getHeight(); row++)
                {
                    for (int column = 0; column < grid.getWidth(); column ++)
                    {

                        Cell* currentCell = Grid::getCellAt(column,row);

                        if (currentCell->getExploding())
                        {

                            for (int i = 0; i < (currentCell->getState()); i++)
                            {
                                std::cout << "Sinhas:" << i << std::endl;

                                std::vector<float> data = *(currentCell->getVBOdata());

                                glm::mat4 transformMat = glm::mat4(1.0f);
                                transformMat = glm::mat4(1.0f);

                                auto explosionTime = (float)((clock() - currentCell->getExplosionInitial())*10/(double)(CLOCKS_PER_SEC));

                                std::cout << "Explosion Time: " << explosionTime << " seconds." << std::endl;
//                                transformMat = glm::scale(transformMat, glm::vec3(data[i*44+8] * explosionTime * 25, data[i*44+9] * explosionTime * 25,0.0));
//                                transformMat = glm::translate(transformMat, glm::vec3(0.0, 0.0 ,(data[i*44+8] * explosionTime * 200000)));

//                                transformMat = glm::scale(transformMat, glm::vec3(data[i*44+8] * explosionTime * 25, data[i*44+9] * explosionTime * 25,0.0));
//                                glUniformMatrix4fv(transformLoc, 4, GL_FALSE, glm::value_ptr(transformMat));
                                currentCell->incrementExplosion();
                                currentCell->updateGraphicsData();

                                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transformMat[0][0]);
                                if (explosionTime > 1)
                                {
                                    std::cout << explosionTime << std::endl;
                                    currentCell->finishExploding();
                                }
                            };

                        }
                        else
                        {
                            glm::mat4 transformMat = glm::mat4(1.0f);
                            transformMat = glm::rotate(transformMat, (float)glfwGetTime()* 2 * (currentCell->getState()+1), glm::vec3(1.0, 0.0, 1.0));
                            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMat));
                        };

                        if (currentCell->getChanged())
                        {
                            GraphicsManager::updateBufferData(currentCell->getVAOaddress(), currentCell->getVBOaddress(), *(currentCell->getVBOdata()));
                            dataLog.coordLogs.push_back({column,row});
                            dataLog.roundProgressed = true;
                            currentCell->toggleChanged();
                        }
                        if (currentCell->getState() == 0)
                        {
                            currentCell->resetOwner();
                        }
                        currentCell->renderSinhas(graphicsManager);
                    }
                }
            }


        }
        else if (server == 1)
        {
            // Establish connection to server
            // ...
            // ...
            // ...
        }
        graphicsManager.concludeRendering();
    }
    glfwTerminate();



    return 0;

}