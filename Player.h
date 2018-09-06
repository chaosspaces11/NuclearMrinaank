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
    Player(int ID);
    int getID();
    bool checkActive();
    void setActive(bool state);

private:
    int ID;
    bool active;
};


#endif //NUCLEARMRINAANK_PLAYER_H
