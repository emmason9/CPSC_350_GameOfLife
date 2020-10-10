/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: Cell.cpp creates a Cell object that has member variables that tell
whether the cell actually exists/is contained or not, as well as the amount out
neighbors surrounding the cell.
*/

#include "Cell.h"

//default constructor
Cell :: Cell(){
      HasCell = false;
      NeighborCount = 0;
    }

//overloaded constructor
Cell :: Cell(bool cell){
      HasCell = cell;
      NeighborCount = 0;
    }

//returns bool is the cell exists/contains a cell
bool Cell :: ContainsCell(){
      return HasCell;
    }

//returns a char that'll indicate whether the cell is present or not
char Cell :: ShowCell(){
      if(ContainsCell()){
        return 'X';
      } else {
        return 'O';
      }
    }

//returns int of number of neighbors surrounding cell
int Cell :: GetNeightborCount(){
      return NeighborCount;
    }

//sets the number of neighbors surrounding cell
void Cell :: SetNeighborCount(int count){
      NeighborCount = count;
    }

//changes whether a cell is contained/exists or not
void Cell :: ChangeCell(bool cellBool){
  HasCell = cellBool;
}
