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
    switch (location)
    {
        case 0:
            CornerCell::adjacentLocations[0][0] = CornerCell::getX() + 1;
            CornerCell::adjacentLocations[0][1] = CornerCell::getY();
            CornerCell::adjacentLocations[1][0] = CornerCell::getX();
            CornerCell::adjacentLocations[1][1] = CornerCell::getY() + 1;
            break;
        case 1:
            CornerCell::adjacentLocations[0][0] = CornerCell::getX() - 1;
            CornerCell::adjacentLocations[0][1] = CornerCell::getY();
            CornerCell::adjacentLocations[1][0] = CornerCell::getX();
            CornerCell::adjacentLocations[1][1] = CornerCell::getY() + 1;
            break;
        case 2:
            CornerCell::adjacentLocations[0][0] = CornerCell::getX() - 1;
            CornerCell::adjacentLocations[0][1] = CornerCell::getY();
            CornerCell::adjacentLocations[1][0] = CornerCell::getX();
            CornerCell::adjacentLocations[1][1] = CornerCell::getY() - 1;
            break;
        case 3:
            CornerCell::adjacentLocations[0][0] = CornerCell::getX() + 1;
            CornerCell::adjacentLocations[0][1] = CornerCell::getY();
            CornerCell::adjacentLocations[1][0] = CornerCell::getX();
            CornerCell::adjacentLocations[1][1] = CornerCell::getY() - 1;
            break;
        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;
            break;
    }

}

