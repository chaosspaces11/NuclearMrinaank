//
// Created by Michael Chen on 6/09/2018.
//

#include "Player.h"

Player::Player(int ID): ID(ID)
{
}

int Player::getID()
{
    return Player::ID;
}

bool Player::checkActive()
{
    return Player::active;
}

void Player::setActive(bool state)
{
    Player::active = state;
}