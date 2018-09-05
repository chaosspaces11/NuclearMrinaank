#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "Debug.h"
#include "CornerCell.h"

int main()
{
    //demo game with single player, selectedX and selectedY are coords of selected cell
    Grid mainGrid(5,5);


    int numPlayers = 0;
    // Requests number of players from user
    std::cout << "Number of players: ";
    std::cin >> numPlayers;

    // Sets player token to the first player
    int player = 1;

    // Setting selectedX and selectedY to sentinel values
    int selectedX = -1;
    int selectedY = -1;

    // Requests X & Y from user
    std::cout << "Player " << player << std::endl << "X: ";
    std::cin >> selectedX;

    // Checks for valid input
    if (selectedX != -1)
    {
        std::cout << "Y: ";
        std::cin >> selectedY;
    }
    else
    {
        return 0;
    }

    // Runs while sentinel value is not given, ie program is not terminated
    while (selectedX != -1 || selectedY != -1)
    {

        // Returns the cell
        Cell* selectedCell = Grid::getCellAt(selectedX,selectedY);

        // Checks to see if current player can place on the cell
        while(selectedCell->getPlayer() != player && selectedCell->getPlayer() != 0)
        {

            // Requests another integer if move is invalid
            std::cout << "Not your Sinha! Please choose another" << std::endl << "X: ";
            std::cin >> selectedX;

            // Again sentinel value,
            if (selectedX != -1)
            {
                std::cout << "Y: ";
                std::cin >> selectedY;
            }
            else
            {
                return 0;
            }

            // Getting pointer for cell
            selectedCell = Grid::getCellAt(selectedX,selectedY);
        }

        // Running increasing the Sinhas in selected cell
        selectedCell->buildUp(player);

        // Prints out each cell for each row and column
        for(int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
            {
                Cell* cell = Grid::getCellAt(x,y);
                cell->print();
            }
            std::cout << std::endl;
        }

        // Loops current player back to first player if the last player has had its turn
        if (player >= numPlayers)
        {
            player = 1;
        }
        else
        {
            player++;
        }

        // Outputs current player
        std::cout << "Player " << player << std::endl << "X: ";
        std::cin >> selectedX;

        // Again sentinel value
        if (selectedX != -1)
        {
            std::cout << "Y: ";
            std::cin >> selectedY;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}