//
//  Deck.hpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>
#include <chrono> // for time delay
using namespace std;


enum class Suit: int {diamond, club, heart, spade};
enum class Face: int {one, two, three, four, five, six, seven, eight,
    nine, ten, jack, queen, king, ace};

struct Card{
    int num;
    Suit suit;
    Face face;
};

const vector<Suit> v_suit {Suit::diamond, Suit::club, Suit::heart, Suit::spade};

const vector<Face> v_rank {Face::two, Face::three, Face::four, Face::five,
    Face::six, Face::seven, Face::eight, Face::nine, Face::ten, Face::jack,
    Face::queen, Face::king, Face::ace};


class Deck{
public:
    Deck();
    void shuffleDeck();
    Card* dealCard(int i) {return &cardArr[i];}
private:
    Card cardArr[52];

};

string cardToString(Card*);


#endif /* Deck_hpp */
