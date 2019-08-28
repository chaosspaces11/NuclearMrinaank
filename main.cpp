#include <iostream>
#include <string>
#include "Cell.h"
#include "Grid.h"
#include "CornerCell.h"
#include "Player.h"
#include "PlayerManager.h"
#include "GraphicsManager.h"

//Graphics
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"

#include "OpenGLDylib/glm/glm.hpp"
#include "OpenGLDylib/glm/gtc/matrix_transform.hpp"
#include "OpenGLDylib/glm//gtc/type_ptr.hpp"

#include <stb_image.h>
// Temporary functions:

// Renders the window correctly
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

// Explained later in datalog implementation
struct ChangeLogger
{
    //
    bool roundProgressed;

    std::vector<std::vector<int>> explodeAnimationQueue;

    std::vector<std::vector<int>> explodeDistributionQueue;

    std::vector<std::vector<int>> coordLogs;

    int explosionTick;


};

// no longer used but kept as documentation of previous code
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

    // Grid width and height
    const int gridWidth = 4;
    const int gridHeight = 6;

    // Sentinel values for player and server selection
    int server = -1;
    int players = -1;

    //Perhaps add code here for forward declaration of IP and required stuff. etc username.

    // Initiation of required managers, playerManager is defaulted with 1 player and awaits player selection.
    PlayerManager playerManager(2);
    GraphicsManager graphicsManager;
    Grid grid(gridWidth, gridHeight,graphicsManager);
    // Shader for rendering graphics
    Shader ourShader( "../vertexShader.glsl", "../fragmentShader.glsl");

    // Value for whether or not the graphics
    int invertedX = 1;
    int invertedY = 1;

    // roundProgressed - Whether the round has been passed
    // explodeAnimationQueue - Queue for cells awaiting explosion animation
    // explodeDistributionQueue - Queue for cells distributing its sinhas.
    // coordLogs - Log of coordinates interacted by the player.
    // explosionTick - Timer for explosion so there  is a slight delay between explosion animations
    ChangeLogger dataLog = {.roundProgressed = false, .explodeAnimationQueue = {},.explodeDistributionQueue = {}, .coordLogs = {}, .explosionTick = 10};

    // GR - location of uniform variable within the shader.
    GLint transformLoc = glGetUniformLocation(ourShader.ID, "transform");

    // Assigning graphical data for the grid
    graphicsManager.assignBufferData((grid).getVAOAddress(), *(grid).getVBOData(), (grid).getVBOAddress(), *(grid).getEBOData(), (grid).getEBOAddress());

    // While window is not closed from escape key or close button
    while(!glfwWindowShouldClose(graphicsManager.getWindow()))
    {
        // Initialises the shader
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
            // If number of players is not yet selected.
            if (players == -1)
            {

                // Render player screen
                graphicsManager.renderPlayer();

                // Set players to be equal to whatever the user clicks on, this uses the modulus function and as such
                // can return an invalid amount of players.
                players = graphicsManager.handlePlayerClick();

                // If a valid number of players has been selected
                if (players > 1 && players < 5)
                {
                    playerManager.setPlayers(players);
                }
            }
            // If players has been selected
            else
            {

                // Renders client - Outer white boarder.
                graphicsManager.renderClient();

                // If there is no cells currently exploding, and it has been over a second since the last explosion.
                if (dataLog.explodeAnimationQueue.size() == 0 && dataLog.explodeDistributionQueue.size() == 0 &&  dataLog.explosionTick > 20)
                {
                    // Handles the user clicking on the grid
                    graphicsManager.handleGridClick((grid), &playerManager);
                }
                // Renders grid
                (grid).renderGameGrid(graphicsManager);

                // Checks if player has changed and updates grid colour accordingly, optimizing so grid data is not constantly
                // being changed
                if (dataLog.roundProgressed && dataLog.explodeAnimationQueue.size() == 0 && dataLog.explodeDistributionQueue.size() == 0)
                {
                    // Updating graphics data for the grid based on the current player.
                    graphicsManager.updateGridColour(playerManager.getCurrentPlayer(), &grid);
                    // Round has no longer progressed
                    dataLog.roundProgressed = false;
                }

                // Increment time since last explosion by 1
                dataLog.explosionTick += 1;

                // Runs for each cell within the grid
                for (int row = 0; row < grid.getHeight(); row++)
                {
                    for (int column = 0; column < grid.getWidth(); column ++)
                    {

                        // Gets current cell that the program will inspect first
                        Cell* currentCell = Grid::getCellAt(column,row);

                        // If cell has changed since the last inspection (from user input)
                        if (currentCell->getChanged())
                        {
                            // Update graphics data so the cell will render the correct amount of sinhas
                            GraphicsManager::updateBufferData(currentCell->getVAOaddress(), currentCell->getVBOaddress(), *(currentCell->getVBOdata()));

                            // Add to data log
                            dataLog.coordLogs.push_back({column,row});

                            // Round has progressed as the user has inputted something
                            dataLog.roundProgressed = true;

                            // Current cell has been inspected and as such, no longer different from our latest inspection
                            currentCell->toggleChanged();
                        }

                        else if (currentCell->getState() > 0)
                        {
                            // If current cell is exploding, hasnt been added to the explosion queue and hasnt been over
                            // ten ticks since the last explosion.
                            if (currentCell->getExploding() && !(currentCell->getQueued()) && dataLog.explosionTick > 10)
                            {
                                // Add current cell to list of cells to have an explosion animation
                                dataLog.explodeAnimationQueue.push_back({column,row});

                                // Sets correct internal data so the current cell will explode correctly
                                currentCell->beginExploding();
                            }
                            // If currentCell is not exploding or it has been under ten ticks since last explosion
                            else if ((!currentCell->getExploding()) || dataLog.explosionTick < 10)
                            {
                                // matrix declaration
                                glm::mat4 transformMat = glm::mat4(1.0f);

                                // Set matrix to cause the sinha to rotate at a speed corresponding to the amount of sinhas
                                transformMat = glm::rotate(transformMat, (float)glfwGetTime()* 2 * (currentCell->getState()+1), glm::vec3(1.0, 0.0, 1.0));

                                // Attaches matrix to shader variables
                                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMat));

                                // Renders all sinhas within the current cell
                                currentCell->renderSinhas(graphicsManager);
                            };
                        }
                    }
                }

                // For each cell exploding
                for (int cell = 0; cell<dataLog.explodeAnimationQueue.size(); cell++)
                {
                    // Get current cell that we're operating on
                    Cell *currentCell = Grid::getCellAt(dataLog.explodeAnimationQueue[cell][0],
                                                        dataLog.explodeAnimationQueue[cell][1]);

                    // Get graphics data from currentCell
                    std::vector<float> data = *currentCell->getVBOdata();

                    // Inverts the movement of sinha if it is on one of the side cells
                    if (dataLog.explodeAnimationQueue[cell][0] == gridWidth-1)
                    {
                        invertedX = -1;
                    }
                    else
                    {
                        invertedX = 1;
                    }

                    if (dataLog.explodeAnimationQueue[cell][1] == 0)
                    {
                        invertedY = -1;
                    }
                    else
                    {
                        invertedY = 1;
                    }

                    // For each sinha within current cell
                    for (int sinha = 0; sinha < currentCell->getState(); sinha++)
                    {
                        // Same as the rotate matrix but now scales the sinhas according to the stage of its animation
                        glm::mat4 transformMat = glm::mat4(1.0f);
                        transformMat = glm::scale(transformMat, glm::vec3(data[sinha*44+8] * currentCell->getAnimationTick() * 10000 * invertedX, data[sinha*44+9] * invertedY * 10000 * currentCell->getAnimationTick(),0.0));
                        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMat));

                        // Renders sinhas
                        currentCell -> renderSinhas(graphicsManager);
                    }

                    // Progresses to the next stage of the animation
                    currentCell->incrementAnimation();

                    // If stage of animation has exceeded its final stage
                    if (currentCell->getAnimationTick() > 25)
                    {
                        // Remove cell from explosion queue and adds it to distribution queue
                        dataLog.explodeDistributionQueue.push_back(dataLog.explodeAnimationQueue[0]);
                        dataLog.explodeAnimationQueue.erase(dataLog.explodeAnimationQueue.begin());

                    }
                }

                // If all cells have finished explosion animation
                if (dataLog.explodeAnimationQueue.size() == 0)
                {
                    // If there are cells awaiting distribution, probably redundant
                    if (dataLog.explodeDistributionQueue.size() > 0)
                    {
                        // For each cell that needs to be distributed, we constantly pop the queue
                        // until the queue is empty
                        for (int cell = 0; cell<dataLog.explodeDistributionQueue.size(); )
                        {
                            // Get current cell that we are operating on
                            Cell* currentCell = Grid::getCellAt(dataLog.explodeDistributionQueue[cell][0],dataLog.explodeDistributionQueue[cell][1]);

                            // Remove it from distibution queue
                            dataLog.explodeDistributionQueue.erase(dataLog.explodeDistributionQueue.begin());

                            // Set data within the currentCell such that the explosion has finished and adds a sinha
                            // to all surrounding cells.
                            currentCell->finishExploding();
                            // It now has been 0 ticks since the last explosion
                            dataLog.explosionTick = 0;
                        }
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
        // Finishes rendering
        graphicsManager.concludeRendering();
    }
    // Deletes data related to glfw freeing up memory space
    glfwTerminate();



    return 0;

}