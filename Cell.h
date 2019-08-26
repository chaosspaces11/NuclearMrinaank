//
// Created by Michael Chen on 29/08/2018.
//
#ifndef NUCLEARMRINAANK_CELL_H
#define NUCLEARMRINAANK_CELL_H

#include <iostream>
#include <vector>
#include "GraphicsManager.h"

//class GraphicsManager;

class Cell
{
public:
    // Constructor that takes X and Y coordinates and sets up private variables.
    Cell(int x, int y);

    // Increments private variable 'states' by 1, calls explode function if maximum amount of states is reached.
    void buildUp(int player);

    //prints out the cell in a grid
    void print();

    //getPlayer number
    int getPlayer();

    //gets X
    int getX();

    //gets Y
    int getY();

    //
    void renderSinhas(GraphicsManager graphicsManager);

    unsigned int* getVAOaddress();
    unsigned int* getVBOaddress();
    unsigned int* getEBOaddress();
    unsigned int* getTEXaddress();

    std::vector<float>* getVBOdata();
    std::vector<unsigned int>* getEBOdata();

    int getState();

//    int* getAdjacentLocations();

    std::vector < std::vector <float> > getAnimationVectors();

    void explodeAnimation();

    void updateGraphicsData();

    void toggleChanged();

    bool getChanged();

    void resetOwner();

    bool getExploding();

    void finishExploding();

    void distributeSinhas();

    void incrementAnimation();

    int getAnimationTick();

    bool getQueued();

    void beginExploding();

//private:

    // Protected allows for child classes to access the attribute
protected:
    // Amount of objects within the cell
    int state;

    //player
    int player;

    // X coordinate
    int x;

    // Y coordinate
    int y;

    //State where it explodes
    int unstableState;

    // Array of the adjacent cells
    int adjacentLocations[4][2];

    unsigned int VAOaddress;
    unsigned int EBOaddress;
    unsigned int VBOaddress;
    unsigned int TEXaddress;

    std::vector<float> sinhaVertices;
    std::vector<unsigned int> sinhaIndices;
    std::vector<float> colour;

    float sinha1Mod, sinha2Mod, sinha3Mod, sinha4Mod;
    float sinha1Arg, sinha2Arg, sinha3Arg, sinha4Arg;

    int maxMod, minMod;
    int maxArg, minArg;

    void randomizeSinhas();

    bool changed;
    bool exploding;

    std::vector<std::vector<float>> swappingBuffer;

    int animationTick;

    bool queued;

};

#endif //NUCLEARMRINAANK_CELL_H
