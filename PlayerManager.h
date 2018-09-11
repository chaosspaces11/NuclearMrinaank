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

    // Constructor
    explicit PlayerManager(int numPlayers);

    // Requests move from player
    Cell* requestMove(int player, Grid mainGrid);

    // Check if cell can be placed on by current player
    bool checkPlayer(int x, int y);

    // Check is cell is a valid position
    bool checkPosition(int x, int y, Grid mainGrid);

    // Runs the turn of the current player
    void iteratePlayer(Grid mainGrid);

    // Returning private variables
    int getPlayers();

    bool getInitialRound();

    int getCurrentPlayer();

private:

    int numPlayers;

    bool initialRound;

    int playerIndex;

    std::vector <Player> players;
};


#endif //NUCLEARMRINAANK_PLAYERMANAGER_H
