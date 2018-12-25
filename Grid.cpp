//
// Created by Michael Chen on 30/08/2018.
//
#include <iostream>
#include "Grid.h"
#include "CornerCell.h"
#include "SideCell.h"
#include "Cell.h"
#include "GraphicsManager.h"
#include "PlayerManager.h"

//defining static vector Grid::cells
std::vector<std::vector<Cell> > Grid::cells;
std::vector<float> backgroundVertices;
std::vector<unsigned int> backgroundIndices;

// Grid constructor
Grid::Grid(int xSize, int ySize, GraphicsManager graphicsManager): width(xSize), height(ySize)
{
    // Integer expression for the location of the edge cells, the top right corner is considered as 0, incrementing as
    // you proceed clockwise.
    int top = 0;
    int right = 1;
    int bottom = 2;
    int left = 3;

    unsigned long position;


    //Fills Grid::cells vector with values
    for (int row = 0; row < height; row++)
    {
        std::vector<Cell> array;

        // Iterates through for each column
        for (int col = 0; col < width; col++)
        {
            // This is a terrible solution, but it'll work

            // If x coordinate is 0, it proceeds to determine if the cell is a side cell or a corner cell
            if (col == 0)
            {

                // Checks if it's a corner cell
                if (row == 0)
                {
                    array.push_back(CornerCell(col, row, top));
                    position = (array.size() - 1);
                    graphicsManager.assignBufferData(
                            array[position].getVAOaddress(),
                            *(array[position].getVBOdata()),
                            array[position].getVBOaddress(),
                            *(array[position].getEBOdata()),
                            array[position].getEBOaddress(),
                            array[position].getTEXaddress()
                            );
                }

                    // The addition of 1 is required as "row" is indexed from 0 while "width" is indexed from 1
                    // Checks if it's a corner cell
                else if ((row + 1 - height) == 0)
                {
                    array.push_back(CornerCell(col, row, left));
                    position = (array.size() - 1);
                    graphicsManager.assignBufferData(
                            array[position].getVAOaddress(),
                            *(array[position].getVBOdata()),
                            array[position].getVBOaddress(),
                            *(array[position].getEBOdata()),
                            array[position].getEBOaddress(),
                            array[position].getTEXaddress()
                    );
                }

                    // If not a corner cell, pushes it as a side cell
                else
                {
                    array.push_back(SideCell(col, row, left));
                    position = (array.size() - 1);
                    graphicsManager.assignBufferData(
                            array[position].getVAOaddress(),
                            *(array[position].getVBOdata()),
                            array[position].getVBOaddress(),
                            *(array[position].getEBOdata()),
                            array[position].getEBOaddress(),
                            array[position].getTEXaddress()
                    );
                }
            }

                // Runs through the same process as the above if statement except this time checking the rightmost column.
            else if ((col + 1 - width) == 0)
            {
                if (row == 0)
                {
                    array.push_back(CornerCell(col, row, right));
                    position = (array.size() - 1);
                    graphicsManager.assignBufferData(
                            array[position].getVAOaddress(),
                            *(array[position].getVBOdata()),
                            array[position].getVBOaddress(),
                            *(array[position].getEBOdata()),
                            array[position].getEBOaddress(),
                            array[position].getTEXaddress()
                    );
                }
                else if ((row + 1 - height) == 0)
                {
                    array.push_back(CornerCell(col, row, bottom));
                    position = (array.size() - 1);
                    graphicsManager.assignBufferData(
                            array[position].getVAOaddress(),
                            *(array[position].getVBOdata()),
                            array[position].getVBOaddress(),
                            *(array[position].getEBOdata()),
                            array[position].getEBOaddress(),
                            array[position].getTEXaddress()
                    );
                }
                else
                {
                    array.push_back(SideCell(col, row, right));
                    position = (array.size() - 1);
                    graphicsManager.assignBufferData(
                            array[position].getVAOaddress(),
                            *(array[position].getVBOdata()),
                            array[position].getVBOaddress(),
                            *(array[position].getEBOdata()),
                            array[position].getEBOaddress(),
                            array[position].getTEXaddress()
                    );
                }
            }

                // As there is no corner cells, checks to see if it a top side cell
            else if (row == 0)
            {
                array.push_back(SideCell(col, row, top));
                position = (array.size() - 1);
                graphicsManager.assignBufferData(
                        array[position].getVAOaddress(),
                        *(array[position].getVBOdata()),
                        array[position].getVBOaddress(),
                        *(array[position].getEBOdata()),
                        array[position].getEBOaddress(),
                        array[position].getTEXaddress()
                );
            }

                // Checks to see if it is a bottom side cell
            else if ((row + 1 - height) == 0)
            {
                array.push_back(SideCell(col, row, bottom));
                position = (array.size() - 1);
                graphicsManager.assignBufferData(
                        array[position].getVAOaddress(),
                        *(array[position].getVBOdata()),
                        array[position].getVBOaddress(),
                        *(array[position].getEBOdata()),
                        array[position].getEBOaddress(),
                        array[position].getTEXaddress()
                );
            }

                // As its not a corner cell or a side cell, its a default cell
            else
            {
                array.emplace_back(Cell(col, row));
                position = (array.size() - 1);
                graphicsManager.assignBufferData(
                        array[position].getVAOaddress(),
                        *(array[position].getVBOdata()),
                        array[position].getVBOaddress(),
                        *(array[position].getEBOdata()),
                        array[position].getEBOaddress(),
                        array[position].getTEXaddress()
                );
            }
        }
        // Adds the array to cells. This arrays is essentially the row of the grid.
        (Grid::cells).push_back(array);
    }

    // The { bracket below refuses to be indented correctly, deal with it Mrinaank.
    backgroundVertices = {
            // Background Grid
             0.2625f,  0.7625f, 0.0f,  0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f, // top right
             0.2625f, -0.7625f, 0.0f,  0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// bottom right
            -0.7625f, -0.7625f, 0.0f,  0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// bottom let
            -0.7625f,  0.7625f, 0.0f,  0.85f, 0.007f, 0.007f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// top left

            // Row 1
            -0.7375f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// top left
            -0.5125f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// top right
            -0.5125f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// bottom right
            -0.7375f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f, 0.0f,0.0f,// bottom left

            -0.4875f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,  0.0f,0.0f,// top left
            -0.2625f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,  0.0f,0.0f,// top right
            -0.2625f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,  0.0f,0.0f,// bottom right
            -0.4875f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 2
            -0.7375f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 3
            -0.7375f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 4
            -0.7375f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  -0.0125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  -0.2375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 5
            -0.7375f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  -0.2625f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  -0.4875f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            // Row 6
            -0.7375f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.5125f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.5125f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.7375f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.4875f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.2625f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.2625f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.4875f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            -0.2375f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            -0.0125f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            -0.0125f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            -0.2375f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left

            0.0125f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top left
            0.2375f,  -0.5125f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// top right
            0.2375f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom right
            0.0125f,  -0.7375f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,0.0f,0.0f,// bottom left
        };

    backgroundIndices = {
            0,1,3,
            1,2,3,

            // Row 1
            4,5,6,
            6,7,4,

            8,9,10,
            10,11,8,

            12,13,14,
            14,15,12,

            16,17,18,
            18,19,16,

            // Row 2
            20,21,22,
            22,23,20,

            24,25,26,
            26,27,24,

            28,29,30,
            30,31,28,

            32,33,34,
            34,35,32,

            // Row 3
            36,37,38,
            38,39,36,

            40,41,42,
            42,43,40,

            44,45,46,
            46,47,44,

            48,49,50,
            50,51,48,

            // Row 4
            52,53,54,
            54,55,52,

            56,57,58,
            58,59,56,

            60,61,62,
            62,63,60,

            64,65,66,
            66,67,64,

            // Row 5
            68,69,70,
            70,71,68,

            72,73,74,
            74,75,72,

            76,77,78,
            78,79,76,

            80,81,82,
            82,83,80,

            // Row 6
            84,85,86,
            86,87,84,

            88,89,90,
            90,91,88,

            92,93,94,
            94,95,92,

            96,97,98,
            98,99,96
    };


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

bool Grid::checkValid(int player)
{
    // Currently there are no valid moves
    bool valid = false;
    for (int row = 0; row < Grid::height; row++)
    {
        // Runs if the function has found an available move
        if (valid)
        {
            break;
        }
        else {
            for (int column = 0; column < Grid::width; column++)
            {
                Cell* inspectingCell = Grid::getCellAt(column, row);
                int cellOwner = inspectingCell->getPlayer();
                if (player ==  cellOwner){
                    valid = true;
                    break;
                }
            }
        }
    }
    return valid;
}

// Generates the display of the grid.
void Grid::renderDisplay()
{
    for(int y = 0; y < this->getHeight(); y++)
    {
        for (int x = 0; x < this->getWidth(); x++)
        {
            Cell* cell = Grid::getCellAt(x,y);
            cell->print();
        }
        std::cout << std::endl;
    }
}

// Checks if there is a winner by observing if all the other players lack a available move
bool Grid::checkWin(int players)
{
    // FD of array containing players with boolean values representing their ability to place a cell
    bool available[players];

    // Assigns false to each element in the array
    for (int index = 0; index < players; index++)
    {
        available[index] = false;
    }

    // Iterates through every cell within the grid and checks if every player owns at least 1 cell.
    // This is used over multiple Grid::checkValids() as this only requires iteration through the grid.
    for (int y = 0; y < this->getHeight(); y++)
    {
        for (int x = 0; x < this->getWidth(); x++)
        {
            // Gets the cell at the location
            Cell *cell = Grid::getCellAt(x, y);

            // Looks at owner of cell and determine if it is owned by a player
            int owner = cell->getPlayer();
            if (owner != 0)
            {
                // Sets corresponding player to true as they own at least 1 cell
                available[cell->getPlayer() - 1] = true;
            }
        }
    }


    // Number corresponding to the players still in the game
    int inGame = 0;

    // Iterates through available array and appends 1 for each player still in the game
    for (int index = 0; index < players; index++)
    {
        if (available[index])
        {
            inGame += 1;
        }
    }

    // Returns if there is 2 or more players still playing
    return (inGame >= 2);

};

std::vector<float>* Grid::getVBOData()
{
    return &backgroundVertices;
};

std::vector<unsigned int>* Grid::getEBOData()
{
    return &backgroundIndices;
};
// VAO, VBO, Textures

unsigned int* Grid::getVAOAddress()
{
    return &VAO;
};

unsigned int* Grid::getVBOAddress()
{
    return &VBO;
};

unsigned int* Grid::getEBOAddress()
{
    return &EBO;
};

void Grid::updateVBO(std::vector<float>* updatedArray)
{
    backgroundVertices = *updatedArray;
}

void Grid::renderGameGrid(GraphicsManager graphicsManager)
{
    graphicsManager.bindVertex(&VAO);

    graphicsManager.renderExternalData(backgroundIndices);

    graphicsManager.unbindVertex();
}
