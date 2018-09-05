//
// Created by Michael Chen on 4/09/2018.
//

#ifndef NUCLEARMRINAANK_SIDECELL_H
#define NUCLEARMRINAANK_SIDECELL_H

#include "Cell.h"

class SideCell : public Cell{

public:
    SideCell(int x, int y, int location);

private:
    int adjacentLocations[3][2];
};


#endif //NUCLEARMRINAANK_SIDECELL_H
