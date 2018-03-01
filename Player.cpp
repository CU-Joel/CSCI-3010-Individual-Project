//
//  Player.cpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//

#include "Player.hpp"

void Player::putInHand(Card *c) {
    if(c->suit == Suit::diamond){
        DiamondVec.push_back(c);
    } else if (c->suit == Suit::club){
        ClubVec.push_back(c);
    }else if (c->suit == Suit::heart){
        HeartVec.push_back(c);
    }else if (c->suit == Suit::spade){
        SpadeVec.push_back(c);
    }
    
}

Card* Player::playDiamond(int selection){
    Card* c = DiamondVec[selection];
    DiamondVec.erase(DiamondVec.begin()+selection);
    return c;
}
Card* Player::playClub(int selection){
    Card* c = ClubVec[selection];
    ClubVec.erase(ClubVec.begin()+selection);
    return c;
}
Card* Player::playHeart(int selection){
    Card* c = HeartVec[selection];
    HeartVec.erase(HeartVec.begin()+selection);
    return c;
}
Card* Player::playSpade(int selection){
    Card* c = SpadeVec[selection];
    SpadeVec.erase(SpadeVec.begin()+selection);
    return c;
}
 
void Player::sortHand(){
    sort(DiamondVec.begin(), DiamondVec.end(), sortByNum);
    sort(ClubVec.begin(), ClubVec.end(), sortByNum);
    sort(HeartVec.begin(), HeartVec.end(), sortByNum);
    sort(SpadeVec.begin(), SpadeVec.end(), sortByNum);

}

void Player::displayHand(){
    for(auto const& i : DiamondVec)
        cout << cardToString(i);
    for(auto const& i : ClubVec)
        cout << cardToString(i);
    for(auto const& i : HeartVec)
        cout << cardToString(i);
    for(auto const& i : SpadeVec)
        cout << cardToString(i);
}

bool sortByNum(Card *lhs, Card *rhs){
    return lhs->num < rhs->num;
}

