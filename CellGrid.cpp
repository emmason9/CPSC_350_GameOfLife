/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: CellGrid.cpp contains all the functionallity that an array of cells would
need to function within the Game of Life, such as creating a dynamic array of cells,
filling the grid with the appropirate information, printing the grid/array
accurately, checking if a grid is empty, and comparing two grids.
*/

#include "CellGrid.h"

//default constructor
CellGrid :: CellGrid(){
  myGrid = MakeArray(5,5);
  gridWidth = 5;
  gridHeight = 5;
  extraWidth = 7;
  extraHeight = 7;
  InitialPopulationDensity = 0.5;
}

//default constructor for given just height and width, just for copy grid to make new object
CellGrid :: CellGrid(int width, int height){
  gridWidth = width;
  gridHeight = height;
  extraWidth = width+2;
  extraHeight = height+2;
  myGrid = MakeArray(extraWidth,extraHeight);
}

//overloaded constructor for randomized grid
CellGrid :: CellGrid(int width, int height, double popDens){
  gridWidth = width;
  gridHeight = height;
  extraWidth = width+2;
  extraHeight = height+2;
  InitialPopulationDensity = popDens;
  myGrid = MakeArray(extraWidth,extraHeight);
  FillRandomGrid();
}

//constructor for mapped grid
CellGrid :: CellGrid(int width, int height, string gridMap[]){
  gridWidth = width;
  gridHeight = height;
  extraWidth = width+2;
  extraHeight = height+2;
  myGrid = MakeArray(extraWidth,extraHeight);
  FillMapGrid(gridMap);
}

//destructor
CellGrid :: ~CellGrid(){
  DeleteArray(myGrid, extraWidth);
}

//copy constructor
CellGrid* CellGrid :: CopyGrid(){
  CellGrid *newGrid = new CellGrid(gridWidth, gridHeight);
  for(int i=0; i<extraWidth; ++i){
    for(int j=0; j<extraHeight; ++j){
      newGrid->myGrid[i][j].ChangeCell(this->myGrid[i][j].ContainsCell());
    }
  }
  return newGrid;
}

//creates grid dynamically
Cell** CellGrid :: MakeArray(int givenwidth, int givenheight){
  Cell** newGrid = new Cell*[givenwidth];
  int temp = 0;
  for(int i=0; i < givenwidth; ++i){
    newGrid[i] = new Cell[givenheight];
  }
  return newGrid;
}

//destories dynamic grid
void CellGrid :: DeleteArray(Cell** Array, int width){
  for(int i=0; i < width; ++i){
    delete[] Array[i];
  }
  delete[] Array;
}

//fills grid randomly
void CellGrid :: FillRandomGrid(){ //random filling grid
  //want to run through random number generater and place cells in random spots on grid
  //until population InitialPopulationDensity is reached
  double totalArea = gridHeight * gridWidth;
  double totalCells = 0;
  int randomWidth;
  int randomHeight;
  while(InitialPopulationDensity > (totalCells/totalArea)){
    //grabing random location in array
    srand(time(0));
    randomWidth = rand()%((gridWidth-1)+1) + 1; //this looks crazy, we just dont want to change 0
    randomHeight = rand()%((gridHeight-1)+1) +1;
    //checking if array doesn't have a cell
    if(!(myGrid[randomWidth][randomHeight].ContainsCell())){
      myGrid[randomWidth][randomHeight] = new Cell(true);
      totalCells++;
    }
  }
}

//fill grid with a given map
void CellGrid :: FillMapGrid(string map[]){
  int mapCurrHeight = 0;
  int mapCurrWidth = 0;
  for(int i=1; i<=gridHeight; ++i){
    mapCurrWidth = 0;
    for(int j=1; j<=gridWidth; ++j){
      if(map[mapCurrHeight].at(mapCurrWidth) == 'X'){
        myGrid[i][j].ChangeCell(true);
      } else {
        myGrid[i][j].ChangeCell(false);
      }
      mapCurrWidth++;
    }
    mapCurrHeight++;
  }
}


//prints out grid neatly
void CellGrid :: GridPrint(){
  for(int i=1; i <=gridWidth; ++i){
    for(int j=1; j <=gridHeight; ++j){
      cout<<"|"<< myGrid[i][j].ShowCell();
    }
    cout << endl;
  }
}
//creates a string that can be put into a file
string CellGrid :: FilePrint(){
  string totalGrid;
  for(int i=1; i <= gridWidth; ++i){
    for(int j=1; j <= gridHeight; ++j){
      totalGrid = totalGrid + "|" + myGrid[i][j].ShowCell();
    }
    totalGrid = totalGrid + "|\n";
  }
  return totalGrid;

}


//count neighbors and return int of the given cell position
int CellGrid :: CountNeighbors(int widthPos, int heightPos){
  int finalCount = 0;
//  Cell *tempCell = &givenGrid[widthPos][heightPos];
  for(int i=widthPos-1; i <= widthPos+1; ++i){
    for(int j=heightPos-1; j <= heightPos+1; ++j){
      if(i==widthPos && j==heightPos){
      //nothing, we don't want to count itself as a neighbor
      } else if (myGrid[i][j].ContainsCell()){
        ++finalCount;
        //nothing, we don't want to count itself as a neighbor
      }//end of if
    }//end of j loop
  }//end of i loop
  myGrid[widthPos][heightPos].SetNeighborCount(finalCount);
  return finalCount;
}

//all get methods to retrieve private variables
int CellGrid :: GetExtraWidth(){
  return extraWidth;
}
int CellGrid :: GetGridWidth(){
  return gridWidth;
}
int CellGrid :: GetExtraHeight(){
  return extraHeight;
}
int CellGrid :: GetGridHeight(){
  return gridHeight;
}


//checks if a grid contains any cells or not
bool CellGrid :: isEmpty(){
  for(int i=0; i < extraWidth; ++i){
    for(int j=0; j < extraHeight; ++j){
      if(myGrid[i][j].ContainsCell()){
        return false;
      }
    }
  }
  return true;
}

//compares two grids, given one grid and the current grid
bool CellGrid :: CompareSame(CellGrid* temp){
  for(int i=0; i<extraWidth; ++i){
    for(int j=0; j<extraHeight; ++j){
      if(myGrid[i][j].ContainsCell() != temp->myGrid[i][j].ContainsCell()){
        return false;
      }
    }
  }
  return true;
}
