#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

enum State
{   
    kPath,
    kClosed,
    kEmpty,
    kObstacle,
    kStart,
    kFinish
};

const int Directions[4][2]{ {-1,0},{0,-1},{1,0},{0,1}};



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

bool Compare(std::vector<int> Node1, std::vector<int> Node2){
    if(Node1[2] + Node1[3] < Node2[2] + Node2[3]){
        return true;
    }else{
        return false;
    }
} 

void CellSort(std::vector<std::vector <int> > &Open){
    sort(Open.begin(), Open.end(), Compare);
}
bool CheckValidCell(int x, int y, std::vector<std::vector<State> > &Board){
    int colLength = Board.size();
    int rowLength = Board[0].size();

    if(y < 0 || y > rowLength - 1){
        return false;
    }
    if(x < 0 || x > colLength - 1){
        return false;
    }

    if(Board[x][y] == kEmpty){
        return true;
    }

    return false;
}

void ExpandNeighbors(std::vector<int> &CurrentNode, 
                        std::vector<std::vector<int> > &Open,
                        std::vector<std::vector <State> > &Board,
                        int goal[2]){
    int x = CurrentNode[0];
    int y = CurrentNode[1];
    int g = CurrentNode[2];
    int h = CurrentNode[3];

    for(auto neighbour: Directions){
        if(CheckValidCell(x + neighbour[0], y + neighbour[1], Board) == true){
            AddToOpen(x + neighbour[0],
                      x + neighbour[0],
                      g + 1,
                      Heuristic(x + neighbour[0],y + neighbour[1], goal[0], goal[1]),
                      Open, 
                      Board);

        }
    }
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> Board
                                , int array1[2]
                                , int array2[2])
{   
    int x = array1[0];
    int y = array1[1];
    int g = 0;
    int h = Heuristic(array1[0], array1[1], array2[0], array2[1]);
    std::vector<std::vector<int> > Open {};
    AddToOpen(x,y,g,h,Open,Board);

    while(Open.size() > 0){
        CellSort(Open);
        std::vector<int> Current = Open[Open.size()-1];
        Open.pop_back();

        Board[Current[0]][Current[1]] = kPath;

        if(Current[0] == array2[0] && Current[1] == array2[1]){
            Board[array1[0]][array1[1]] = kStart;
            Board[array2[0]][array2[1]] = kFinish;
            return Board;
        }
        ExpandNeighbors(Current, Open, Board , array2);
    }
    return Board;
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