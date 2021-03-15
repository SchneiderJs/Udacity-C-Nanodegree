#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

/*
References:
http://www.cplusplus.com/reference/sstream/istringstream/
*/

enum class State
{
    kEmpty,
    kObstacle
};

std::vector<State> ParseLine(std::string s)
{
    std::vector<State> v;
    int i;
    char c;

    std::istringstream my_string(s);
    while (my_string >> i >> c)
    {
        if (i == 0)
            v.push_back(State::kEmpty);
        else
            v.push_back(State::kObstacle);
    }

    return v;
}

std::vector<std::vector<State>> ReadBoardFile(std::string path)
{
    std::vector<std::vector<State>> board;

    std::ifstream my_file;
    my_file.open(path);

    if (my_file)
    {
        std::string line;
        while (getline(my_file, line))
        {
            board.push_back(ParseLine(line));
        }
    }

    return board;
}

std::string CellString(State cell)
{
    switch (cell)
    {
    case State::kObstacle:
        return "⛰️   ";
    default:
        return "0   ";
    }
}

void PrintBoard(std::vector<std::vector<State>> board)
{
    for (std::vector<State> line : board)
    {
        for (State element : line)
        {
            std::cout << CellString(element);
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::vector<State>> board = ReadBoardFile("1.board");
    PrintBoard(board);
}
