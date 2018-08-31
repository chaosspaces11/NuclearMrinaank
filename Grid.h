//
// Created by Michael Chen on 30/08/2018.
//

#ifndef NUCLEARMRINAANK_GRID_H
#define NUCLEARMRINAANK_GRID_H


class Grid
{
public:
    // Grid function that creates the width, height and amount of cells contained.
    Grid(int width, int height);

    // Returns the private variable cells
    int numCells();

private:
    int width;
    int height;
    int cells;
};


#endif //NUCLEARMRINAANK_GRID_H
