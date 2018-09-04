//
// Created by Michael Chen on 30/08/2018.
//
#include <iostream>
#include "Grid.h"

//defining static vector Grid::cells
std::vector<std::vector<Cell> > Grid::cells;

Grid::Grid(int xSize, int ySize): width(xSize), height(ySize)
{
    //Fills Grid::cells vector with values
    for (int row = 0; row < height; row++)
    {
        std::vector <Cell> array;
        for(int col = 0; col < width; col++)
        {
            array.push_back( Cell(row,col) );
        }
        cells.push_back(array);
    }
//    std::cout << "Grid file linked successfully" << std::endl;
}

Cell* Grid::getCellAt(int x, int y)
{
    return &cells[x][y];
}

int Grid::getHeight()
{
    return Grid::height;
}

int Grid::getWidth()
{
    return Grid::width;
}


