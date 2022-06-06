#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    int ships = 0;
    int turn = 0;
    // Seed the random function so it isn't the same everytime.
    srand(time(0));
    bool gameBoard[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    // Randomly place ships on the board, continue the loop until we have enough ships.
    while(ships < 5)
    {
        for(int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if((rand() % 10) == 1)
                {
                    if(ships < 5 && !gameBoard[i][j])
                    {
                        gameBoard[i][j] = 1;
                        ships++;
                    }
                }
            }
        }
    }
    // Print game board with 0's for reference.
    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << 0;
        }
        cout << endl;
    }
    // Game Loop.
    while (ships > 0)
    {
        int row, column;
        cout << "Select coordinates" << endl;
        // Row
        cout << "Select a row (0-4): ";
        cin >> row;
        // Column
        cout << "Select a column (0-4): ";
        cin >> column;
        //Check if a hit was scored.
        if(gameBoard[row][column])
        {
            gameBoard[row][column] = 0;
            ships--;
            cout << "Hit." << (ships) << " ships left" << endl;
        }
        else
        {
            cout << "Miss. There are still " << (ships) << " ships left" << endl;
        }
        turn++;
    }
    cout << "You won in " << turn << " turns." << endl;
    return 0;
}
