#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <time.h>
#include <vector>

int topRightDiff;
int middleDiff;
int bottomRightDiff;

const int ROWS_COUNT = 480;
const int COLS_COUNT = 844;

void readFileAndInputToArray(int map[ROWS_COUNT][COLS_COUNT]) {

    std::ifstream readFile("map_844x480.dat");

    // reading the file and inputting the values into the array
    for (int i = 0; i < 480; i++) {
        for (int j = 0; j < 844; j++) {
            readFile >> map[i][j];
        }
    }

    readFile.close();

}

int smallestDifference(int startingValue, int topRight, int middle, int bottomRight){

    // calculating the difference between the current element and the three elements to the right
    topRightDiff = abs(startingValue - topRight);
    middleDiff = abs(startingValue - middle);
    bottomRightDiff = abs(startingValue - bottomRight);


    // returning the smallest difference
    return std::min(topRightDiff, std::min(middleDiff, bottomRightDiff));
}

void scenarioOneB() {

    int row = 0;
    int col = 0;
    srand(time(NULL));

    int map[ROWS_COUNT][COLS_COUNT];
    readFileAndInputToArray(map);
    std::vector <int> optimalPath;

    for (int i = 0; i < ROWS_COUNT; i++) {
        row = i;

        for (int j = 0; j < COLS_COUNT; j++) {
            col = j;

            int currentElement, topRight, middle, bottomRight;

            /* initializing to bottomRight and topRight to a large number for row 0 and 479 
            so that it is avoided to be chosen in order to avoid segmentation fault*/
            if(row == 479) {
                //check only top right and middle
                currentElement = map[row][col];
                topRight = map[row - 1][col + 1];
                middle = map[row][col + 1];
                bottomRight = 1000000;
            } else if (row == 0) {
                //check only bottom right and middle
                currentElement = map[row][col];
                bottomRight = map[row + 1][col + 1];
                middle = map[row][col + 1];
                topRight = 1000000;
            } else {
                //check all three
                currentElement = map[row][col];
                topRight = map[row - 1][col + 1];
                middle = map[row][col + 1];
                bottomRight = map[row + 1][col + 1];
            }

            // int bottomRight = map[row + 1][col + 1];
            int smallestDiff = smallestDifference(currentElement, topRight, middle, bottomRight);

            // if smallestDiff is equal to both topRightDiff and bottomRightDiff
            if ((smallestDiff == topRightDiff) && (smallestDiff == bottomRightDiff)) {
                int coinFlip = rand() % 2;

                if (coinFlip == 0) {
                    row = row - 1;
                }
                else {
                    row = row + 1;
                }

            // if smallestDiff is equal to both topRightDiff and middleDiff, or both middleDiff and bottomRightDiff
            } else if ((topRightDiff == middleDiff) && (topRightDiff < bottomRightDiff) ||
                     (bottomRightDiff == middleDiff) && (bottomRightDiff < topRightDiff)) {
                row = row;

            // if smallestDiff is equal to topRightDiff, or bottomRightDiff, or middleDiff 
            } else {
                if (smallestDiff == topRightDiff) {
                    row = row - 1;
                }
                else if (smallestDiff == middleDiff) {
                    row = row;
                }
                else if (smallestDiff == bottomRightDiff) {
                    row = row + 1;
                }
            }

            // adding the current element to the vector
            optimalPath.push_back(currentElement);
        }
    }

    int maxSize = COLS_COUNT;
    int differences[COLS_COUNT] = {0};  

    int leastEnergy = INT_MAX;
    int leaestEnergyRow = 0;

    // splitting the vector into rows and calculating the energy of each row
    for (int i = 0; i < optimalPath.size(); i++) {
        
        // if we reach the end of a row
        if ((i + 1) % maxSize == 0) {
            int totalEnergy = 0;

            // calculating the energy of each row
            for(int j = 0; j < COLS_COUNT - 1; j++) {
                differences[j] = abs(optimalPath[i - j] - optimalPath[i - j - 1]);
                totalEnergy += differences[j];
            }

            // finding the least energy
            if (totalEnergy < leastEnergy) {
                leastEnergy = totalEnergy;
                leaestEnergyRow = i / maxSize;
            }

            std::cout << "Row " << i / maxSize << " has energy " << totalEnergy << std::endl;
            
        }
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "The least energy is " << leastEnergy << " and it is in row " << leaestEnergyRow << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "The least energy path is: " << std::endl;

    // Printing the least energy path
    for(int i = 0; i < COLS_COUNT; i++) {
        std::string pathColored = "\033[1;31m";
        std::cout << pathColored << optimalPath[leaestEnergyRow * COLS_COUNT + i] << " -> ";
    }

    std::cout << "The end.";

}

int main()
{
    scenarioOneB();
    return 0;
}