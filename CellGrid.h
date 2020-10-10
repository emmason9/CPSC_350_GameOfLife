/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: This is the header class for the CellGrid object. The CellGrid is an
array of cells with various functions that help analyze and change the cells
given the right conditions.
*/

#ifndef  CELL_H
#define CELL_H
#include "Cell.h"

class Cell;
class CellGrid{
  public:
    CellGrid();
    CellGrid(int width, int height);
    CellGrid(int Width, int Height, double PopDens);
    CellGrid(int width, int height, string map[]);
    ~CellGrid();
    CellGrid* CopyGrid();

    void GridPrint();
    string FilePrint();

    int CountNeighbors(int widthPos, int heightPos);
    int GetExtraWidth();
    int GetExtraHeight();
    int GetGridWidth();
    int GetGridHeight();

    bool isEmpty();
    bool CompareSame(CellGrid* testGrid);
    
    Cell** myGrid; //made public just so it's easily accessable to the GameMode class

  private:
    int gridWidth;
    int gridHeight;
    int extraWidth;
    int extraHeight;
    double InitialPopulationDensity;

    Cell** MakeArray(int width, int height);
    void DeleteArray(Cell** Array, int width);
    void FillRandomGrid();
    void FillMapGrid(string map[]);


#endif
};
