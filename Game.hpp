//
//  Game.hpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Player.hpp"

using namespace std;

class Game{
public:
    Game(int maxScore);
    void deal();
    void takeTurn();
    void setDealer(){DealerPtr = &User;}
    void moveDealer();
    void setWhoseTurn(Player* _Player){TurnPtr = _Player;}
    void moveWhoseTurn();
    void getBid();
    void bid(Player* _Player);
    void playCard(Player* _Player);
    void displayCardsOnTable(){for(auto const& i : CardsOnTable)
        cout << cardToString(i);}
    void userTurn();
    void userBid();
    bool isGameOver(){return gameOver;}
    void tallyPoints();

private:
    bool trump, gameOver;
    int userTeamScore, computerTeamScore, userTeamBid, computerTeamBid, computerTeamTricks, userTeamTricks, computerTeamBags, userTeamBags, winningScore;
    Deck D;
    Player User, OPP1, TM, OPP2;
    Player* DealerPtr;
    Player* TurnPtr;
    Player* WinningPtr;
    //Pointers to keep track of who played which card
    Player* first;
    Player* second;
    Player* third;
    Player* fourth;
    vector<Card*> CardsOnTable;
    
};

#endif /* Game_hpp */
