//
// Created by Michael Chen on 30/08/2018.
//
#ifndef NUCLEARMRINAANK_GRID_H
#define NUCLEARMRINAANK_GRID_H

#include "Cell.h"
#include <vector>
#include "SideCell.h"
#include "CornerCell.h"

#include "GraphicsManager.h"

//class GraphicsManager;

class Grid
{
public:
    // Grid function that creates the width, height and amount of cells contained.
    Grid(int width, int height, GraphicsManager graphicsManager);

    //Returns cell at location x,y
    static Cell* getCellAt(int x, int y);

    int getHeight();

    int getWidth();

    bool checkValid(int player);

    void renderDisplay();

    bool checkWin(int players);

    // Graphics
    std::vector<float>* getVBOData();
    std::vector<unsigned int>* getEBOData();
    unsigned int* getVAOAddress();
    unsigned int* getVBOAddress();
    unsigned int* getEBOAddress();

    void renderGameGrid(GraphicsManager graphicsManager);

    void updateVBO(std::vector<float>* updatedArray);

private:
    //declares height and width of grid
    const int height;
    const int width;

    // Graphics
    std::vector<float> backgroundVertices;
    std::vector<unsigned int> backgroundIndices;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    //declares vector of cells
    static std::vector<std::vector<Cell>> cells;
};

#endif //NUCLEARMRINAANK_GRID_H
