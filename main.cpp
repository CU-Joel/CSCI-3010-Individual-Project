//
//  main.cpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//

#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
    char selection;
    bool done = false;
    int maxScore = 200;
    cout << "Welcome to Joels Spades. \n\nTo begin a new game enter the number for the game score you want to play to.\nEnter \n1. for 200 points \n2. for 500 points \n3. for 1000 points";
    while(!done){
        cin >> selection;
        switch(selection){
            case '1': {
                maxScore = 200;
                done = true;
                break;
            }
            case '2': {
                maxScore = 500;
                done = true;
                break;
            }
            case '3': {
                maxScore = 1000;
                done = true;
                break;
            }
            default: {
                cout << "Invalid Entry";
            }
        }
    }
    
    Game G(maxScore);
    G.setDealer();
    cout << "\nNew Game. \nWelcome to Joels Spades. You will deal first so Opponent 1 will start the bidding.\n";
    while(1){
        G.deal();
        G.getBid();
        for (int i=0; i<13; i++){
            G.takeTurn();
        }
        G.tallyPoints();
        if(G.isGameOver())
            break;
        G.moveDealer();
    }
    
    cout << endl;
    return 0;
}
