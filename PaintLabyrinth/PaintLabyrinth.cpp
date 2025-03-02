/*1.1. Покраска лабиринта (5)
Лабиринт представляет собой квадрат, состоящий из NxN сегментов. 
Каждый из сегментов может быть либо пустым, либо заполненным монолитной каменной стеной. 
Гарантируется, что левый верхний и правый нижний сегменты пусты. 
Лабиринт обнесён сверху, снизу, слева и справа стенами, оставляющими свободными только левый верхний и правый нижний углы. 
Директор лабиринта решил покрасить стены лабиринта, видимые изнутри (см. рисунок). 
Помогите ему рассчитать количество краски, необходимой для этого.

Студент: Шашкин М.Р ПС-24
Среда выполнения: Visual Studio*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>

const int WALL_HEIGHT = 3;
const int WALL_WIDTH = 3;
const int WALL_AREA = WALL_WIDTH * WALL_HEIGHT;

struct Cell 
{
    int countPainted;
    bool isEmpty;
    bool isWatched;
    bool isWatching;
    Cell(bool isEmpty = true, bool isWatched = false, bool isWatching = false, int countPainted = 0) : isEmpty(isEmpty), isWatched(isWatched), isWatching(isWatching), countPainted(countPainted){};
};
int FirstLineToInt(std::ifstream &iFile)
{
    std::string firstLine;
    std::getline(iFile, firstLine);
    std::cout << "Field Size: " << firstLine << "\n\n";
    return (firstLine.empty() ? 5 : std::stoi(firstLine));
}
std::vector<std::vector<Cell>> MakeField(std::ifstream &iFile)
{
    std::vector<std::vector<Cell>> field = {{}};
    int countLine = 0;
    std::string line = "";

    while (std::getline(iFile, line))
    {
        std::cout << line << "\n";
        for (char c : line) 
        {
            Cell cell(c == '#' ? false : true, false);
            field[countLine].push_back(cell);
        }
        field.push_back({});
        countLine++;
    }
    std::cout << "\n";
    return field;
}
std::vector<std::vector<Cell>> processField(std::stack<std::pair<int, int>>&notWatchedEmptyCellsIndexes, int &area, const int sizeField, std::vector<std::vector<Cell>> field)
{
        while (!notWatchedEmptyCellsIndexes.empty())
        {

            std::pair<int, int> tempCell = notWatchedEmptyCellsIndexes.top();

            if ((tempCell.first != 0 || tempCell.second != 0) && !field[tempCell.first][tempCell.second].isWatching) 
            {

                if (tempCell.first - 1 < 0 || (tempCell.first - 1 > 0 && !field[tempCell.first - 1][tempCell.second].isEmpty))
                {
                    field[tempCell.first][tempCell.second].countPainted += 1;
                    area += WALL_AREA;
                }
                if (tempCell.second - 1 < 0 || (tempCell.second - 1 > 0 && !field[tempCell.first][tempCell.second - 1].isEmpty))
                {
                    field[tempCell.first][tempCell.second].countPainted += 1;
                    area += WALL_AREA;
                }
                if (tempCell.first != sizeField - 1 || tempCell.second != sizeField - 1) 
                {
                    if (tempCell.first + 1 == sizeField || (tempCell.first + 1 < sizeField && !field[tempCell.first + 1][tempCell.second].isEmpty))
                    {
                        field[tempCell.first][tempCell.second].countPainted += 1;
                        area += WALL_AREA;
                    }
                    if (tempCell.second + 1 == sizeField || (tempCell.second + 1 < sizeField && !field[tempCell.first][tempCell.second + 1].isEmpty))
                    {
                        field[tempCell.first][tempCell.second].countPainted += 1;
                        area += WALL_AREA;
                    }
                }
            }
            if (tempCell.first + 1 < sizeField && field[tempCell.first + 1][tempCell.second].isEmpty 
                && !field[tempCell.first + 1][tempCell.second].isWatched 
                && !field[tempCell.first + 1][tempCell.second].isWatching)
            {
                field[tempCell.first][tempCell.second].isWatching = true;
                notWatchedEmptyCellsIndexes.push({ tempCell.first + 1, tempCell.second });
            } 
            else if (tempCell.second + 1 < sizeField && field[tempCell.first][tempCell.second + 1].isEmpty
                && !field[tempCell.first][tempCell.second + 1].isWatched 
                && !field[tempCell.first][tempCell.second + 1].isWatching)
            {
                field[tempCell.first][tempCell.second].isWatching = true;
                notWatchedEmptyCellsIndexes.push({ tempCell.first, tempCell.second + 1 });
            } 
            else if (tempCell.second - 1 > 0 && field[tempCell.first][tempCell.second - 1].isEmpty 
                && !field[tempCell.first][tempCell.second - 1].isWatched 
                && !field[tempCell.first][tempCell.second - 1].isWatching) 
            {
                field[tempCell.first][tempCell.second].isWatching = true;
                notWatchedEmptyCellsIndexes.push({ tempCell.first, tempCell.second - 1 });
            } 
            else if (tempCell.first - 1 >= 0 && field[tempCell.first - 1][tempCell.second].isEmpty 
                && !field[tempCell.first - 1][tempCell.second].isWatched 
                && !field[tempCell.first - 1][tempCell.second].isWatching && (tempCell.first != sizeField - 1 || tempCell.second != sizeField - 1)) 
            {
                field[tempCell.first][tempCell.second].isWatching = true;
                notWatchedEmptyCellsIndexes.push({ tempCell.first - 1, tempCell.second });
            }
            else 
            {
                field[tempCell.first][tempCell.second].isWatched = true;
                field[tempCell.first][tempCell.second].isWatching = false;
                notWatchedEmptyCellsIndexes.pop();
            }
        }
        return field;
}
int main()
{
    
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream iFile("input.txt");

    const int sizeField = FirstLineToInt(iFile);

    std::vector<std::vector<Cell>> field = MakeField(iFile);

    std::stack<std::pair<int, int>> notWatchedEmptyCellsIndexes;
    notWatchedEmptyCellsIndexes.push({ 0, 0 });

    int area = 0;

    field = processField(notWatchedEmptyCellsIndexes, area, sizeField, field);
    if (!field[sizeField - 1][sizeField - 1].isWatched) 
    {
        notWatchedEmptyCellsIndexes.push({ sizeField - 1, sizeField - 1 });
        field = processField(notWatchedEmptyCellsIndexes, area, sizeField, field);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    for (int i = 0; i != sizeField; ++i)
    {
        for (int j = 0; j != sizeField; ++j) 
        {
            if (field[i][j].isEmpty) 
            {
                std::cout << field[i][j].countPainted;
            }
            else 
            {
                std::cout << "#";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\nResult: " << area << "\n";
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    std::ofstream oFile("output.txt");
    oFile << area << "\n";
    oFile << "Execution time: " << elapsed.count() << " seconds\n";
}
