//
// Created by Michael Chen on 4/09/2018.
//

#include <iostream>
#include "SideCell.h"
#include "Grid.h"

SideCell::SideCell(int x, int y, int location): Cell(x,y)
{
    Cell::unstableState = 3;
    int currentIndex = 0;

//     Initialises the location of the cells around the initialised cell
    switch (location)
    {
        case 0:
            Cell::adjacentLocations[currentIndex][0] = x;
            Cell::adjacentLocations[currentIndex][1] = y + 1;
//            std::cout << "Top: " << x << " " << y << std::endl;
            break;
        case 2:
            Cell::adjacentLocations[currentIndex][0] = x;
            Cell::adjacentLocations[currentIndex][1] = y - 1;
//            std::cout << "Bottom:" << x << " " << y << std::endl;

            break;
        case 1:
        case 3:
            Cell::adjacentLocations[currentIndex][0] = x;
            Cell::adjacentLocations[currentIndex][1] = y - 1;
            Cell::adjacentLocations[++currentIndex][0] = x;
            Cell::adjacentLocations[currentIndex][1] = y + 1;
            break;
        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;
    }

    currentIndex++;

    switch (location)
    {
        case 1:
            Cell::adjacentLocations[currentIndex][0] = x - 1;
            Cell::adjacentLocations[currentIndex][1] = y;
//            std::cout << "Right: " << x << " " << y  << std::endl;
            break;

        case 3:
            Cell::adjacentLocations[currentIndex][0] = x + 1;
            Cell::adjacentLocations[currentIndex][1] = y;
//            std::cout << "Left: "  << x << " " << y << std::endl;
            break;

        case 0:
        case 2:
            Cell::adjacentLocations[currentIndex][0] = x + 1;
            Cell::adjacentLocations[currentIndex][1] = y;
            Cell::adjacentLocations[++currentIndex][0] = x - 1;
            Cell::adjacentLocations[currentIndex][1] = y;
//            std::cout << Cell::adjacentLocations[currentIndex][0] << " " << Cell::adjacentLocations[currentIndex][1] << std::endl;
            break;
        default:
            std::cout <<"ERROR initializing corner cell at (" << x << "," << y << ")!" << std::endl;
    }

}


