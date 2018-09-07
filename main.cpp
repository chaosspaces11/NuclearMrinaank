#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "Debug.h"
#include "CornerCell.h"
#include "Player.h"
#include "PlayerManager.h"

int main()
{
    // Sets up width and height of the grid
    int gridWidth = 5;
    int gridHeight = 5;

    //demo game with single player, selectedX and selectedY are coords of selected cell
    Grid mainGrid(gridHeight, gridWidth);

    // Sets up sentinel value for players
    int numPlayers = 0;

    // Requests number of players from user
    std::cout << "Number of players: ";
    std::cin >> numPlayers;
    while (numPlayers < 2 || numPlayers > 4)
    {
        std::cout << "Invalid amount of players. Please reselect" << std::endl;
        std::cout << "Number of players: ";
        std::cin >> numPlayers;
    }

    PlayerManager playerManager(numPlayers);

    while (true)
    {
        playerManager.iteratePlayer(mainGrid);
        // Checks for win
    }

    return 0;
}