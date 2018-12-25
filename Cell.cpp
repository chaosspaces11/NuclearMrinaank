#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include "GraphicsManager.h"

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
    float size = 0.125;

    // Initialises the location of the cells around the initialised cell
    Cell::adjacentLocations[0][0] = x;
    Cell::adjacentLocations[0][1] = y - 1;

    Cell::adjacentLocations[1][0] = x + 1;
    Cell::adjacentLocations[1][1] = y;

    Cell::adjacentLocations[2][0] = x;
    Cell::adjacentLocations[2][1] = y + 1;

    Cell::adjacentLocations[3][0] = x - 1;
    Cell::adjacentLocations[3][1] = y;

    Cell::colour = {1.0f, 0.0f, 0.0f};
    Cell::sinhaVertices =
            {
                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f, 0.01f, 0.01f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f, 0.01f, 0.01f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f, 0.01f, 0.01f, 0.0f,
                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.01f,0.01f, 0.01f, 0.0f,

                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f, 0.02f, 0.02f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f, 0.02f, 0.02f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f, 0.02f, 0.02f, 0.0f,
                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.01f,0.02f, 0.02f, 0.0f,

                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f, 0.03f, 0.03f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f, 0.03f, 0.03f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f, 0.03f, 0.03f, 0.0f,
                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.01f, 0.03f, 0.03f, 0.0f,

                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 1.0f, 0.04f, 0.04f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 + size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 1.0f, 0.04f, 0.04f, 0.0f,
                (float)(-0.625 + size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 1.0f, 0.0f, 0.04f, 0.04f, 0.0f,
                (float)(-0.625 - size/2 + (0.25 * x)), (float)(0.625 - size/2 - (0.25 * y)), 0.0f, Cell::colour[0], Cell::colour[1], Cell::colour[2], 0.0f, 0.01f, 0.04f, 0.04f, 0.0f,
            };
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

//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true);
//    Cell::texture1 = ;
//    unsigned char *data = stbi_load("../NuclearMrinaank_Icon_SinhaDefault.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
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

    graphicsManager.renderExternalData(*(Cell::getEBOdata()), Cell::state);

    graphicsManager.unbindVertex();
}



