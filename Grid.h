//
// Created by Michael Chen on 30/08/2018.
//
#ifndef NUCLEARMRINAANK_GRID_H
#define NUCLEARMRINAANK_GRID_H

#include "Cell.h"
#include <vector>
#include "SideCell.h"
#include "CornerCell.h"

class Grid
{
public:
    // Grid function that creates the width, height and amount of cells contained.
    Grid(int width, int height);

    //Returns cell at location x,y
    static Cell* getCellAt(int x, int y);

    int getHeight();

    int getWidth();

    bool checkValid(int player);

private:
    //declares height and width of grid
    const int height;
    const int width;

    //declares vector of cells
    static std::vector<std::vector<Cell> > cells;
};

// Function input a,b
// Outputs pointer

#endif //NUCLEARMRINAANK_GRID_H
