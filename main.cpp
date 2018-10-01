#include <iostream>
#include <string>
#include "Cell.h"
#include "Grid.h"
#include "CornerCell.h"
#include "Player.h"
#include "PlayerManager.h"


//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>

// Temporary functions:
bool isInt(std::string data)
{
    int valid = 0;
    for (int i = 0; i < data.length(); i++)
    {
        if (isdigit(data[i]))
        {
            valid += 1;
        }
    }
    return (valid == data.length());
}


int main()
{
    // Sets up width and height of the grid
    int gridWidth = 7;
    int gridHeight = 5;

    // FD of the game winner
    int winner = 0;

    //demo game with single player, selectedX and selectedY are coords of selected cell
    Grid mainGrid(gridHeight, gridWidth);

    // Sets up sentinel value for players
    int numPlayers = 0;

    bool server = false;
    bool gameModeSelected = false;

    std::string choice;
    int intChoice;

    do
    {
        std::cout << "Please select a game-mode:" << std::endl;
        std::cout << "1. Offline Lobby" << std::endl;
        std::cout << "2. Online Lobby" << std::endl;
        std::cout << ": ";
        std::cin >> choice;
        if (isInt(choice))
        {
            intChoice = stoi(choice);
            // Convert choice to integer
            if (intChoice == 1)
            {

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

        // Runs until a winner is found
        while (true)
        {
            // Runs the turn of the player
            playerManager.iteratePlayer(mainGrid);

            // If it is not the 1st round as the current player should own 0 cells in the first round
            if (!playerManager.getInitialRound())
            {

                // Checks to see if there is a winner
                if (!mainGrid.checkWin(playerManager.getPlayers()))
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
        mainGrid.renderDisplay();

        // Outputs the winner
        std::cout << "Player " << winner << " has won!" << std::endl;

        // Code exits
        return 0;
    }
    else
    {
        std::cout << "Server mode selected" << std::endl;
        while (true)
        {
            std::cout << "Would you like to:" << std::endl;
            std::cout << "1. Create a room" << std::endl;
            std::cout << "2. Join a room" << std::endl;
            std::cin >> choice;
            if (isInt(choice))
            {
                intChoice = stoi(choice);

                if (intChoice == 1)
                {
                    break;
                }
                else if (intChoice == 2)
                {
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
        std::cout << "Not implemented yet" << std::endl;
        return 0;
    }
}