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

    static const int numShips=6;
    static const int dimension=10;

    void populate(vector<vector<int>>& grid, vector<int>& hps) {
        //initializing hp values
        hps.resize(numShips);
        hps[1]=2; hps[2]=3; hps[3]=3; hps[4]=5; hps[5]=6;

        //place all ships
        int x,y,r;
        bool invalid;
        for (int i=1; i<numShips; ++i) {
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

    // void turn (vector<vector<int>>& opposingGrid, vector<int>& hps) {

    // }

    // bool hasWon(int player, vector<int>& hps) {

    // }
    
    void run() {
        
    }
}