//
// Created by yr12 on 4/9/18.
//

#ifndef NUCLEARMRINAANK_CORNERCELL_H
#define NUCLEARMRINAANK_CORNERCELL_H

#include "Cell.h"

class CornerCell: public Cell
{
public:
    CornerCell(int x, int y, int location);


private:
    int adjacentLocations[2][2];

    int unstableState;
};


#endif //NUCLEARMRINAANK_CORNERCELL_H
