//
// Created by Michael Chen on 6/09/2018.
//

#include "Player.h"

// Constructor function with active set to true.
Player::Player(int ID): ID(ID), active(true)
{

}

// Returning private variables
int Player::getID()
{
    return Player::ID;
}

// Returning private variables
bool Player::checkActive()
{
    return Player::active;
}

// Setting private variables
void Player::setActive(bool state)
{
    Player::active = state;
}