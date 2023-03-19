#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <time.h>
#include <vector>
#include <algorithm>

// All the function prototypes
void readFileAndInputToArray(int map[480][844]);
int smallestDifference(int startingValue, int topRight, int middle, int bottomRight);
int difference(int current, int next);
void scenarioOneA();
void scenarioOneB();
void scenarioTwo();

// declaring the constants
const int rowCount = 480;
const int colCount = 844;

// declaring some global variables
int topRightDiff;
int middleDiff;
int bottomRightDiff;

// reading the file and inputting the values into the array
void readFileAndInputToArray(int map[480][844])
{

    std::ifstream readFile("map_844x480.dat");

    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 844; j++)
        {
            readFile >> map[i][j];
        }
    }
}

// calculating the difference between the current element and three adjacent elements
// for scenario 1-A and 1-B
int smallestDifference(int startingValue, int topRight, int middle, int bottomRight)
{

    topRightDiff = abs(startingValue - topRight);
    middleDiff = abs(startingValue - middle);
    bottomRightDiff = abs(startingValue - bottomRight);

    return std::min(topRightDiff, std::min(middleDiff, bottomRightDiff));
}

// calculating the difference between the current element and the next element (Scenario 2)
int difference(int current, int next)
{
    return abs(current - next);
}

void scenarioOneA()
{

    int map[480][844];

    readFileAndInputToArray(map);

    int row;
    std::cout << std::endl;
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
        if ((smallestDiff == topRightDiff) && (smallestDiff == bottomRightDiff))
        {
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

        // if smallestDiff is equal to middleDiff
        else if (smallestDiff == middleDiff)
        {
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

        // if topRight and middle are equal, move to middle
        else if ((topRightDiff == middleDiff) && (topRightDiff < bottomRightDiff) ||
                 (bottomRightDiff == middleDiff) && (bottomRightDiff < topRightDiff))
        {
            row = row;
        }

        else
        {
            std::cout << "Error" << std::endl;
        }

        // std::cout << "row: " << row << ", Column: " << j << ", Element: " << currentElement << std::endl;
        totalEnergy += smallestDiff;

        std::cout << currentElement << " -> ";
    }

    std::cout << "The end.";

    std::cout << "\n\n";

    std::cout << "Total energy: " << totalEnergy << std::endl;
}

void scenarioOneB()
{

    int row = 0;
    int col = 0;
    srand(time(NULL));

    int map[rowCount][colCount];
    readFileAndInputToArray(map);
    std::vector<int> optimalPath;

    for (int i = 0; i < rowCount; i++)
    {
        row = i;

        for (int j = 0; j < colCount; j++)
        {
            col = j;

            int currentElement, topRight, middle, bottomRight;

            /* initializing to bottomRight and topRight to a large number for row 0 and 479
            so that it is avoided to be chosen in order to avoid segmentation fault*/
            if (row == 479)
            {
                // check only top right and middle
                currentElement = map[row][col];
                topRight = map[row - 1][col + 1];
                middle = map[row][col + 1];
                bottomRight = 1000000;
            }
            else if (row == 0)
            {
                // check only bottom right and middle
                currentElement = map[row][col];
                bottomRight = map[row + 1][col + 1];
                middle = map[row][col + 1];
                topRight = 1000000;
            }
            else
            {
                // check all three
                currentElement = map[row][col];
                topRight = map[row - 1][col + 1];
                middle = map[row][col + 1];
                bottomRight = map[row + 1][col + 1];
            }

            // int bottomRight = map[row + 1][col + 1];
            int smallestDiff = smallestDifference(currentElement, topRight, middle, bottomRight);

            // if smallestDiff is equal to both topRightDiff and bottomRightDiff
            if ((smallestDiff == topRightDiff) && (smallestDiff == bottomRightDiff))
            {
                int coinFlip = rand() % 2;

                if (coinFlip == 0)
                {
                    row = row - 1;
                }
                else
                {
                    row = row + 1;
                }

                // if smallestDiff is equal to both topRightDiff and middleDiff, or both middleDiff and bottomRightDiff
            }
            else if ((topRightDiff == middleDiff) && (topRightDiff < bottomRightDiff) ||
                     (bottomRightDiff == middleDiff) && (bottomRightDiff < topRightDiff))
            {
                row = row;

                // if smallestDiff is equal to topRightDiff, or bottomRightDiff, or middleDiff
            }
            else
            {
                if (smallestDiff == topRightDiff)
                {
                    row = row - 1;
                }
                else if (smallestDiff == middleDiff)
                {
                    row = row;
                }
                else if (smallestDiff == bottomRightDiff)
                {
                    row = row + 1;
                }
            }

            // adding the current element to the vector
            optimalPath.push_back(currentElement);
        }
    }

    // splitting the vector into rows and calculating the energy of each row
    int maxSize = colCount;
    int differences[colCount] = {0};

    int leastEnergy = INT_MAX;
    int leaestEnergyRow = 0;

    // splitting the vector into rows and calculating the energy of each row
    for (int i = 0; i < optimalPath.size(); i++)
    {

        // if we reach the end of a row
        if ((i + 1) % maxSize == 0)
        {
            int totalEnergy = 0;

            // calculating the energy of each row
            for (int j = 0; j < colCount - 1; j++)
            {
                differences[j] = abs(optimalPath[i - j] - optimalPath[i - j - 1]);
                totalEnergy += differences[j];
            }

            // finding the least energy
            if (totalEnergy < leastEnergy)
            {
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

    std::string reset = "\033[0m";

    // Printing the least energy path
    for (int i = 0; i < colCount; i++)
    {
        std::string pathColored = "\033[1;31m";
        std::cout << pathColored << optimalPath[leaestEnergyRow * colCount + i] << " -> ";
    }

    std::cout << reset << "The end."
              << "\n\n";
}

void scenarioTwo()
{

    int map[rowCount][colCount];

    readFileAndInputToArray(map);

    // make a vector that holds both row and energy
    std::vector<std::pair<int, int>> energies;

    // loop through each row
    for (int startingRow = 0; startingRow < rowCount; startingRow++)
    {

        // set the current element to the first element in the row
        int currentElement = map[startingRow][0];
        int currentRow = startingRow;
        int currentCol = 0;

        int totalEnergy = 0;

        int nextElement = 0;
        int nextRow = 0;
        int nextCol = 0;

        // loop through the column and find the least energy element and set the next element to that element
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

    // sort the vector
    std::sort(energies.begin(), energies.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b)
              { return a.second < b.second; });

    std::cout << std::endl;

    // print out the row with the least energy
    std::cout << "row: " << energies[0].first << " with the least energy: " << energies[0].second << std::endl;

    std::cout << "----------------------------------------" << std::endl;

    // print the path for the row with the least energy
    std::cout << "path of the least energy: "
              << "\n\n";

    int currentElement = map[energies[0].first][0];
    int currentRow = energies[0].first;
    int currentCol = 0;

    int nextElement = 0;
    int nextRow = 0;
    int nextCol = 0;

    int goodJ = 0;
    int goodI = 0;

    // same thing as above but just used to print out the optimal path
    for (int i = 0; i < rowCount; i++)
    {

        int minEnergy = INT_MAX;
        int leastEnergyElement = 0;

        for (int j = 0; j < colCount; j++)
        {
            nextElement = map[nextRow][nextCol + 1];

            int energy = difference(currentElement, nextElement);

            if (energy < minEnergy)
            {
                minEnergy = energy;
                leastEnergyElement = nextElement;
                goodI = nextRow;
                goodJ = nextCol + 1;
            }

            nextRow++;

            if (nextRow > rowCount - 1)
            {
                nextRow = 0;
                nextCol = goodJ;
                currentRow = goodI;
                currentCol = goodJ;
            }
        }
        // dont compare last column to first column
        if (nextCol == colCount + 1)
        {
            break;
        }

        std::cout << currentElement << " -> ";

        currentElement = leastEnergyElement;
    }

    std::cout << "END";

    std::cout << "\n\n";
}

int main()
{

    char ch;

    do
    {
        std::cout << "---------------------------------------------------------------------" << std::endl;

        std::cout << "Enter 'A' for scenario 1-A" << std::endl;
        std::cout << "Enter 'B' for scenario 1-B" << std::endl;
        std::cout << "Enter 'C' for scenario 2" << std::endl;
        std::cout << "Enter 'Q' to quit" << std::endl;

        std::cout << "---------------------------------------------------------------------" << std::endl;

        std::cin >> ch;

        switch (ch)
        {
        case 'a':
            scenarioOneA();
            break;
        case 'b':
            scenarioOneB();
            break;
        case 'c':
            scenarioTwo();
            break;
        case 'q':
            break;
        default:
            std::cout << std::endl;
            std::cout << "Please enter a valid input!" << "\n\n";
            break;
        }
    } while (ch != 'q');

    return 0;
}