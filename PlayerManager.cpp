//
// Created by Michael Chen on 6/09/2018.
//
#include <iostream>
#include "PlayerManager.h"
#include "Grid.h"
#include "Player.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGlShader.h"
#include <stb_image.h>


// Construction of the player manager
PlayerManager::PlayerManager(int numPlayers): numPlayers(numPlayers), initialRound(true)
{
    // Generates an array of the Player class for each player.
    for (int player = 0; player < numPlayers; player++)
    {
        // Player is indexed from 1
        Player temp(player+1);
        PlayerManager::players.push_back(temp);
    }

    // Sets the index to the first player
    PlayerManager::playerIndex = 1;
}

// Checks the positon given to ensure that it is within the grid.
bool PlayerManager::checkPosition(int selectedX, int selectedY, Grid mainGrid)
{
    int gridWidth = mainGrid.getWidth();
    int gridHeight = mainGrid.getHeight();

    if (selectedX == -1|| selectedY == -1 || selectedX < 0 || selectedX > gridWidth - 1 || selectedY < 0 || selectedY > gridHeight - 1)
    {
        // Runs if values provided are not valid
        std::cout << "Invalid position, please enter another coordinate." << std::endl;
        return false;
    }

    return true;
}

// Checks the position given to ensure it is an appropriate cell for the player
bool PlayerManager::checkPlayer(int x, int y)
{

    // Gets a cell from the coordinates given
    Cell* selectedCell = Grid::getCellAt(x,y);

    // Checking the player matches the owner of the grid
    if (selectedCell->getPlayer() != playerIndex && selectedCell->getPlayer() != 0)
    {
        std::cout << "Not your Sinha, please enter another coordinate." << std::endl;
        return false;
    }

    return true;
}

// Gets an appropriate move from the player
Cell* PlayerManager::requestMove(int player, Grid mainGrid)
{
    // While loop runs until appropriate coordinate given
    while (true){

        // FD
        int selectedX;
        int selectedY;

        // Outputs the current player
        std::cout << "Player " << player << std::endl << "X: ";
        std::cin >> selectedX;
        std::cout << "Y: ";
        std::cin >> selectedY;
        selectedX--;
        selectedY--;

        // Checks if position is valid
        if (PlayerManager::checkPosition(selectedX,selectedY, mainGrid)){
            if (PlayerManager::checkPlayer(selectedX,selectedY))
            {
                // Returns the cell at the location
                return Grid::getCellAt(selectedX, selectedY);
            }
        }
    }
}


// Runs through the turn of the player
void PlayerManager::iteratePlayer(Grid mainGrid)
{

    // Debugging
//    std::cout << mainGrid.checkValid(playerIndex) << " Player:" << playerIndex << std::endl;
//    std::cout << players[playerIndex-1].checkActive() << std::endl;


    // Selects the currentPlayer
    Player currentPlayer = PlayerManager::players[PlayerManager::playerIndex-1];


//    while (current player is not active) || (there is no valid move for them)
//     increment current player till an active player is found


    while (!currentPlayer.checkActive() || !(mainGrid.checkValid(PlayerManager::playerIndex) || initialRound))
    {
        if (!(mainGrid.checkValid(PlayerManager::playerIndex) || initialRound))
        {
            std::cout << "Toggling off player: " << currentPlayer.getID() << std::endl;
            currentPlayer.setActive(false);
        }

        PlayerManager::nextPlayer();
        std::cout << "Player 1:" << mainGrid.checkValid(1) << std::endl;
        currentPlayer = PlayerManager::players[PlayerManager::playerIndex-1];
        std::cout << currentPlayer.getID() << std::endl;
    }

    // Checks if current player is still available to play
//    if (currentPlayer.checkActive())
//    {
//        // Checks if the current player has a valid move and it isn't the intial round as no players will have a cell.
//        if (mainGrid.checkValid(PlayerManager::playerIndex) || initialRound)
//        {
//
//            PlayerManager::playerIndex += 1;
////            std::cout << PlayerManager::playerIndex << std::endl;
//
//            // If the last player has just had their turn, loops back to the first round
//            if (PlayerManager::playerIndex > PlayerManager::numPlayers)
//            {
//                PlayerManager::playerIndex = 1;
//                initialRound = false;
//            }
//        }
//        else
//        {
//            // If no available move, takes the user out of the game and proceeds onto the next player
//            currentPlayer.setActive(false);
//            PlayerManager::playerIndex++;
//        }
//    }
//    else
//    {
//        // Moves onto the next player
//        PlayerManager::playerIndex++;
//
//
//        // If the last player has just had their turn, loops back to the first round
//        if (PlayerManager::playerIndex > PlayerManager::numPlayers)
//        {
//            PlayerManager::playerIndex = 1;
//        }
//    }
}

// Returning private variables
int PlayerManager::getPlayers()
{
    return PlayerManager::numPlayers;
}

void PlayerManager::setPlayers(int input)
{

    PlayerManager::numPlayers = input;
    PlayerManager::players = {};
    for (int player = 0; player < PlayerManager::numPlayers; player++)
    {
        // Player is indexed from 1
        Player temp(player+1);
        PlayerManager::players.push_back(temp);
    }
}

// Returning private variables
bool PlayerManager::getInitialRound()
{
    return PlayerManager::initialRound;
}

// Returning private variables
int PlayerManager::getCurrentPlayer()
{
    return PlayerManager::playerIndex;
}

void PlayerManager::nextPlayer()
{
    PlayerManager::playerIndex += 1;
    //std::cout << PlayerManager::playerIndex << std::endl;

    // If the last player has just had their turn, loops back to the first round
    if (PlayerManager::playerIndex > PlayerManager::numPlayers)
    {
        PlayerManager::playerIndex = 1;
        PlayerManager::initialRound = false;
    }
}
