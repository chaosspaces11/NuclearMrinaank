//
// Created by Michael Chen on 6/09/2018.
//
#include <iostream>
#include "PlayerManager.h"
#include "Grid.h"
#include "Player.h"

PlayerManager::PlayerManager(int numPlayers): numPlayers(numPlayers)
{

    for (int player = 0; player < numPlayers; player++)
    {
        Player temp(player+1);
        players.push_back(temp);
    }

    currentPlayer = 1;

}

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

bool PlayerManager::checkPlayer(int x, int y)
{
    Cell* selectedCell = Grid::getCellAt(x,y);
    if (selectedCell->getPlayer() != currentPlayer && selectedCell->getPlayer() != 0)
    {
        std::cout << "Not your Sinha, please enter another coordinate." << std::endl;
        return false;
    }
    return true;
}

Cell* PlayerManager::requestMove(int player, Grid mainGrid)
{
    while (true){
        int selectedX;
        int selectedY;
        std::cout << "Player " << player << std::endl << "X: ";
        std::cin >> selectedX;
        std::cout << "Y: ";
        std::cin >> selectedY;
        if (PlayerManager::checkPosition(selectedX,selectedY, mainGrid)){
            if (PlayerManager::checkPlayer(selectedX,selectedY))
            {
                return Grid::getCellAt(selectedX, selectedY);
            }
        }
    }
}

void PlayerManager::iteratePlayer(Grid mainGrid)
{
    if (mainGrid.checkValid(currentPlayer))
    {
        mainGrid.renderDisplay();
        Cell *selectedCell = requestMove(currentPlayer, mainGrid);
        selectedCell->buildUp(currentPlayer++);
        if (currentPlayer > numPlayers){
            currentPlayer = 1;
        }
    }
    else
    {

    }
}

