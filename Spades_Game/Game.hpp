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
#include <QObject>
#include <QDebug>


using namespace std;

class Game : public QObject {
    Q_OBJECT
public:
    Game();
    Game(int maxScore);
    void deal();
    void takeTurn();
    //void setDealer(){DealerPtr = &User;}
    void moveDealer();
    void setWhoseTurn(Player* _Player){TurnPtr = _Player;}
    void moveWhoseTurn();
    int getWhoseTurn();
    void getBid();
    string getScore();
    void bid(Player* _Player);
    void playCard(int i);
    vector<string> getCardsOnTable();
    int userTurn(int selection);
    void setUserBid(int bid);
    bool isGameOver(){return gameOver;}
    void tallyPoints();

private:
    bool trump, gameOver;
    int userTeamScore, computerTeamScore, userTeamBid, computerTeamBid, computerTeamTricks, userTeamTricks, computerTeamBags, userTeamBags, winningScore;
    int Opp1Bid, Opp2Bid, TMBid;
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

signals:
    void sendHand(vector<string> &s);
    void printText(string s);
    void getUserBid();
    void putOpp1Card(string s);
    void putOpp2Card(string s);
    void putTMCard(string s);
    void putPlayerCard(string s);
};

#endif /* Game_hpp */
