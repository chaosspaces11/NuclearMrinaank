//
// Created by Michael Chen on 29/08/2018.
//
#ifndef NUCLEARMRINAANK_CELL_H
#define NUCLEARMRINAANK_CELL_H

class Cell
{
public:
    // Constructor that takes X and Y coordinates and sets up private variables.
    Cell(int x, int y);

    // Increments private variable 'states' by 1, calls explode function if maximum amount of states is reached.
    void buildUp();

private:
    // Amount of objects within the cell
    int state;

    //State where it explodes
    int unstableState;

    // X coordinate
    int x;

    // Y coordinate
    int y;

    // Array of the adjacent cells
    int adjacentLocations[4][2];

    // Distributes objects within current cell to adjacent cells
    void explode();
};

#endif //NUCLEARMRINAANK_CELL_H
