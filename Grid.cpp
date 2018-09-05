//
// Created by Michael Chen on 30/08/2018.
//
#include <iostream>
#include "Grid.h"
#include "CornerCell.h"
#include "SideCell.h"

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
            // This is a terrible solution, but it'll work
            if (col == 0)
            {
                if (row == 0)
                {
                    array.push_back( CornerCell(row,col,0) );
                }
                else if ((row + 1 - width) == 0)
                {
                    array.push_back( CornerCell(row,col,3) );
                }
                else
                {
                    array.push_back( SideCell(row,col,3) );
                }
            }
            else if ((col + 1 - height) == 0)
            {
                if (row == 0)
                {
                    array.push_back( CornerCell(row,col,1) );
                }
                else if ((row + 1 - width) == 0)
                {
                    array.push_back( CornerCell(row,col,2) );
                }
                else
                {
                    array.push_back( SideCell(row,col,1) );
                }
            }
            else if (row == 0)
            {
                array.push_back( SideCell(row,col,0) );
            }
            else if ((row + 1 - width) == 0)
            {
                array.push_back( SideCell(row,col,2) );
            }
            else
            {
                array.push_back( Cell(row,col));
            }
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


