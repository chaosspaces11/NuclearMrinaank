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
    void buildUp(int player);

    //prints out the cell in a grid
    void print();

    //getPlayer number
    int getPlayer();

    //gets X
    int getX();

    //gets Y
    int getY();

private:

    // Protected allows for child classes to access the attribute
protected:
    // Amount of objects within the cell
    int state;

    //player
    int player;

    // X coordinate
    int x;

    // Y coordinate
    int y;

    // Distributes objects within current cell to adjacent cells
    virtual void explode();

    //State where it explodes
    int unstableState;

    // Array of the adjacent cells
    int adjacentLocations[4][2];
};

#endif //NUCLEARMRINAANK_CELL_H
