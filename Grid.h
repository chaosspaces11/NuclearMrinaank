//
// Created by Michael Chen on 30/08/2018.
//
#ifndef NUCLEARMRINAANK_GRID_H
#define NUCLEARMRINAANK_GRID_H

#include "Cell.h"
#include <vector>

class Grid
{
public:
    // Grid function that creates the width, height and amount of cells contained.
    Grid(int width, int height);

    // Returns the private variable cells-->USELESS?????
    int numCells();

    //Returns cell at location x,y
    static Cell getCellAt(int x, int y);

private:
    //declares height and width of grid
    const int height;
    const int width;

    //declares vector of cells
    static std::vector<std::vector<Cell> > cells;
};


#endif //NUCLEARMRINAANK_GRID_H
