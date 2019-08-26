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

    // Max and minimum modulus for vector
    Cell::maxMod = 25;
    Cell::minMod = 5;

    // Max and minimum argument for vector
    Cell::maxArg = 360;
    Cell::minArg = 100;

    // Conditions noting whether the cell has been changed or exploded
    Cell::changed = false;
    Cell::exploding = false;

    // The stage of explosioin animation cycle
    Cell::animationTick = 0;

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

    // Randomizes the modulus and arguments of the cell
    Cell::randomizeSinhas();

    // Generates random x,y positions corresponting to the sinhas
    sinha1X = (float)(sinha1Mod * sin((double)sinha1Arg));
    sinha2X = (float)(sinha2Mod * sin((double)sinha2Arg));
    sinha3X = (float)(sinha3Mod * sin((double)sinha3Arg));
    sinha4X = (float)(sinha4Mod * sin((double)sinha4Arg));
    sinha1Y = (float)(sinha1Mod * sin((double)sinha1Arg));
    sinha2Y = (float)(sinha2Mod * sin((double)sinha2Arg));
    sinha3Y = (float)(sinha3Mod * sin((double)sinha3Arg));
    sinha4Y = (float)(sinha4Mod * sin((double)sinha4Arg));

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



};

void Cell::buildUp(int player)
{

    std::cout <<"Build up at (" << x + 1<< "," << y + 1 << ")!" << std::endl;

    // Changes ownership of the cell to current player
    if (player != Cell::player)
    {
        // Changes colour of the cell according to its new owner using switch cases.
        Cell::player = player;
        switch (player)
        {
            default:
                Cell::colour = {1.0f,1.0f,1.0f};
                break;
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

        // Updates cell data to correspond with colour change
        for (int vertice = 0; vertice < (sinhaVertices.size()/11); vertice++)
        {
            sinhaVertices[vertice*11 + 3] = colour[0];
            sinhaVertices[vertice*11 + 4] = colour[1];
            sinhaVertices[vertice*11 + 5] = colour[2];
        }
    }

    // Increases state
    Cell::state += 1;

    // If cell has not been changed before, it is now flagged as changed
    if (!(Cell::changed))
    {
        Cell::toggleChanged();
    }

    // Cell has exceeded maximum state then set exploding to true, note there is a case in which a cell can reach 5 sinhas
    // hence the >=
    if (Cell::state >= Cell::unstableState)
    {
        Cell::exploding = true;
    }
}

// Explode function that is called to distribute Sinhas to nearby cells.
void Cell::beginExploding()
{
    Cell::queued = true;
    std::cout <<"Explosion at (" << x + 1<< "," << y + 1<< ")!" << std::endl;
    Cell::explodeAnimation();
}

// Current 2D GUI
void Cell::print()
{
    std::cout << "\x1b[3" << Cell::player << "m " << Cell::state << " \x1b[0m";
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

// Getting address for the data buffer
unsigned int* Cell::getVAOaddress()
{
    return &(Cell::VAOaddress);
}

// Getting address for the sinhaVertices buffer
unsigned int* Cell::getVBOaddress()
{
    return &(Cell::VBOaddress);
}

// Getting address for the sinhaIndices buffer
unsigned int* Cell::getEBOaddress()
{
    return &(Cell::EBOaddress);
}

// Getting address for the texture buffer
unsigned int* Cell::getTEXaddress()
{
    return &(Cell::TEXaddress);
}

// Getting VBO data, sinhaVertices
std::vector<float>* Cell::getVBOdata()
{
    return &(Cell::sinhaVertices);
}

// Getting EBO data, sinhaIndices
std::vector<unsigned int>* Cell::getEBOdata()
{
    return &(Cell::sinhaIndices);
}

// Rendering the sinhas within the cell
void Cell::renderSinhas(GraphicsManager graphicsManager)
{
    // Attaches data buffer
    graphicsManager.bindVertex(Cell::getVAOaddress());

    // Attaches texture buffer
    graphicsManager.bindTexture(*(Cell::getTEXaddress()));

    // Renders the data using the EBO data and the number of sinhas to render
    graphicsManager.renderExternalData(*(Cell::getEBOdata()), Cell::state);

    // Unbinds the data buffer
    graphicsManager.unbindVertex();
}

// Randomizes rotation size
void Cell::randomizeSinhas()
{
    // Creates a seed for randomisation
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 1000.0);

    // Essentially generates a random modulus and argument for each sinha
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

// Returns animation vector for each adjacent cell to render the explosion animation
std::vector< std::vector <float> > Cell::getAnimationVectors()
{
    // Temporary storage for the animaiton vectors
    std::vector< std::vector<float>> sideVectors;

    // For each sinha for distribution
    for (int i = 0; i < unstableState; i++)
    {
        // Generates a side vector for each
        std::vector<float> appendingVector = {(float)(adjacentLocations[i][0] - x)/1000,(float)(adjacentLocations[i][1] - y)/1000, 0.0f};
        sideVectors.push_back(appendingVector);
    }
    return sideVectors;

}

void Cell::explodeAnimation()
    {
    Cell::exploding = true;
    std::vector<std::vector<float>> animationVectors = Cell::getAnimationVectors();
    Cell::swappingBuffer = {};
    for (int i = 0; i < animationVectors.size(); i++)
    {
        Cell::swappingBuffer.push_back({Cell::sinhaVertices[i*11+8],Cell::sinhaVertices[i*11+9]});
        for (int a = 0; a < 4; a++)
        {

            Cell::sinhaVertices[(i*4+a)*11+8] = animationVectors[i][0];
            Cell::sinhaVertices[(i*4+a)*11+9] = animationVectors[i][1];
        }
    }
    updateGraphicsData();
    GraphicsManager::renderExternalData(sinhaIndices);
}

void Cell::updateGraphicsData()
{
    GraphicsManager::updateBufferData(&VAOaddress, &VBOaddress, sinhaVertices);
}

void Cell::toggleChanged()
{
    Cell::changed = !Cell::changed;
}

bool Cell::getChanged()
{
    return Cell::changed;
}

void Cell::resetOwner()
{
    Cell::player = 0;
}

bool Cell::getExploding()
{
    return Cell::exploding;
}

void Cell::finishExploding()
{


    Cell::exploding = false;
    Cell::queued = false;
    Cell::distributeSinhas();
    Cell::state -= Cell::unstableState;

    //TODO: Stick swap buffer data back into sinhaVertices;
    Cell::randomizeSinhas();

    float sinha1X = (float)(sinha1Mod * sin((double)sinha1Arg));
    float sinha2X = (float)(sinha2Mod * sin((double)sinha2Arg));
    float sinha3X = (float)(sinha3Mod * sin((double)sinha3Arg));
    float sinha4X = (float)(sinha4Mod * sin((double)sinha4Arg));
    float sinha1Y = (float)(sinha1Mod * sin((double)sinha1Arg));
    float sinha2Y = (float)(sinha2Mod * sin((double)sinha2Arg));
    float sinha3Y = (float)(sinha3Mod * sin((double)sinha3Arg));
    float sinha4Y = (float)(sinha4Mod * sin((double)sinha4Arg));

    Cell::swappingBuffer = {{sinha1X,sinha1Y},{sinha2X,sinha2Y},{sinha3X,sinha3Y},{sinha4X,sinha4Y}};

    for (int i = 0; i < Cell::swappingBuffer.size(); i++)
    {
        for (int a = 0; a < 4; a++)
        {
            Cell::sinhaVertices[(i*4+a)*11+8] = Cell::swappingBuffer[i][0];
            Cell::sinhaVertices[(i*4+a)*11+9] = Cell::swappingBuffer[i][1];
        }

    }
    Cell::animationTick = 0;

}

void Cell::distributeSinhas()
{
    for (int i = 0; i < Cell::unstableState;i++)
    {
        // Takes cell pointer of the adjacent cells
        Cell* adjacentCell = Grid::getCellAt(adjacentLocations[i][0],adjacentLocations[i][1]);

        // Runs buildUp function on the cell.
        adjacentCell->buildUp(Cell::player);
    }
}

void Cell::incrementAnimation()
{
    Cell::animationTick ++;
}

int Cell::getAnimationTick()
{
    return Cell::animationTick;
}

bool Cell::getQueued()
{
    return Cell::queued;
}
