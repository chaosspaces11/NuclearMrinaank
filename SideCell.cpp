//
// Created by Michael Chen on 4/09/2018.
//

#include <iostream>
#include "SideCell.h"
SideCell::SideCell(int x, int y, int heightLocation, int widthLocation): Cell(x,y)
{
    SideCell::unstableState = 2;
    int currentIndex = 0;


//     Initialises the location of the cells around the initialised cell
    switch (heightLocation)
    {
        case 0:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY() - 1;
            break;
        case 2:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() - 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();

            break;
        default:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() - 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();
            SideCell::adjacentLocations[++currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[++currentIndex][1] = SideCell::getY() - 1;
            break;

    }

    currentIndex++;

    switch (widthLocation)
    {
        case 1:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY() - 1;
            break;
        case 3:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() + 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();
            break;
        default:
            SideCell::adjacentLocations[currentIndex][0] = SideCell::getX() + 1;
            SideCell::adjacentLocations[currentIndex][1] = SideCell::getY();
            SideCell::adjacentLocations[+currentIndex][0] = SideCell::getX();
            SideCell::adjacentLocations[+currentIndex][1] = SideCell::getY() - 1;
            break;
    }

}