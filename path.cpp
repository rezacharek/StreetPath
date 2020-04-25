#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

enum State
{
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
        if(val == 1){
            result.push_back(kObstacle);
        }
        else{
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

int main()
{
    printBoard(ReadBoardFile("test_file.txt"));

    return 0;
}