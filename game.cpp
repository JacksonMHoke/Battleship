#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
    10x10 grid
    grid legend:
        -1 = shot
        0 = vacant
        1 = 2 ship
        2 = first 3 ship
        3 = second 3 ship
        4 = 5 ship
        5 = 6 ship

    hps legend:
        hp[0] = N/A
        hp[1] = 2 ship hp
        hp[2] = first 3 ship hp
        hp[3] = second 3 ship hp
        hp[4] = 5 ship hp
        hp[5] = 6 ship hp

*/

namespace game {

    static const int numShips=5;
    static const int dimension=10;

    void populate(vector<vector<int>>& grid, vector<int>& hps) {
        //initializing hp values
        hps.resize(numShips+1);
        hps[1]=2; hps[2]=3; hps[3]=3; hps[4]=5; hps[5]=6;

        //place all ships
        int x,y,r;
        bool invalid;
        string s;
        for (int i=1; i<numShips+1; ++i) {
            //takes in input, repeats when invalid input
            while(true) {
                invalid=false;
                cout << "Pick the orientation of the length " << hps[i] << " ship(0 for down, 1 for right): ";
                cin >> r;
                cout << "Pick your x and y coordinates(ex: 1 2): ";
                cin >> x >> y;
                //if valid input check if there will be any overlap of ships
                if ((r==0 && y+hps[i]-1<dimension && y>=0 && x>=0 && x<dimension) || (r==1 && x+hps[i]-1<dimension && x>=0 && y>=0 && y<dimension)) {
                    for (int j=0; j<hps[i]; ++j) {
                        if (r==0 && grid[y+j][x]!=0) invalid=true;
                        else if (r==1 && grid[y][x+j]!=0) invalid=true;
                    }
                    //if it gets past for loop checking for collisions placement is valid
                    if (!invalid) break;
                }
            }

            //place ship on grid
            for (int j=0; j<hps[i]; ++j) {
                if (r==0) grid[y+j][x]=i;
                else grid[y][x+j]=i;
            }
        }
    }

    void turn (vector<vector<int>>& opposingGrid, vector<int>& hps) {
        int x, y;
        cout << "Enter the coordinates to attack: ";
        cin >> x >> y;

        while(opposingGrid[x][y] <= 0 || x < 0 || x >= 10 || y < 0 || y > 10){
            
            if(x < 0 || x >= 10 || y < 0 || y > 10){
                cout << "The coordinates are out of range.\n";
            }
            else if(opposingGrid[x][y] <= 0){
                cout << "Coordinates already have been attacked.\n";
            }

            cout << "Please enter new coordinates to attack:\n";
            cin >> x >> y;
        }
        int ship = opposingGrid[x][y];
        
        if(ship >= 1){
            hps[ship - 1]--;
            opposingGrid[x][y] *= -1;
            
            if(hps[ship - 1] == 0){
                int brokenship = opposingGrid[x][y];
                int destroyedvalue = INT32_MIN + 1;
                opposingGrid[x][y] = destroyedvalue;

                //checks if the ship is horizontal
                if(x > 0 && opposingGrid[x-1][y] == brokenship || x != 9 && opposingGrid[x+1][y] == brokenship){
                    int i = x;
                    while(i > 0 && opposingGrid[i][y] == brokenship){
                        opposingGrid[i][y] = destroyedvalue;
                        i--;
                    }
                    
                    i = x;

                    while(i < 0 && opposingGrid[i][y] == brokenship){
                        opposingGrid[i][y] = destroyedvalue;
                        i++;
                    }
                }
                else{
                    //the ship is vertical
                    int i = y;
                    while(i > 10 && opposingGrid[x][i] == brokenship){
                        opposingGrid[x][i] = destroyedvalue;
                        i--;
                    }
                    
                    i = y;

                    while(i < 10 && opposingGrid[x][i] == brokenship){
                        opposingGrid[x][i] = destroyedvalue;
                        i++;
                    }
                }
                
            }
        }
        else if(ship == 0){
            opposingGrid[x][y] = INT32_MIN;
        }

    }

    bool hasWon(vector<int>& hps) {
        for (auto h : hps) {
            if (h!=0) return false;
        }
        return true;
    }

    void display(vector<vector<int>>& grid) {
        for (auto r : grid) {
            for (auto i : r) {
                switch (i) {
                    case INT32_MIN+1: cout << "D "; break;
                    case INT32_MIN: cout << "X "; break;
                    case -1: cout << "O "; break;
                    case -2: cout << "O "; break;
                    case -3: cout << "O "; break;
                    case -4: cout << "O "; break;
                    case -5: cout << "O "; break;
                    case -6: cout << "O "; break;
                    default: cout << "- ";
                }
            }
            cout << endl;
        }
    }
    
    void run() {
        //populating player 1
        vector<vector<int>> player1Grid(dimension, vector<int>(dimension, 0));
        vector<int> player1Hp;
        cout << "Player 1 choose your ship's positions, Player 2 look away.\n";
        populate(player1Grid, player1Hp);
        display(player1Grid);

        //populating player 2
        vector<vector<int>> player2Grid(dimension, vector<int>(dimension, 0));
        vector<int> player2Hp;
        cout << "Player 2 choose your ship's positions, Player 1 look away.\n";
        populate(player2Grid, player2Hp);

        //run turns until game is decided
        string temp;
        while (true) {
            display(player2Grid);
            cout << "Player 1's turn:\n";
            turn(player2Grid, player2Hp);
            if (hasWon(player2Hp)) {
                cout << "Player 1 wins!";
                break;
            }
            display(player2Grid);
            cout << "ENTER OK TO GO TO NEXT TURN: ";
            cin >> temp;

            display(player1Grid);
            cout << "Player 2's turn:\n";
            turn(player1Grid, player1Hp);
            if (hasWon(player1Hp)) {
                cout << "Player 2 wins!";
                break;
            }
            display(player1Grid);
            cout << "ENTER OK TO GO TO NEXT TURN: ";
            cin >> temp;
        }
    }
}