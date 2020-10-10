/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

Purpose: Simluation.h is the header file that declares all the methods
implemented in the corresponding .cpp file. It also defines the necessary
classes that are used in the Simulation class as well.
*/

#ifndef GAMEMODE_H
#define GAMEMODE_H
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include "FileProcessor.h"
#include "GameMode.h"

class GameMode;
class FileProcessor;
class Simulation{
  public:
    Simulation();
    ~Simulation();

    void StartGame();

  private:
    FileProcessor *myFiles;
    GameMode *gameMode;
    bool pauseBool;
    bool enterBool;
    bool fileBool;
    string printOutFileName;

    void RandomGame();
    void FileGame();
    void CreateRandomGameMode(int width, int height, double popDens, string mode);
    void CreateMapGameMode(int width, int height, string map[], string mode);

    void SetUpGame(string inputType);
    string SetMapFileName();
    void SetWrittenFileName();
    int SetRandomWidth();
    int SetMapWidth();
    int SetRandomHeight();
    int SetMapHeight();
    double SetPopDens();
    string SetGameMode();

    void PauseControlSim();
    void PauseGen();
    void EnterGen();
    void FileGen(int genNum);
    bool StablizeCheck();

    void RunSimulation();

    void PrintToFile();

#endif
#endif
};
