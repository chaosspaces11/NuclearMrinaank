#include <iostream>
#include "Cell.h"
#include "Grid.h"

Cell::Cell(int x, int y)
{
    // Test output statements
//    std::cout << "Cell file linked successfully" << std::endl;
//    std::cout << "X: " << x << " Y: " << y << std::endl;

    // Variable initialisation for the default cell
    Cell::x = x;
    Cell::y = y;
    Cell:state = 0;
    Cell::unstableState = 4;

    // Initialises the location of the cells around the initialised cell
    Cell::adjacentLocations[0][0] = Cell::x;
    Cell::adjacentLocations[0][1] = Cell::y - 1;

    Cell::adjacentLocations[1][0] = Cell::x + 1;
    Cell::adjacentLocations[1][1] = Cell::y;

    Cell::adjacentLocations[2][0] = Cell::x;
    Cell::adjacentLocations[2][1] = Cell::y+1;

    Cell::adjacentLocations[3][0] = Cell::x-1;
    Cell::adjacentLocations[3][1] = Cell::y;
};

void Cell::buildUp()
{
    Cell::state += 1;

    //cell has exceeded maximum state
    if (Cell::state >= Cell::unstableState)
    {
        Cell::explode();
    }
}

void Cell::explode()
{
    Cell::state = 0;

    for (int i = 0; i < sizeof(Cell::adjacentLocations) / sizeof(Cell::adjacentLocations[0]);i++)
    {
        Cell adjacentCell = Grid::getCellAt(Cell::adjacentLocations[i][0],Cell::adjacentLocations[i][1]);
        adjacentCell.buildUp();
    }
}

void Cell::print()
{
    std::cout << "Cell: X: " << x << " Y: " << y << std::endl;
}

