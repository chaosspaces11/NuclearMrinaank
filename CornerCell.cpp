//
// Created by yr12 on 4/9/18.
//

#include <iostream>
#include "CornerCell.h"
#include "Grid.h"

CornerCell::CornerCell(int x, int y, int location) : Cell(x,y)
{
    // Sets maximum number of Sinhas to 2
    CornerCell::unstableState = 2;

    // Goes clockwise from top-left corner to determine valid side cells
    switch (location)
    {
        case 0:
            Cell::adjacentLocations[0][0] = x + 1;
            Cell::adjacentLocations[0][1] = y;
            Cell::adjacentLocations[1][0] = x;
            Cell::adjacentLocations[1][1] = y + 1;
            break;
        case 1:
            Cell::adjacentLocations[0][0] = x - 1;
            Cell::adjacentLocations[0][1] = y;
            Cell::adjacentLocations[1][0] = x;
            Cell::adjacentLocations[1][1] = y + 1;
            break;
        case 2:
            Cell::adjacentLocations[0][0] = x - 1;
            Cell::adjacentLocations[0][1] = y;
            Cell::adjacentLocations[1][0] = x;
            Cell::adjacentLocations[1][1] = y - 1;
            break;
        case 3:
            Cell::adjacentLocations[0][0] = x + 1;
            Cell::adjacentLocations[0][1] = y;
            Cell::adjacentLocations[1][0] = x;
            Cell::adjacentLocations[1][1] = y - 1;
            break;
        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;
            break;
    }
}

