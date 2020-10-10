/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: GameMode.h is the header file for the GameMode class. This declares all the
memeber variables and methods GameMode.cpp will contain.
*/

#ifndef CELLGRID_H
#define CELLGRID_H
#include "CellGrid.h"

class CellGrid;
class GameMode{
  public:
    CellGrid *gameGrid;
    CellGrid *oldGrid;
    GameMode();
    GameMode(string mode, CellGrid *newGrid);
    ~GameMode();

    void ModeCheck();
    void NextGeneration();

    void UpdateClassicMode();
    void UpdateMirrorMode();
    void UpdateDoughnutMode();
    void UpdateGrid();
    void CountAllNeighbors(); 

  private:
    string gamemode;

#endif
};
