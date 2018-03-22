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
    shuffle(&cardArr[0], &cardArr[52], std::default_random_engine(seed));
}

string cardToString(Card* c){
    switch(c->num){
        case 1:
            return ":/cards/PNG-cards/2d.png";
        case 2:
            return ":/cards/PNG-cards/3d.png";
        case 3:
            return ":/cards/PNG-cards/4d.png";
        case 4:
            return ":/cards/PNG-cards/5d.png";
        case 5:
            return ":/cards/PNG-cards/6d.png";
        case 6:
            return ":/cards/PNG-cards/7d.png";
        case 7:
            return ":/cards/PNG-cards/8d.png";
        case 8:
            return ":/cards/PNG-cards/9d.png";
        case 9:
            return ":/cards/PNG-cards/10d.png";
        case 10:
            return ":/cards/PNG-cards/jd.png";
        case 11:
            return ":/cards/PNG-cards/qd.png";
        case 12:
            return ":/cards/PNG-cards/kd.png";
        case 13:
            return ":/cards/PNG-cards/ad.png";
        case 14:
            return ":/cards/PNG-cards/2c.png";
        case 15:
            return ":/cards/PNG-cards/3c.png";
        case 16:
            return ":/cards/PNG-cards/4c.png";
        case 17:
            return ":/cards/PNG-cards/5c.png";
        case 18:
            return ":/cards/PNG-cards/6c.png";
        case 19:
            return ":/cards/PNG-cards/7c.png";
        case 20:
            return ":/cards/PNG-cards/8c.png";
        case 21:
            return ":/cards/PNG-cards/9c.png";
        case 22:
            return ":/cards/PNG-cards/10c.png";
        case 23:
            return ":/cards/PNG-cards/jc.png";
        case 24:
            return ":/cards/PNG-cards/qc.png";
        case 25:
            return ":/cards/PNG-cards/kc.png";
        case 26:
            return ":/cards/PNG-cards/ac.png";
        case 27:
            return ":/cards/PNG-cards/2h.png";
        case 28:
            return ":/cards/PNG-cards/3h.png";
        case 29:
            return ":/cards/PNG-cards/4h.png";
        case 30:
            return ":/cards/PNG-cards/5h.png";
        case 31:
            return ":/cards/PNG-cards/6h.png";
        case 32:
            return ":/cards/PNG-cards/7h.png";
        case 33:
            return ":/cards/PNG-cards/8h.png";
        case 34:
            return ":/cards/PNG-cards/9h.png";
        case 35:
            return ":/cards/PNG-cards/10h.png";
        case 36:
            return ":/cards/PNG-cards/jh.png";
        case 37:
            return ":/cards/PNG-cards/qh.png";
        case 38:
            return ":/cards/PNG-cards/kh.png";
        case 39:
            return ":/cards/PNG-cards/ah.png";
        case 40:
            return ":/cards/PNG-cards/2s.png";
        case 41:
            return ":/cards/PNG-cards/3s.png";
        case 42:
            return ":/cards/PNG-cards/4s.png";
        case 43:
            return ":/cards/PNG-cards/5s.png";
        case 44:
            return ":/cards/PNG-cards/6s.png";
        case 45:
            return ":/cards/PNG-cards/7s.png";
        case 46:
            return ":/cards/PNG-cards/8s.png";
        case 47:
            return ":/cards/PNG-cards/9s.png";
        case 48:
            return ":/cards/PNG-cards/10s.png";
        case 49:
            return ":/cards/PNG-cards/js.png";
        case 50:
            return ":/cards/PNG-cards/qs.png";
        case 51:
            return ":/cards/PNG-cards/ks.png";
        case 52:
            return ":/cards/PNG-cards/as.png";
        default:
            return "";
    }
}
