#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

enum State
{
    kClosed,
    kEmpty,
    kObstacle
};



std::string CellString(State state)
{
    if (state == kObstacle)
    {
        return "\u26F0 ";
    }
    else
    {
        return "0 ";
    }
}

std::vector<State> ParseLine(std::string line)
{
    std::istringstream iss(line);
    int val;
    std::vector<State> result;

    for (int i = 0; i < 6; i++)
    {
        iss >> val;
        if (val == 1)
        {
            result.push_back(kObstacle);
        }
        else
        {
            result.push_back(kEmpty);
        }
    }
    return result;
}

void printBoard(std::vector<std::vector<State>> my_vector)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            std::cout << CellString(my_vector[i][j]);
        }
        std::cout << std::endl;
    }
}
std::vector<std::vector<State>> ReadBoardFile(std::string filePath)
{
    std::ifstream MyFile(filePath);
    std::string Line;
    int val;
    std::vector<std::vector<State>> result;
    while (std::getline(MyFile, Line))
    {
        result.push_back(ParseLine(Line));
    }
    MyFile.close();
    return result;
}

int Heuristic(int one, int two, int three, int four)
{
    return abs(three - one) + abs(four - two);
}

void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> &OpenNodes,
               std::vector<std::vector<State>> &Grid)
{
    std::vector<int> temp{x, y, g, h};
    OpenNodes.push_back(temp);
    Grid[x][y] = kClosed;
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> Board, int array1[2], int array2[2])
{   
    int x = array1[0];
    int y = array1[1];
    int g = 0;
    int h = Heuristic(array1[0], array1[1], array2[0], array2[1]);
    std::vector<std::vector<int> > Open {};
    AddToOpen(x,y,g,h,Open,Board);

    return Board;
}

bool Compare(std::vector<int> Node1, std::vector<int> Node2){
    if(Node1[2] + Node1[3] < Node2[2] + Node2[3]){
        return true;
    }else{
        return false;
    }
} 

int main()
{
    std::vector<std::vector<State>> Board = ReadBoardFile("test_file.txt");
    printBoard(Board);
    int start[2] = {0, 0};
    int end[2] = {4, 5};
    std::vector<std::vector<State>> Solution = Search(Board, start, end);
    printBoard(Solution);
    return 0;
}