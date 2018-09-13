#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "CornerCell.h"
#include "Player.h"
#include "PlayerManager.h"

//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>

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
                winner = playerManager.getCurrentPlayer()-1;

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