//
// Created by Michael Chen on 30/08/2018.
//
#include <iostream>
#include "Grid.h"

// Errors:
//      - Currently throws a tantrum whenever Grid::cells is used.
//          - std::vector <Cell> array; is fine


Grid::Grid(int xSize, int ySize): width(xSize), height(ySize)
{
    for (int row = 0; row < height; row++)
    {
        std::vector <Cell> array;
        for(int col = 0; col < width; col++)
        {

            array.push_back( Cell(row,col) );
        }
        Grid::cells.push_back(array);
    }
    std::cout << "Grid file linked successfully" << std::endl;
}

Cell Grid::getCellAt(int x, int y)
{
    return Grid::cells[x][y];
}

