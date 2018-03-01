//
//  Deck.cpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//

#include "Deck.hpp"
#include <vector>
#include <algorithm>  // for shuffle
#include <cstdlib> //srand
#include <ctime> //time
#include <random> //default_random_engine
using namespace std;


//The constructor will initialize an array of card structs and shuffle them.
Deck::Deck(){
    int count = 0;
    for(const auto & s : v_suit){
        for (const auto & f : v_rank){
            cardArr[count] = {count+1, s, f};
            count++;
        }
    }
    shuffleDeck();
    
}

void Deck::shuffleDeck(){
    unsigned seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(&cardArr[0], &cardArr[51], std::default_random_engine(seed));
}

string cardToString(Card* c){
    switch(c->num){
        case 1:
            return "2♦️, ";
        case 2:
            return "3♦️, ";
        case 3:
            return "4♦️, ";
        case 4:
            return "5♦️, ";
        case 5:
            return "6♦️, ";
        case 6:
            return "7♦️, ";
        case 7:
            return "8♦️, ";
        case 8:
            return "9♦️, ";
        case 9:
            return "10♦️, ";
        case 10:
            return "J♦️, ";
        case 11:
            return "Q♦️, ";
        case 12:
            return "K♦️, ";
        case 13:
            return "A♦️, ";
        case 14:
            return "2♣️, ";
        case 15:
            return "3♣️, ";
        case 16:
            return "4♣️, ";
        case 17:
            return "5♣️, ";
        case 18:
            return "6♣️, ";
        case 19:
            return "7♣️, ";
        case 20:
            return "8♣️, ";
        case 21:
            return "9♣️, ";
        case 22:
            return "10♣️, ";
        case 23:
            return "J♣️, ";
        case 24:
            return "Q♣️, ";
        case 25:
            return "K♣️, ";
        case 26:
            return "A♣️, ";
        case 27:
            return "2♥️, ";
        case 28:
            return "3♥️, ";
        case 29:
            return "4♥️, ";
        case 30:
            return "5♥️, ";
        case 31:
            return "6♥️, ";
        case 32:
            return "7♥️, ";
        case 33:
            return "8♥️, ";
        case 34:
            return "9♥️, ";
        case 35:
            return "10♥️, ";
        case 36:
            return "J♥️, ";
        case 37:
            return "Q♥️, ";
        case 38:
            return "K♥️, ";
        case 39:
            return "A♥️, ";
        case 40:
            return "2♠️, ";
        case 41:
            return "3♠️, ";
        case 42:
            return "4♠️, ";
        case 43:
            return "5♠️, ";
        case 44:
            return "6♠️, ";
        case 45:
            return "7♠️, ";
        case 46:
            return "8♠️, ";
        case 47:
            return "9♠️, ";
        case 48:
            return "10♠️, ";
        case 49:
            return "J♠️, ";
        case 50:
            return "Q♠️, ";
        case 51:
            return "K♠️, ";
        case 52:
            return "A♠️, ";
        default:
            return "";
    }
}
