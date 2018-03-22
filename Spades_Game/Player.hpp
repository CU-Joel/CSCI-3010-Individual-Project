//
//  Player.hpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Deck.hpp"

class Player{
public:
    
    Card* playDiamond(int selection);
    Card* playClub(int selection);
    Card* playHeart(int selection);
    Card* playSpade(int selection);

    void putInHand(Card *c);
    void sortHand();
    vector<string> displayHand();
    vector<Card*> getDiamonds(){return DiamondVec;}
    vector<Card*> getClubs(){return ClubVec;}
    vector<Card*> getHearts(){return HeartVec;}
    vector<Card*> getSpades(){return SpadeVec;}

private:
    vector<Card*> DiamondVec;
    vector<Card*> ClubVec;
    vector<Card*> HeartVec;
    vector<Card*> SpadeVec;

};

bool sortByNum(Card *lhs, Card *rhs);

#endif /* Player_hpp */
