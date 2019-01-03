#include <iostream>
#include <random>
#include "Cell.h"
#include "Grid.h"
#include "GraphicsManager.h"
#include "math.h"

Cell::Cell(int x, int y)
{


    // Test output statements
//    std::cout << "Cell file linked successfully" << std::endl;
//    std::cout << "X: " << x << " Y: " << y << std::endl;

    // Variable initialisation for the default cell
    Cell::x = x;
    Cell::y = y;
    Cell::state = 0;
    Cell::unstableState = 4;
    Cell::player = 0;

    Cell::maxMod = 25;
    Cell::minMod = 5;

    Cell::maxArg = 360;
    Cell::minArg = 100;

    // Graphics related initialisation
    float size = 0.125;
    float leftX,rightX,topY,bottomY;

    float sinha1X, sinha2X, sinha3X, sinha4X;
    float sinha1Y, sinha2Y, sinha3Y, sinha4Y;

    // Initialises the location of the cells around the initialised cell
    Cell::adjacentLocations[0][0] = x;
    Cell::adjacentLocations[0][1] = y - 1;

    Cell::adjacentLocations[1][0] = x + 1;
    Cell::adjacentLocations[1][1] = y;

    Cell::adjacentLocations[2][0] = x;
    Cell::adjacentLocations[2][1] = y + 1;

    Cell::adjacentLocations[3][0] = x - 1;
    Cell::adjacentLocations[3][1] = y;

    // Positions defining the corners of a sinha square.
    leftX =   (float)(-0.625 - size/2 + (0.25 * x));
    rightX =  (float)(-0.625 + size/2 + (0.25 * x));
    topY =    (float)(0.625 + size/2 - (0.25 * y));
    bottomY = (float)(0.625 - size/2 - (0.25 * y));

    // Colour for all sinhas within cell
    Cell::colour = {1.0f, 0.0f, 0.0f};

    Cell::randomizeSinhas();

//    std::cout << Cell::sinha1Mod << " " << Cell::sinha1Arg;
    sinha1X = (float)(sinha1Mod * sin((double)sinha1Arg));
    sinha2X = (float)(sinha2Mod * sin((double)sinha2Arg));
    sinha3X = (float)(sinha3Mod * sin((double)sinha3Arg));
    sinha4X = (float)(sinha4Mod * sin((double)sinha4Arg));
    sinha1Y = (float)(sinha1Mod * sin((double)sinha1Arg));
    sinha2Y = (float)(sinha2Mod * sin((double)sinha2Arg));
    sinha3Y = (float)(sinha3Mod * sin((double)sinha3Arg));
    sinha4Y = (float)(sinha4Mod * sin((double)sinha4Arg));

//    std::cout << "Sinha 1 Randomised Values X:" << sinha1X << " Y: " << sinha1Y << std::endl;


    // Data to be inputted into the VBO for rendering.
    Cell::sinhaVertices =
            {
            //  Position, 3 elements   Colour, 3 elements                                 Texture, 2 elements, Centre Shift, 3 elements, Unit Vector,
                leftX,  topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f,          sinha1X, sinha1Y, 0.0f, // 1.0f,
                rightX, topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f,          sinha1X, sinha1Y, 0.0f, // 1.0f,
                rightX, bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f,          sinha1X, sinha1Y, 0.0f, // 1.0f,
                leftX,  bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.0f,          sinha1X, sinha1Y, 0.0f, // 1.0f,

                leftX,  topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f,          sinha2X, sinha2Y, 0.0f, // 1.0f,
                rightX, topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f,          sinha2X, sinha2Y, 0.0f, // 1.0f,
                rightX, bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f,          sinha2X, sinha2Y, 0.0f, // 1.0f,
                leftX,  bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.0f,          sinha2X, sinha2Y, 0.0f, // 1.0f,

                leftX,  topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f,          sinha3X, sinha3Y, 0.0f, // 1.0f,
                rightX, topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f,          sinha3X, sinha3Y, 0.0f, // 1.0f,
                rightX, bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f,          sinha3X, sinha3Y, 0.0f, // 1.0f,
                leftX,  bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.0f,          sinha3X, sinha3Y, 0.0f, // 1.0f,

                leftX,  topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f,          sinha4X, sinha4Y, 0.0f, // 1.0f,
                rightX, topY,    0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f,          sinha4X, sinha4Y, 0.0f, // 1.0f,
                rightX, bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f,          sinha4X, sinha4Y, 0.0f, // 1.0f,
                leftX,  bottomY, 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.0f,          sinha4X, sinha4Y, 0.0f, // 1.0f
            };

    // Outlines how the each row within sinhaVertices should be connected.
    Cell::sinhaIndices =
            {
                // Sinha 1
                0,1,2,
                2,3,0,

                // Sinha 2
                4,5,6,
                6,7,4,

                // Sinha 3
                8,9,10,
                10,11,8,

                // Sinha 4
                12,13,14,
                14,15,12
            };

    getAnimationVectors();
};

void Cell::buildUp(int player)
{

    std::cout <<"Build up at (" << x + 1<< "," << y + 1 << ")!" << std::endl;

    // Changes ownership of the cell to current player
    if (player != Cell::player)
    {
        Cell::player = player;
        switch (player)
        {
            default:
            case 1:
                Cell::colour = {1.0f, 0.0f, 0.0f};
                break;
            case 2:
                Cell::colour = {0.0f, 1.0f, 0.0f};
                break;
            case 3:
                Cell::colour = {0.0f, 0.0f, 1.0f};
                break;
            case 4:
                Cell::colour = {1.0f, 1.0f, 0.0f};
                break;

        }

        for (int vertice = 0; vertice < (sinhaVertices.size()/11); vertice++)
        {
            sinhaVertices[vertice*11 + 3] = colour[0];
            sinhaVertices[vertice*11 + 4] = colour[1];
            sinhaVertices[vertice*11 + 5] = colour[2];
        }
    }

    // Increases state
    Cell::state += 1;

    // Cell has exceeded maximum state
    if (Cell::state == Cell::unstableState)
    {
        Cell::explode();
        Cell::randomizeSinhas();
    }

    // Should never happen unless an error has occured
    else if (Cell::state > Cell::unstableState)
    {
        std::cout << "ERROR: Cell exceeded maximum stack without exploding." << std::endl;
    }
}

// Explode function that is called to distribute Sinhas to nearby cells.
void Cell::explode()
{
    // Setting the state to 0 as it has distributed all Sinhas
    Cell::state = 0;


    std::cout <<"Explosion at (" << x + 1<< "," << y + 1<< ")!" << std::endl;

    // For each Sinha within cell, distribute one to each neighbouring cell
    for (int i = 0; i < Cell::unstableState;i++)
    {
        // Takes cell pointer of the adjacent cells
        Cell* adjacentCell = Grid::getCellAt(adjacentLocations[i][0],adjacentLocations[i][1]);

        // Runs buildUp function on the cell.
        adjacentCell->buildUp(Cell::player);
    }
}

// Current 2D GUI
void Cell::print()
{
    std::cout << "\x1b[3" << Cell::player << "m " << Cell::state << " \x1b[0m";
//    std::cout << "Cell: X: " << x << " Y: " << y << " State: " << Cell::state << std::endl;
}

// Returns the owner of the cell
int Cell::getPlayer()
{
    return Cell::player;
}

int Cell::getX()
{
    return Cell::x;
}

int Cell::getY()
{
    return Cell::y;
}

unsigned int* Cell::getVAOaddress()
{
    return &(Cell::VAOaddress);
}

unsigned int* Cell::getVBOaddress()
{
    return &(Cell::VBOaddress);
}

unsigned int* Cell::getEBOaddress()
{
    return &(Cell::EBOaddress);
}

unsigned int* Cell::getTEXaddress()
{
    return &(Cell::TEXaddress);
}

std::vector<float>* Cell::getVBOdata()
{
    return &(Cell::sinhaVertices);
}

std::vector<unsigned int>* Cell::getEBOdata()
{
    return &(Cell::sinhaIndices);
}

std::vector<float> Cell::getColour()
{
    return Cell::colour;
}

void Cell::renderSinhas(GraphicsManager graphicsManager)
{
    graphicsManager.bindVertex(Cell::getVAOaddress());

    graphicsManager.bindTexture(*(Cell::getTEXaddress()));

    graphicsManager.renderExternalData(*(Cell::getEBOdata()), Cell::state);

    graphicsManager.unbindVertex();
}


void Cell::randomizeSinhas()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 1000.0);
    Cell::sinha1Mod = (float)(((int)(dist(mt)) % Cell::maxMod) + Cell::minMod)/1000;
    Cell::sinha2Mod = (float)((((int)dist(mt)) % Cell::maxMod) + Cell::minMod)/1000;
    Cell::sinha3Mod = (float)((((int)dist(mt)) % Cell::maxMod) + Cell::minMod)/1000;
    Cell::sinha4Mod = (float)((((int)dist(mt)) % Cell::maxMod) + Cell::minMod)/1000;

    Cell::sinha1Arg = (float)((((int)dist(mt)) % Cell::maxArg) + Cell::minArg);
    Cell::sinha2Arg = (float)((((int)dist(mt)) % Cell::maxArg) + Cell::minArg);
    Cell::sinha3Arg = (float)((((int)dist(mt)) % Cell::maxArg) + Cell::minArg);
    Cell::sinha4Arg = (float)((((int)dist(mt)) % Cell::maxArg) + Cell::minArg);
}

int Cell::getState()
{
    return Cell::state;
}

int* Cell::getAdjacentLocations()
{
    return &(adjacentLocations[0][0]);
}

std::vector< std::vector <float> > Cell::getAnimationVectors()
{
    std::vector< std::vector<float>> sideVectors;
    for (int i = 0; i < unstableState; i++)
    {
        std::vector<float> appendingVector = {(float)(adjacentLocations[i][0] - x)/1000,(float)(adjacentLocations[i][1] - y)/1000, 0.0f};
        sideVectors.push_back(appendingVector);
    }
    return sideVectors;

}

void Cell::explodeAnimation()
{
    std::vector<std::vector<float>> animationVectors = Cell::getAnimationVectors();
    for (int i = 0; i < animationVectors.size(); i++)
    {


    }
}

void Cell::updateGraphicsData(GraphicsManager graphicsManager)
{
    graphicsManager.updateBufferData(&VAOaddress, &VBOaddress, sinhaVertices);
}