#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "Debug.h"


int main()
{
    //demo game with single player, a and b are coords of selected cell
    Grid mainGrid(5,5);

    int a = -1;
    int b = -1;
    std::cout << "X: ";
    std::cin >> a;
    if (a != -1)
    {
        std::cout << "Y: ";
        std::cin >> b;
    }
    while (a != -1 || b != -1)
    {
        Cell* selectedCell = Grid::getCellAt(a,b);
        selectedCell->buildUp();
        for(int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
            {
                Cell* cell = Grid::getCellAt(x,y);
                cell->print();
            }
            std::cout << std::endl;
        }

        std::cout << "X: ";
        std::cin >> a;
        if (a != -1)
        {
            std::cout << "Y: ";
            std::cin >> b;
        }
    }

    return 0;
}