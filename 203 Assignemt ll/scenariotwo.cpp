#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>
#include <utility>

const int rowCount = 480;
const int colCount = 844;

void readFileAndInputToArray(int map[rowCount][colCount]) {

    std::ifstream readFile("map_844x480.dat");

    // reading the file and inputting the values into the array
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            readFile >> map[i][j];
        }
    }

}

int difference(int current, int next) {
    return abs(current - next);
}

void scenarioTwo() {

    int map[rowCount][colCount];

    readFileAndInputToArray(map);

    //make a vector that holds both row and energy
    std::vector<std::pair<int, int>> energies;

    //loop through each row
    for (int startingRow = 0; startingRow < rowCount; startingRow++)
    {

        int currentElement = map[startingRow][0];
        int currentRow = startingRow;
        int currentCol = 0;

        int totalEnergy = 0;

        int nextElement = 0;
        int nextRow = 0;
        int nextCol = 0;

        int goodJ = 0;
        int goodI = 0;

        /* loop through the column and find the least energy element and
        set the next element to that element */
        for (int j = 0; j < colCount; j++)
        {
            int minEnergy = INT_MAX;
            int leastEnergyElement = 0;
            // loop through row in column and find the least energy element
            for (int i = 0; i < rowCount; i++)
            {

                nextElement = map[nextRow][nextCol + 1];

                int energy = difference(currentElement, nextElement);

                /* if the energy is less than the min energy, set the min energy to the energy and
                set the least energy element to the next element */
                if (energy < minEnergy)
                {
                    minEnergy = energy;
                    leastEnergyElement = nextElement;
                    goodI = nextRow;
                    goodJ = nextCol + 1;
                }

                nextRow++;

                // if nextRow is greater than the row count, reset it to 0 and increment the column
                if (nextRow > rowCount - 1)
                {
                    nextRow = 0;
                    nextCol = goodJ;
                    currentRow = goodI;
                    currentCol = goodJ;
                }
            }
            // dont compare last column to first column
            if (nextCol == colCount)
            {
                break;
            }
            totalEnergy += minEnergy;

            currentElement = leastEnergyElement;
        }

        // push the row and total energy into the vector
        energies.push_back(std::make_pair(startingRow, totalEnergy));

        std::cout << std::endl;

        std::cout << "row: " << startingRow << std::endl;
        std::cout << "total energy: " << totalEnergy << std::endl;
    }

    //sort the vector
    std::sort(energies.begin(), energies.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });

    std::cout << std::endl;

    //print out the row with the least energy
    std::cout << "row: " << energies[0].first << " with the least energy: " << energies[0].second << std::endl;

    std::cout << "----------------------------------------" << std::endl;

    //print the path for the row with the least energy
    std::cout << "path of the least energy: " << "\n\n";

    int currentElement = map[energies[0].first][0];
    int currentRow = energies[0].first;
    int currentCol = 0;

    int nextElement = 0;
    int nextRow = 0;
    int nextCol = 0;

    int goodJ = 0;
    int goodI = 0;

    //same thing as above but just used to print out the optimal path
    for(int i = 0; i < rowCount; i++) {
        
        int minEnergy = INT_MAX;
        int leastEnergyElement = 0;

        for(int j = 0; j < colCount; j++) {
            nextElement = map[nextRow][nextCol + 1];

            int energy = difference(currentElement, nextElement);

            if(energy < minEnergy) {
                minEnergy = energy;
                leastEnergyElement = nextElement;
                goodI = nextRow;
                goodJ = nextCol + 1;
            }

            nextRow++;

            if(nextRow > rowCount - 1) {
                nextRow = 0;
                nextCol = goodJ;
                currentRow = goodI;
                currentCol = goodJ;
            }
        }
        //dont compare last column to first column
        if(nextCol == colCount + 1) {
            break;
        }

        std::cout << currentElement << " -> ";

        currentElement = leastEnergyElement;

    }

    std::cout << "END";

    

}

int main() {

    scenarioTwo();

    return 0;
}