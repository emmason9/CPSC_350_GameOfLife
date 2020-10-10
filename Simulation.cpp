/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: Simulation.cpp controls the entire simulation of the cell grid and each
generation, as well as all of the UI. It will ask the users the apporpriate
questions that will help it set up the right cell grid in the right gamemode as
well as run the simulation in whatever way they specify.
*/

#include "Simulation.h"
#include <algorithm> //for transform()
#include <thread>
#include <chrono>

Simulation :: Simulation(){
  myFiles = new FileProcessor();
  pauseBool = false;
  enterBool = false;
  fileBool = false;
}

Simulation :: ~Simulation(){
  delete myFiles;
  delete gameMode;
}

//starts up and asks the user how they want to set up the grid/world
void Simulation :: StartGame(){
  //introducing user to game, asking about what kinda way they want to start it
  string userInput;
  bool gameBool = true;
  cout << "\n\nLet's play the Game of Life!" << endl;
  while(gameBool){
    cout << "Would you like to create a 'random' grid or provide a 'file'?\n(you can 'quit' at any time)" << endl;
    cin >> userInput;
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    //checking userInput
    if(userInput == "random"){
      cout << "...setting up random game...\n" << endl;
      RandomGame();
      gameBool = false;
    } else if (userInput == "file"){
      cout<<"...setting up file game...\n" << endl;
      FileGame();
      gameBool = false;
    } else if (userInput == "quit"){
      gameBool = false;
    } else {
      cout<< "That's not an option!\nTry again" <<endl;
    }
  }
}

//sets up and runs random game
void Simulation :: RandomGame(){
  int userWidth;
  int userHeight;
  double userPopDens;
  string userMode;
  userWidth = SetRandomWidth();
  userHeight = SetRandomHeight();
  userPopDens = SetPopDens();
  userMode = SetGameMode();
  CreateRandomGameMode(userWidth, userHeight, userPopDens, userMode);
  PauseControlSim();
  RunSimulation();
}
//sets up and runs file game
void Simulation :: FileGame(){
  int userWidth;
  int userHeight;
  double userPopDens;
  string userMode;
  string userFileName = SetMapFileName();
  myFiles->OpenReaderFile(userFileName);
  userWidth = SetMapWidth();
  userHeight = SetMapHeight();
  //i couldn't refactor this one into it's own method ;-;
  string currentLine;
  int tempInt = 0;
  string newGrid[userHeight];
  while(getline(myFiles->Reader, currentLine)){
    newGrid[tempInt] = currentLine;
    tempInt++;
  }
  userMode = SetGameMode();
  CreateMapGameMode(userWidth, userHeight, newGrid, userMode);
  PauseControlSim();
  RunSimulation();
}

//asks user for width int
int Simulation :: SetRandomWidth(){
  string userWidth;
  int intWidth;
  bool checkWid = true;
  while(checkWid){
    cout <<"What would you like the width of the cell grid to be?"<<endl;
    cin >> userWidth;
    //trys to create int value from string,
    //will catch it if user inputs a not covertable string value
    try{
      intWidth = stoi(userWidth);
      checkWid = false;
    } catch (invalid_argument invalidWidth){
        cout<<"Invalid Input\nPlease give a number input! (ex: 1,2,3)" <<endl;
        continue;
    }
    return intWidth;
  }
}
//grabs width from a file
int Simulation :: SetMapWidth(){
  string givenWidth;
  int intWidth;
  getline(myFiles->Reader, givenWidth);
  intWidth = stoi(givenWidth);
  return intWidth;
}
//asks use for height int
int Simulation :: SetRandomHeight(){
  string userHeight;
  int intHeight;
  bool checkHeight = true;
  while(checkHeight){
    cout <<"What would you like the height of the cell grid to be?"<<endl;
    cin >> userHeight;
    try{
      intHeight = stoi(userHeight);
      cout<<"int height: "<<endl;
      checkHeight = false;
    } catch (invalid_argument invalidHeight){
      cout<<"Invlaid Input\nPlease give a number input! (ex: 1,2,3)\n" <<endl;
      continue;
    }
  }
  return intHeight;
}
//grabs height from a file
int Simulation :: SetMapHeight(){
  string givenHeight;
  int intHeight;
  getline(myFiles->Reader, givenHeight);
  intHeight = stoi(givenHeight);
  return intHeight;
}
//asks user for an initial population density
double Simulation :: SetPopDens(){
  string userPopDens;
  double doublePopDens;
  bool checkPopDens = true;
  while(checkPopDens){
    cout <<"What would you like the initial population density on the cell grid to be?" << endl;
    cout <<"Please give a number between 0 and 1 in decimal form (ex. 0.3 or 0.65)" << endl;
    cin >> userPopDens;
    try{
      doublePopDens = stod(userPopDens);
      //needs to be between 0 and 1 check
      if(doublePopDens >= 1.0 || doublePopDens < 0.0){
        cout << "This double is not between 0 and 1, but not including 0.\nPlease try again.\n" << endl;
        continue;
      }
      checkPopDens = false;
    } catch (invalid_argument invalidPopDens){
      cout<<"Invlaid Input\nPlease give a decimal input! (ex: 1.0,0.2,0.35)\n" <<endl;
      continue;
    }
    return doublePopDens;
  }
}
//askes user what gamemode would like to be played
string Simulation :: SetGameMode(){
  string userInput;
  while(userInput != "classic" && userInput != "mirror" && userInput != "doughnut"){
    cout << "What gamemode would you like to play?\nClassic, Mirror, or Doughnut"<<endl;
    cin >> userInput;
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    if (userInput != "classic" && userInput != "mirror" && userInput != "doughnut"){
      cout << "that's not a gamemode! try again!\n" << endl;
    } else {
      return userInput;
    }
  }
}

//creates a randomized grid
void Simulation :: CreateRandomGameMode(int width, int height, double popDens, string mode){
  cout<<"...creating grid..."<<endl;
  CellGrid *newGrid = new CellGrid(width,height,popDens);
  cout<<"...setting up game..."<<endl;
  GameMode *newGame = new GameMode(mode, newGrid);
  gameMode = newGame;
  cout<<endl;
}
//creates a mapped grid g
void Simulation :: CreateMapGameMode(int width, int height, string map[], string mode){
  cout<<"...creating grid..."<<endl;
  CellGrid *newGrid = new CellGrid(width,height,map);
  cout<<"...setting up game..." << endl;
  GameMode *newGame = new GameMode(mode, newGrid);
  newGame->gameGrid->GridPrint();
  gameMode = newGame;
  cout<<endl;
}

//asks user for a file name
string Simulation :: SetMapFileName(){
  string userFileName;
  bool fileCheck = true;
  FileProcessor *fileTest = new FileProcessor();
  while(fileCheck){
    cout<<"What file name is the map under? Remember to put in the extention!\n";
    cout<<"(you can always 'quit' as well)"<<endl;
    cin >> userFileName;
    if(userFileName == "quit"){
      cout<<"...quiting..."<<endl;
    } else if(fileTest->OpenReaderFile(userFileName)){
      delete fileTest;
      fileCheck = false;
      return userFileName;
    } else {
      cout<<"Reader didn't recognize the file name, try again!\n"<<endl;
    }
  }

}
//sets the bool that controls how the user will see each generation
void Simulation :: SetWrittenFileName(){
  string writerFileName;
  while(true){
    cout<<"What name would you like the file to be under?\n(just the name, I'll add the '.txt')"<<endl;
    cin>>writerFileName;
    if(myFiles->OpenWriterFile(writerFileName + ".txt")){
      printOutFileName = writerFileName + ".txt";
      myFiles->Writer.close();
      break;
    } else {
      cout<<"That file name didn't work, try again\n"<<endl;
    }
  }
}
//asks use how they want to control the flow of the generations
void Simulation :: PauseControlSim(){
  string userPauseInput;
  bool simulationCheck = true;
  while(simulationCheck){
    cout<<"How would you like to run your simulation?\nWould you like to 'pause' after each generation,\n";
    cout<<"...or press 'enter' to access the next generation,\n...or send all the generations to a 'file'?\n";
    cin >> userPauseInput;
    transform(userPauseInput.begin(), userPauseInput.end(), userPauseInput.begin(), ::tolower);
    //going through all the given options and checks if the user inputs the right response
    if(userPauseInput == "pause"){
      simulationCheck = false;
      pauseBool = true;
    } else if (userPauseInput=="enter"){
      simulationCheck = false;
      enterBool = true;
    } else if (userPauseInput == "file"){
      fileBool = true;
      simulationCheck = false;
      SetWrittenFileName();
    } else {
      cout<<"Sorry, that's not an option. Try again.\n"<<endl;
    }
  }
}
//performs a little pause before continuing to iterate through to the next generation
void Simulation :: PauseGen(){
  cout<<"...pausing..."<<endl;
  this_thread::sleep_for(chrono::seconds(3));
  cout<<"...unpaused..."<<endl;
}
//takes an input and checks if the user wants to continue the generations or quit
void Simulation :: EnterGen(){
  cout<<"Press enter to continue!" << endl;
  cin.ignore();
}
//puts all generations into a file
void Simulation :: FileGen(int genNum){
  myFiles->OpenAppenderFile(printOutFileName);
  myFiles->Appender << "Generation: "<<genNum<<endl;
  myFiles->Appender << gameMode->gameGrid->FilePrint()<<endl;
  myFiles->Appender.close();
}

//going through each generation for the cell grid
void Simulation :: RunSimulation(){
  bool runSimBool = true;
  bool stableBool = false;
  int genNum = 0;
  CellGrid *previousGrid;
  while(runSimBool){
    //file gen will not print out to the console, it's only in the file.
    if(fileBool){
      FileGen(genNum);
      if(genNum != 0){ //checks for all gens after 0/initial one
        bool isEmpty = gameMode->gameGrid->isEmpty();
        bool isSame = gameMode->gameGrid->CompareSame(previousGrid);
        if(isEmpty){
          stableBool = true;
        } else if (isSame){
            stableBool = true;
        }
      }
      if(stableBool){
        cout<<"The game grid has stablized!"<<endl;
        runSimBool = false;
        break;
      }
    //for the other pause controls, we will print out to the console
    } else {
  //printing out grid to console
      cout<<"Generation "<< genNum << endl;
      gameMode->gameGrid->GridPrint();
      cout<<endl;
  //stablize check (for all generations after 0)
      if(genNum != 0){
        bool isEmpty = gameMode->gameGrid->isEmpty();
        bool isSame = gameMode->gameGrid->CompareSame(previousGrid);
        if(isEmpty){
          stableBool = true;
        } else if (isSame){
        stableBool = true;
        }
      }
      if(stableBool){
        cout<<"The game grid has stablized."<<endl;
        runSimBool = false;
        break;
      }
  //running pause control check
      if(pauseBool){
        PauseGen();
      } else if(enterBool){
        if(genNum == 0){
          cin.ignore();//throw away any other inputs that may be lurking in console input
        }
        EnterGen();
      }
    }
  //updating to next gen
    previousGrid = gameMode->gameGrid->CopyGrid();
    gameMode->NextGeneration();
    genNum++;
  }//while loop end
  delete previousGrid;
  cout<<"Simluation is complete!"<<endl;
  cout<<"Press Enter to exit."<<endl;
  cin.ignore();
}
