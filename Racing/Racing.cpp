#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

const int INFINITY_INT = std::numeric_limits<int>::max();
int main() 
{
    std::cout << "Write name of file: ";
    std::string nameFile;
    std::cin >> nameFile;
    std::cout << "\n";
    std::ifstream inFile(nameFile);
    if (!inFile)
    {
        std::cout << "File not found\n";
        return 0;
    }
    int count;
    inFile >> count; 
    std::cout << count << "\n";
    std::vector<int> fuelStations = {};
    while (!inFile.eof() && fuelStations.size() != count)
    {
        int num = 0;
        inFile >> num;
        std::cout << num << " ";
        fuelStations.push_back(num);
    }
    std::cout << "\n";
    int minStartFuel = INFINITY_INT;
    for (int i = 0; i != fuelStations.size(); ++i)
    { 
        int startFuel = fuelStations[i];
        int tempFuel = startFuel;
        for (int j = i; j != fuelStations.size(); ++j)
        {
           if (startFuel > minStartFuel)
           {
               break;
           }
           tempFuel -= fuelStations[j];
           if (tempFuel < 0)
           {
               startFuel += abs(tempFuel);
           }
           tempFuel += fuelStations[j] + 1;
        }
        for (int j = 0; j != i; ++j)
        {
            if (startFuel > minStartFuel)
            {
                break;
            }
            tempFuel -= fuelStations[j];
            if (tempFuel < 0)
            {
                startFuel += abs(tempFuel);
            }
            tempFuel += fuelStations[j] + 1;
        }
        if (startFuel < minStartFuel)
        {
            minStartFuel = startFuel;
        }
    }
    std::ofstream outFile("output.txt");
    outFile << minStartFuel << "\n";
    std::cout << "Min Start Fuel = " << minStartFuel << "\n";
}