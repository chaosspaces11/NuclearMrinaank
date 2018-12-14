//
// Created by Michael Chen on 30/08/2018.
//
#include <iostream>
#include "Grid.h"
#include "CornerCell.h"
#include "SideCell.h"
#include "Cell.h"

//defining static vector Grid::cells
std::vector<std::vector<Cell> > Grid::cells;
std::vector<float> backgroundVertices;
std::vector<unsigned int> backgroundIndices;

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
                array.emplace_back( Cell(col,row));
            }
        }
        // Adds the array to cells. This arrays is essentially the row of the grid.
        cells.push_back(array);
    }

    std::vector<float> backgroundVertices = {// Coordinate vectors     Colour Vectors      Texture Vectors
             1.0f, 1.0f, 1.0f,      1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner
          1.0f, -1.0f, 1.0f,     1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner
          -1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left corner
          -1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top left corner

          0.975f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
          0.975f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

          1.0f, 0.975f, 1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
          -1.0f, 0.975f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

          -0.975f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
          -0.975f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom right corner gridded

          -1.0f, -0.975f, 1.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right corner gridded
          1.0f, -0.975f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f // bottom right corner gridded
    };

    std::vector<unsigned int> backgroundIndices = {
            0,1,4,
            5,4,1,
            6,3,7,
            6,3,0,
            8,3,9,
            9,3,2,
            10,2,1,
            11,1,10
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

}