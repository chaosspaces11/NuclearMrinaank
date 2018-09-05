#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "Debug.h"
#include "CornerCell.h"

int main()
{
    //demo game with single player, a and b are coords of selected cell
    Grid mainGrid(5,5);

    int numPlayers = 0;
    std::cout << "Number of players: ";
    std::cin >> numPlayers;

    int player = 1;


    int a = -1;
    int b = -1;
    std::cout << "Player " << player << std::endl << "X: ";
    std::cin >> a;
    if (a != -1)
    {
        std::cout << "Y: ";
        std::cin >> b;
    }
    else
    {
        return 0;
    }
    while (a != -1 || b != -1)
    {
        // SelectedCell only returns the Cell class type, not its children.
        Cell* selectedCell = Grid::getCellAt(a,b);
        while(selectedCell->getPlayer() != player && selectedCell->getPlayer() != 0)
        {
            std::cout << "Not your Sinha! Please choose another" << std::endl << "X: ";
            std::cin >> a;
            if (a != -1)
            {
                std::cout << "Y: ";
                std::cin >> b;
            }
            else
            {
                return 0;
            }
            selectedCell = Grid::getCellAt(a,b);
        }

        selectedCell->buildUp(player);
        for(int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
            {
                Cell* cell = Grid::getCellAt(x,y);
                cell->print();
            }
            std::cout << std::endl;
        }

        if (player >= numPlayers)
        {
            player = 1;
        }
        else
        {
            player++;
        }

        std::cout << "Player " << player << std::endl << "X: ";
        std::cin >> a;
        if (a != -1)
        {
            std::cout << "Y: ";
            std::cin >> b;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}