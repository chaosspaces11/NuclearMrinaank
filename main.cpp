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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

struct mutualItems
        {
            Grid coreGrid;
            PlayerManager* corePlayerManager;
            GraphicsManager* coreGraphicsManager;
        };


void *dataThread(void* mutualItemsInput)
{
    // Sets up width and height of the grid
//    int gridWidth = 7;
//    int gridHeight = 5;

    // FD of the game winner
    int winner = 0;

    //demo game with single player, selectedX and selectedY are coords of selected cell
//    Grid mainGrid(gridHeight, gridWidth);

    mutualItems* mutualItems1 = (mutualItems*) mutualItemsInput;
    Grid* mainGridPtr = &(mutualItems1->coreGrid);


    GraphicsManager* graphicsManagerPtr = (mutualItems1->coreGraphicsManager);
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
        mutualItems1->corePlayerManager = &playerManager;

        // Runs until a winner is found
        while (true)
        {
//            mutualItems1->corePlayerManager = playerManager;

//            mutualItems1->coreGraphicsManager = *graphicsManagerPtr;
            // Runs the turn of the player
            playerManager.iteratePlayer(*mainGridPtr);


            // If it is not the 1st round as the current player should own 0 cells in the first round
            if (!playerManager.getInitialRound())
            {

                // Checks to see if there is a winner
                if (!((*mainGridPtr).checkWin(playerManager.getPlayers())))
                {

                    // Sets the winner, -1 is used to return indexing from 1 to 0
                    winner = playerManager.getCurrentPlayer() - 1;

                    // Fixes index shift
                    if (winner == 0)
                    {
                        winner = 1;
                    }

                    break;
                }
            }
        }

        // Draws final display before ending the game
        (*mainGridPtr).renderDisplay();

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

//void *graphicsThread( void*)
//{
//    GraphicsManager graphicsManager;
//    Shader ourShader("../vertexShader.glsl", "../fragmentShader.glsl");
//    graphicsManager.render();
//    return NULL;
//}

int main()
{
    pthread_t threads[2];
    int rc;

    PlayerManager temp(2);
    GraphicsManager graphicsManager;
    mutualItems core = {.coreGrid = Grid(4,6,graphicsManager), .corePlayerManager = &temp, .coreGraphicsManager = &graphicsManager};
    Grid* gridPtr = &(core.coreGrid);

//    rc = pthread_create(&threads[1], NULL, dataThread, (void*)&core);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    Shader ourShader( "../vertexShader.glsl", "../fragmentShader.glsl");

    graphicsManager.assignBufferData((*gridPtr).getVAOAddress(), *(*gridPtr).getVBOData(), (*gridPtr).getVBOAddress(), *(*gridPtr).getEBOData(), (*gridPtr).getEBOAddress());
    while(!glfwWindowShouldClose(graphicsManager.getWindow()))
    {
        ourShader.use();

//        std::cout << (*gridPtr->getVBOData())[3] << std::endl;
        // Renders screen
        graphicsManager.renderWindow();

        // Renders client
        graphicsManager.renderClient();

        // Renders grid
        graphicsManager.updateGridColour(core.corePlayerManager->getCurrentPlayer(), gridPtr);
        (*gridPtr).renderGameGrid(graphicsManager);
        graphicsManager.checkClick((*gridPtr), core.corePlayerManager->getCurrentPlayer());

        // Rotation Matrix
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, (float)glfwGetTime()*2, glm::vec3(0.0, 0.0, 1.0));
        GLint transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // Renders sinhas
        for (int row = 0; row < gridPtr->getHeight(); row++)
        {
            for (int column = 0; column < gridPtr -> getWidth(); column ++)
            {
                Cell* currentCell = gridPtr ->getCellAt(column,row);
                graphicsManager.updateBufferData(currentCell->getVAOaddress(), currentCell->getVBOaddress(), *(currentCell->getVBOdata()));

                currentCell->renderSinhas(graphicsManager);
            }
        }

        graphicsManager.concludeRendering();
    }
//    pthread_join(threads[1],NULL);
    glfwTerminate();



    return 0;

}