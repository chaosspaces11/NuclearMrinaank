//
// Created by Michael Chen on 4/09/2018.
//

#include <iostream>
#include "SideCell.h"
#include "Grid.h"

SideCell::SideCell(int x, int y, int location): Cell(x,y)
{
    SideCell::unstableState = 3;
    int currentIndex = 0;


//     Initialises the location of the cells around the initialised cell
    switch (location)
    {
        case 0:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY() - 1;
            break;
        case 2:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() - 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();

            break;
        case 1:
        case 3:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() - 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();
            SideCell::adjacentLocations[++currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[++currentIndex][1] = SideCell::getY() - 1;
            break;
        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;

    }

    currentIndex++;

    switch (location)
    {
        case 1:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY() - 1;
            break;

        case 3:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() + 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();
            break;

        case 0:
        case 2:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() + 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();
            SideCell::adjacentLocations[+currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[+currentIndex][1] = SideCell::getY() - 1;
            break;

        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;
    }
}


