#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>


enum State
{   
    Path,
    Closed,
    Empty,
    Obstacle,
    Start,
    Finish
};

std::string CellString(State state);

std::vector<State> ParseLine(std::string line);

void printBoard(std::vector<std::vector<State>> my_vector);

std::vector<std::vector<State>> ReadBoardFile(std::string filePath);

int Heuristic(int one, int two, int three, int four);

void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> &OpenNodes,
               std::vector<std::vector<State>> &Grid);

bool Compare(std::vector<int> Node1, std::vector<int> Node2);

void CellSort(std::vector<std::vector <int> > &Open);

bool CheckValidCell(int x, int y, std::vector<std::vector<State> > &Board);

void ExpandNeighbors(std::vector<int> &CurrentNode, 
                        std::vector<std::vector<int> > &Open,
                        std::vector<std::vector <State> > &Board,
                        int goal[2]);

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> Board
                                , int array1[2]
                                , int array2[2]);

