#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>

int topRightDiff;
int middleDiff;
int bottomRightDiff;

void readFileAndInputToArray(int map[480][844]) {

    std::ifstream readFile("map_844x480.dat");

    for (int i = 0; i < 480; i++) {
        for (int j = 0; j < 844; j++) {
            readFile >> map[i][j];
        }
    }
}

int smallestDifference(int startingValue, int topRight, int middle, int bottomRight)
{

    topRightDiff = abs(startingValue - topRight);
    middleDiff = abs(startingValue - middle);
    bottomRightDiff = abs(startingValue - bottomRight);

    return std::min(topRightDiff, std::min(middleDiff, bottomRightDiff));

}

void scenarioOne()
{

    int map[480][844];

    readFileAndInputToArray(map);

    int row;
    std::cout << "Please enter a row to start from: ";
    std::cin >> row;

    std::cout << std::endl;

    int totalEnergy = 0;
    srand(time(NULL));

    for (int j = 0; j < 844; j++)
    {
        int currentElement = map[row][j];
        int topRight = map[row - 1][j + 1];
        int middle = map[row][j + 1];
        int bottomRight = map[row + 1][j + 1];

        int smallestDiff = smallestDifference(currentElement, topRight, middle, bottomRight);

        // if smallest difference is equal for both top right and bottom right
        if ((smallestDiff == topRightDiff) && (smallestDiff == bottomRightDiff)) {
            int coinFlip = rand() % 2;

            if (coinFlip == 0)
            {
                row = row - 1;
            }
            else
            {
                row = row + 1;
            }
        }

        //if smallestDiff is equal to middleDiff
        else if (smallestDiff == middleDiff) {
            row = row;
        }

        // if smallestDiff is equal to topRightDiff
        else if (smallestDiff == topRightDiff)
        {
            row = row - 1;
        }

        // if smallestDiff is equal to bottomRightDiff
        else if (smallestDiff == bottomRightDiff)
        {
            row = row + 1;
        }

        //if topRight and middle are equal, move to middle
        else if ((topRightDiff == middleDiff) && (topRightDiff < bottomRightDiff) || 
        (bottomRightDiff == middleDiff) && (bottomRightDiff < topRightDiff))
        {
            row = row;
        }

        else {
            std::cout << "Error" << std::endl;
        }

        // std::cout << "row: " << row << ", Column: " << j << ", Element: " << currentElement << std::endl;
        totalEnergy += smallestDiff;
        
        std::cout << currentElement << " -> ";

    }

    std::cout << "The end.";

    std::cout << std::endl;

    std::cout << "Total energy: " << totalEnergy << "\n\n";
}


int main()
{

    scenarioOne();

    return 0;
  
}