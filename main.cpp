#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "Debug.h"


int main()
{
    Grid mainGrid(5,5);


    Cell test = Grid::getCellAt(1,3);
    test.print();
    return 0;
}