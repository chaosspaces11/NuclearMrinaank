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
    Cell::state = 0;
    Cell::unstableState = 4;
    Cell::player = 0;

    // Initialises the location of the cells around the initialised cell
    Cell::adjacentLocations[0][0] = Cell::getX();
    Cell::adjacentLocations[0][1] = Cell::getY() - 1;

    Cell::adjacentLocations[1][0] = Cell::getX() + 1;
    Cell::adjacentLocations[1][1] = Cell::getY();

    Cell::adjacentLocations[2][0] = Cell::getX();
    Cell::adjacentLocations[2][1] = Cell::getY()+1;

    Cell::adjacentLocations[3][0] = Cell::getX()-1;
    Cell::adjacentLocations[3][1] = Cell::getY();
};

void Cell::buildUp(int player)
{
    //Changes player
    if (player != Cell::player)
    {
        Cell::player = player;
    }

    //Increases state
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
        Cell* adjacentCell = Grid::getCellAt(Cell::adjacentLocations[i][0],Cell::adjacentLocations[i][1]);
        adjacentCell->buildUp(Cell::player);
    }
}

void Cell::print()
{
    std::cout << "\x1b[3" << Cell::player << "m " << Cell::state << " \x1b[0m";
//    std::cout << "Cell: X: " << x << " Y: " << y << " State: " << Cell::state << std::endl;
}

int Cell::getPlayer()
{
    return Cell::player;
}

int Cell::getX()
{
    return Cell::x;
}

int Cell::getY()
{
    return Cell::Y;
}