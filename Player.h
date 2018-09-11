//
// Created by Michael Chen on 6/09/2018.
//

#ifndef NUCLEARMRINAANK_PLAYER_H
#define NUCLEARMRINAANK_PLAYER_H


#include <vector>
#include "Cell.h"

class Player
{
public:
    // Constructor, explicit avoids conversion of int to bool
    explicit Player(int ID);

    // Gets the id of the current player
    int getID();

    // Gets whether or not the player is still in the game
    bool checkActive();

    // Sets activity
    void setActive(bool state);

private:

    int ID;

    bool active;
};


#endif //NUCLEARMRINAANK_PLAYER_H
