//
// Created by Michael Chen on 6/09/2018.
//

#ifndef NUCLEARMRINAANK_PLAYERMANAGER_H
#define NUCLEARMRINAANK_PLAYERMANAGER_H

#include "Cell.h"
#include "Grid.h"

class PlayerManager
{
    PlayerManager(int players);

    Cell* requestMove(int player, Grid mainGrid);

    bool checkPlayer(int x, int y);

    bool checkPosition(int x, int y, Grid mainGrid);

    void runRound();

private:
    int players;
    int currentPlayer;
};


#endif //NUCLEARMRINAANK_PLAYERMANAGER_H
