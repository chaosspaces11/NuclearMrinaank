//
// Created by Michael Chen on 6/09/2018.
//

#ifndef NUCLEARMRINAANK_PLAYERMANAGER_H
#define NUCLEARMRINAANK_PLAYERMANAGER_H

#include "Cell.h"
#include "Grid.h"
#include "Player.h"

class PlayerManager
{
public:
    PlayerManager(int numPlayers);

    Cell* requestMove(int player, Grid mainGrid);

    bool checkPlayer(int x, int y);

    bool checkPosition(int x, int y, Grid mainGrid);

    void iteratePlayer(Grid mainGrid);

private:
    int numPlayers;
    int currentPlayer;
    std::vector <Player> players;
};


#endif //NUCLEARMRINAANK_PLAYERMANAGER_H
