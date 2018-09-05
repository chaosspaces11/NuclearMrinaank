//
// Created by yr12 on 4/9/18.
//

#include <iostream>
#include "CornerCell.h"
#include "Grid.h"

CornerCell::CornerCell(int x, int y, int location) : Cell(x,y)
{
    CornerCell::unstableState = 2;
//     Initialises the location of the cells around the initialised cell
    CornerCell::adjacentLocations[1][2];
    switch (location)
    {
        case 0:
            std::cout << "Intialised" << std::endl;
            CornerCell::adjacentLocations[0][0] = x + 1;
            CornerCell::adjacentLocations[0][1] = y;
            CornerCell::adjacentLocations[1][0] = x;
            CornerCell::adjacentLocations[1][1] = y + 1;
            std::cout << adjacentLocations << std::endl;
            std::cout << adjacentLocations[0][0] << " " << adjacentLocations[0][1] << std::endl;
            break;
        case 1:
            CornerCell::adjacentLocations[0][0] = x - 1;
            CornerCell::adjacentLocations[0][1] = y;
            CornerCell::adjacentLocations[1][0] = x;
            CornerCell::adjacentLocations[1][1] = y + 1;
            break;
        case 2:
            CornerCell::adjacentLocations[0][0] = x - 1;
            CornerCell::adjacentLocations[0][1] = y;
            CornerCell::adjacentLocations[1][0] = x;
            CornerCell::adjacentLocations[1][1] = y - 1;
            break;
        case 3:
            CornerCell::adjacentLocations[0][0] = x + 1;
            CornerCell::adjacentLocations[0][1] = y;
            CornerCell::adjacentLocations[1][0] = x;
            CornerCell::adjacentLocations[1][1] = y - 1;
            break;
        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;
            break;
    }

}

