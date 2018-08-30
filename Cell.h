//
// Created by Michael Chen on 29/08/2018.
//
#ifndef NUCLEARMRINAANK_CELL_H
#define NUCLEARMRINAANK_CELL_H

//Cell
//    - buildUp() - public
//    - states - private int - changed by buildUp() - { 0 , 1 , 2 , 3 , 4 }
//    - adjacentLocation - array of pointers
//    - explode() - private, called by buildUp()

class Cell
{
public:
    Cell();
    void buildUp();

private:
    int states;
    int adjacentLocations[4];
    void explode();
};

#endif //NUCLEARMRINAANK_CELL_H
