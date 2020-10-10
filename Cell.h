/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: Cell.h is the header file for the Cell object. This declares all the
memeber variables and methods Cell.cpp will contain.
*/

#include <iostream>
using namespace std;

class Cell{
  public:
    Cell();
    Cell(bool HasCell);
    bool ContainsCell();
    char ShowCell();
    int GetNeightborCount();
    void SetNeighborCount(int count);
    void ChangeCell(bool cellBool);

  private:
    bool HasCell;
    int NeighborCount;

//#endif
};
