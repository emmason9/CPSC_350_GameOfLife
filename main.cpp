/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: main.cpp is the main file that will run the Game of Life program.
*/
#include "Simulation.h"

int main(int argc, char** argv){

  Simulation *gameSim = new Simulation();

  gameSim->StartGame();

  delete gameSim;

}
