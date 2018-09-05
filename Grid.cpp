//
// Created by Michael Chen on 30/08/2018.
//
#include <iostream>
#include "Grid.h"
#include "CornerCell.h"
#include "SideCell.h"

//defining static vector Grid::cells
std::vector<std::vector<Cell> > Grid::cells;

// Grid constructor
Grid::Grid(int xSize, int ySize): width(xSize), height(ySize)
{
    // Integer expression for the location of the edge cells, the top right corner is considered as 0, incrementing as
    // you proceed clockwise.
    int top = 0;
    int right = 1;
    int bottom = 2;
    int left = 3;

    //Fills Grid::cells vector with values
    for (int row = 0; row < height; row++)
    {
        std::vector <Cell> array;

        // Iterates through for each column
        for(int col = 0; col < width; col++)
        {
            // This is a terrible solution, but it'll work

            // If x coordinate is 0, it proceeds to determine if the cell is a side cell or a corner cell
            if (col == 0)
            {

                // Checks if it's a corner cell
                if (row == 0)
                {
                    array.push_back( CornerCell(col,row,top) );
                }

                // The addition of 1 is required as "row" is indexed from 0 while "width" is indexed from 1
                // Checks if it's a corner cell
                else if ((row + 1 - width) == 0)
                {
                    array.push_back( CornerCell(col,row,left) );
                }

                // If not a corner cell, pushes it as a side cell
                else
                {
                    array.push_back( SideCell(col,row,left) );
                }
            }

            // Runs through the same process as the above if statement except this time checking the rightmost column.
            else if ((col + 1 - height) == 0)
            {
                if (row == 0)
                {
                    array.push_back( CornerCell(col,row,right) );
                }
                else if ((row + 1 - width) == 0)
                {
                    array.push_back( CornerCell(col,row,bottom) );
                }
                else
                {
                    array.push_back( SideCell(col,row,right) );
                }
            }

            // As there is no corner cells, checks to see if it a top side cell
            else if (row == 0)
            {
                array.push_back( SideCell(col,row, top) );
            }

            // Checks to see if it is a bottom side cell
            else if ((row + 1 - width) == 0)
            {
                array.push_back( SideCell(col,row, bottom) );
            }

            // As its not a corner cell or a side cell, its a default cell
            else
            {
                array.push_back( Cell(col,row));
            }
        }
        // Adds the array to cells. This arrays is essentially the row of the grid.
        cells.push_back(array);
    }
//    std::cout << "Grid file linked successfully" << std::endl;
}

// Returns a pointer given the x and y coordinate
Cell* Grid::getCellAt(int x, int y)
{
    // Y & X are swapped around as during code generation, the rows were appended before the columns.
    return &cells[y][x];
}

int Grid::getHeight()
{
    return Grid::height;
}

int Grid::getWidth()
{
    return Grid::width;
}


