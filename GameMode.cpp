/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: GameMode.cpp manipulates a given grid of cells to behave in a given
gamemode setting, such as classic, mirror, or doughnut. It will update the grid
and it's out edges and create the next generation.
*/
#include "GameMode.h"

//default constructor
GameMode :: GameMode(){
  gamemode = "classic";
  gameGrid = new CellGrid();
  oldGrid = gameGrid;
  ModeCheck(); //we need to set up the boundaries right away so the first count is accurate

}

//overloaded constructor
GameMode :: GameMode(string mode, CellGrid *newGrid){
  gamemode = mode;
  gameGrid = newGrid;
  oldGrid = gameGrid;
  ModeCheck(); //we need to set up the boundaries right away so the first count is accurate
}

//destructor (might delete if not used)
GameMode :: ~GameMode(){
  delete gameGrid;
}

//creates the next generation of the current grid
void GameMode :: NextGeneration(){
  CountAllNeighbors();
  UpdateGrid();
  ModeCheck();
}

//recounts all cell neighbors
void GameMode :: CountAllNeighbors(){
  for(int i=1; i<=oldGrid->GetGridWidth(); ++i){
    for(int j=1; j<=oldGrid->GetGridHeight(); ++j){
      oldGrid->CountNeighbors(i,j);
    }
  }
}

//applies correct updates that all grids must perform
void GameMode :: UpdateGrid(){
  int tempCount;
  for(int i=1; i<=gameGrid->GetGridWidth(); ++i){
    for(int j=1; j<=gameGrid->GetGridHeight(); ++j){
      tempCount = oldGrid->myGrid[i][j].GetNeightborCount();
      if(tempCount <= 1){
        gameGrid->myGrid[i][j].ChangeCell(false);
      } else if(tempCount == 3){
        gameGrid->myGrid[i][j].ChangeCell(true);
      } else if(tempCount >= 4){
        gameGrid->myGrid[i][j].ChangeCell(false);
      }//end of if/else statments
    }//end of j loop
  }//end of i loop
}

//checks what gamemode simulation is in and runs the right update for the outer cells
void GameMode :: ModeCheck(){
  if(gamemode == "classic"){
    UpdateClassicMode();
  } else if (gamemode == "mirror"){
    UpdateMirrorMode();
  } else if (gamemode == "doughnut"){
    UpdateDoughnutMode();
  }
  oldGrid = gameGrid;
}

//sets up boundaries for classic mode
void GameMode :: UpdateClassicMode(){
  //we wont need to change the outer boundaries at all, they will always be empty,
  //so nothing occurs here
}

//sets up boundaries for mirror mode
void GameMode :: UpdateMirrorMode(){
  //check all corner/edge pieces and reflect them onto extended cells
  for(int i=0; i<oldGrid->GetExtraWidth(); ++i){
    for(int j=0; j<oldGrid->GetExtraHeight(); ++j){
      //if corners
      if(i==1 && j==1){ //top left corner
        if (oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i-1][j-1].ChangeCell(true);
          gameGrid->myGrid[i][j-1].ChangeCell(true);
          gameGrid->myGrid[i-1][j].ChangeCell(true);
        } else {
          gameGrid->myGrid[i-1][j-1].ChangeCell(false);
          gameGrid->myGrid[i][j-1].ChangeCell(false);
          gameGrid->myGrid[i-1][j].ChangeCell(false);
        }
      } else if (i==1 && j == oldGrid->GetGridHeight()){ //bottom left corner
        if (oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i-1][j].ChangeCell(true);
          gameGrid->myGrid[i-1][j+1].ChangeCell(true);
          gameGrid->myGrid[i][j+1].ChangeCell(true);
        } else{
          gameGrid->myGrid[i-1][j].ChangeCell(false);
          gameGrid->myGrid[i-1][j+1].ChangeCell(false);
          gameGrid->myGrid[i][j+1].ChangeCell(false);
        }
      } else if (i==oldGrid->GetGridWidth() && j==1){ //top right corner
        if (oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i][j-1].ChangeCell(true);
          gameGrid->myGrid[i+1][j-1].ChangeCell(true);
          gameGrid->myGrid[i+1][j].ChangeCell(true);
        } else {
          gameGrid->myGrid[i][j-1].ChangeCell(false);
          gameGrid->myGrid[i+1][j-1].ChangeCell(false);
          gameGrid->myGrid[i+1][j].ChangeCell(false);
        }
      } else if (i==oldGrid->GetGridWidth() && j == oldGrid->GetGridHeight()){ //bottom right corner
        if (oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i][j+1].ChangeCell(true);
          gameGrid->myGrid[i+1][j+1].ChangeCell(true);
          gameGrid->myGrid[i+1][j].ChangeCell(true);
        } else {
          gameGrid->myGrid[i][j+1].ChangeCell(false);
          gameGrid->myGrid[i+1][j+1].ChangeCell(false);
          gameGrid->myGrid[i+1][j].ChangeCell(false);
        }
      //all edges
      } else if (i==1){ //along the top edge
        if(oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i-1][j].ChangeCell(true);
        } else {
          gameGrid->myGrid[i-1][j].ChangeCell(false);
        }
      } else if (j==1){ //along left edge
        if(oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i][j-1].ChangeCell(true);
        } else {
          gameGrid->myGrid[i][j-1].ChangeCell(false);
        }
      } else if (i==oldGrid->GetGridWidth()){ //along bottom edge
        if(oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i+1][j].ChangeCell(true);
        } else {
          gameGrid->myGrid[i+1][j].ChangeCell(false);
        }
      } else if (j==oldGrid->GetGridHeight()){ //along right edge
        if(oldGrid->myGrid[i][j].ContainsCell()){
          gameGrid->myGrid[i][j+1].ChangeCell(true);
        } else {
          gameGrid->myGrid[i][j+1].ChangeCell(false);
        }
      } //else, middle untouched
    }//end of j loop
  }//end of i loop
}//end of method

//sets up boundaries for doughnut mode
void GameMode :: UpdateDoughnutMode(){
  int bottomWid = gameGrid->GetGridWidth();
  int bottomHet = gameGrid->GetGridHeight();
  int extendedWid = gameGrid->GetExtraWidth();
  int extendedHet = gameGrid->GetExtraHeight();
  //each outter corner will match opposite corner
  //top left corner matches bottom right corner
  gameGrid->myGrid[0][0].ChangeCell((gameGrid->myGrid[bottomWid][bottomHet]).ContainsCell());
  //bottom left corner matches top right corner
  gameGrid->myGrid[0][extendedHet-1].ChangeCell(gameGrid->myGrid[bottomWid][1].ContainsCell());
  //top right corner matches bottom left corner
  gameGrid->myGrid[extendedWid-1][0].ChangeCell(gameGrid->myGrid[1][bottomHet].ContainsCell());
  //bottom right corner matches top left corner
  gameGrid->myGrid[extendedWid-1][extendedHet-1].ChangeCell(gameGrid->myGrid[1][1].ContainsCell());
  //iterate through all edges
  for(int i=1; i < bottomWid+1; ++i){
    for(int j=1; j < bottomHet+1; ++j){
      //top edge
      if(i==1){
        gameGrid->myGrid[0][j].ChangeCell(gameGrid->myGrid[bottomWid][j].ContainsCell());
      //left edge
      } if (j==1){
        gameGrid->myGrid[i][0].ChangeCell(gameGrid->myGrid[i][bottomHet].ContainsCell());
      //bottom edge
      } if (i==bottomWid){
        gameGrid->myGrid[i+1][j].ChangeCell(gameGrid->myGrid[1][j].ContainsCell());
      //right edge
      } if (j==bottomHet){
        gameGrid->myGrid[i][j+1].ChangeCell(gameGrid->myGrid[i][1].ContainsCell());
      }
    }
  }
}
