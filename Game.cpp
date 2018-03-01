//
//  Game.cpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//
#include "Deck.hpp"
#include "Game.hpp"

Game::Game(int maxScore){
    winningScore = maxScore;
    trump = false;
    gameOver = false;
    DealerPtr = &User;
    setWhoseTurn(&OPP1);
    first = &OPP1;
    second = &TM;
    third = &OPP2;
    fourth = &User;
}

void Game::deal(){
    D.shuffleDeck();
    for(int i=0; i<52; i+=4){
        OPP1.putInHand(D.dealCard(i));
        TM.putInHand(D.dealCard(i+1));
        OPP2.putInHand(D.dealCard(i+2));
        User.putInHand(D.dealCard(i+3));
    }
    OPP1.sortHand();
    TM.sortHand();
    OPP2.sortHand();
    User.sortHand();
}

void Game::moveDealer(){
    if(DealerPtr == &User){
        DealerPtr = &OPP1;
        TurnPtr = &TM;
        first = &TM;
        second = &OPP2;
        third = &User;
        fourth = &OPP1;
        cout << "\nOpponent 1 is the dealer. It is your team mate's turn to start the bidding.";
    }else if(DealerPtr == &OPP1){
        DealerPtr = &TM;
        TurnPtr = &OPP2;
        first = &OPP2;
        second = &User;
        third = &OPP1;
        fourth = &TM;
        cout << "\nYour team mate is the dealer. It is Opponent 2's turn to start the bidding.";
    }else if(DealerPtr == &TM){
        DealerPtr = &OPP2;
        TurnPtr = &User;
        first = &User;
        second = &OPP1;
        third = &TM;
        fourth = &OPP2;
        cout << "\nOpponent 2 is the dealer. It is your turn to start the bidding.";
    }else {
        DealerPtr = &User;
        TurnPtr = &OPP1;
        first = &OPP1;
        second = &TM;
        third = &OPP2;
        fourth = &User;
        cout << "\nYou are the dealer. It is Opponent 1's turn to start the bidding.";
    }
}

void Game::moveWhoseTurn(){
    if(TurnPtr == &User){
        TurnPtr = &OPP1;
    }else if(TurnPtr == &OPP1){
        TurnPtr = &TM;
    }else if(TurnPtr == &TM){
        TurnPtr = &OPP2;
    }else{
        TurnPtr = &User;
    }
}

void Game::getBid(){
    userTeamBid = 0;
    computerTeamBid = 0;
    cout << "\nLet the bidding begin.";
    cout << "\nYour hand: ";
    User.displayHand();
    cout << endl;
    if (TurnPtr != &User){
        bid(TurnPtr);
        moveWhoseTurn();
    } else {
        userBid();
        moveWhoseTurn();
    }
    if (TurnPtr != &User){
        bid(TurnPtr);
        moveWhoseTurn();
    } else {
        userBid();
        moveWhoseTurn();
    }if (TurnPtr != &User){
        bid(TurnPtr);
        moveWhoseTurn();
    } else {
        userBid();
        moveWhoseTurn();
    }if (TurnPtr != &User){
        bid(TurnPtr);
        moveWhoseTurn();
    } else {
        userBid();
        moveWhoseTurn();
    }
    cout << "\n\nYour team: \nScore: " << userTeamScore << "\nBid: " << userTeamBid << " Tricks: " <<  userTeamTricks << "\n\nOpponents: \nScore "<< computerTeamScore << "\nBid: " << computerTeamBid << " Tricks: " << computerTeamTricks;
}
/************************************************************/
/*bid function includes the logic used by computer opponents.
 It */
/************************************************************/

void Game::bid(Player* _Player){
    int count=0;
    for(auto const& i : _Player->getDiamonds()){
        if(i->face == Face::king || i->face == Face::ace)
            count++;
    }
    for(auto const& i : _Player->getClubs()){
        if(i->face == Face::king || i->face == Face::ace)
            count++;
    }
    for(auto const& i : _Player->getHearts()){
        if(i->face == Face::king || i->face == Face::ace)
            count++;
    }
    for(auto const& i : _Player->getSpades()){
        if(i->num>45)
            count++;
    }
    if(!count)
        count = 1;
    if(_Player == &OPP1){ 
        cout << "\nOpponent 1 bids: " << count;
        computerTeamBid += count;
    } else if(_Player == &OPP2){
        cout << "\nOpponent 2 bids: " << count;
        computerTeamBid += count;
    } else {
        cout << "\nTeammate bids: " << count;
        userTeamBid += count;
    }
}

void Game::userBid(){
    int userBid =0;
    bool done = false;
    while(!done){
        cout << "\nEnter your bid.\n";
        cin >> userBid;
        if(userBid > 13 || userBid < 1){
            cout << "Invalid bid. Bid must be between 1 and 13.";
        } else {
            done = true;
        }
    }
    userTeamBid += userBid;
    
}

void Game::takeTurn(){
    trump = false;
    if(TurnPtr == &User){
        first = &User;
        second = &OPP1;
        third = &TM;
        fourth = &OPP2;
    }else if(TurnPtr == &OPP1){
        first = &OPP1;
        second = &TM;
        third = &OPP2;
        fourth = &User;
    }else if(TurnPtr == &TM){
        first = &TM;
        second = &OPP2;
        third = &User;
        fourth = &OPP1;
    }else{
        first = &OPP2;
        second = &User;
        third = &OPP1;
        fourth = &TM;
    }
    int leadingCard=0;
    
    /*This commented section is for testing purposes so I can see what is in the
     computer players hand and make sure they are playing the right
     card.*/
    
    /*
    cout << "\nOpponent 1's hand: ";
    OPP1.displayHand();
    cout << "\nTeammates's hand: ";
    TM.displayHand();
    cout << "\nOpponent 2's hand: ";
    OPP2.displayHand();
     */
    //cout << "\nYour hand: ";
    //User.displayHand();
    
    if (TurnPtr != &User){
        playCard(TurnPtr);
        moveWhoseTurn();
    } else {
        userTurn();
        moveWhoseTurn();
    }
    if (TurnPtr != &User){
        playCard(TurnPtr);
        moveWhoseTurn();
    } else {
        userTurn();
        moveWhoseTurn();
    }
    if (TurnPtr != &User){
        playCard(TurnPtr);
        moveWhoseTurn();
    } else {
        userTurn();
        moveWhoseTurn();
    }
    if (TurnPtr != &User){
        playCard(TurnPtr);
        moveWhoseTurn();
    } else {
        userTurn();
        moveWhoseTurn();
    }
        
    //Determine the winner of the hand
    if(trump){
        if(CardsOnTable[0]->num>CardsOnTable[1]->num && CardsOnTable[0]->num>CardsOnTable[2]->num && CardsOnTable[0]->num>CardsOnTable[3]->num){
            WinningPtr = first;
        }else if(CardsOnTable[1]->num>CardsOnTable[0]->num && CardsOnTable[1]->num>CardsOnTable[2]->num && CardsOnTable[1]->num>CardsOnTable[3]->num){
            WinningPtr = second;
        }else if(CardsOnTable[2]->num>CardsOnTable[0]->num && CardsOnTable[2]->num>CardsOnTable[1]->num && CardsOnTable[2]->num>CardsOnTable[3]->num){
            WinningPtr = third;
        }else {
            WinningPtr = fourth;
        }
    } else if (CardsOnTable[0]->suit == Suit::diamond){
        WinningPtr = first;
        leadingCard = CardsOnTable[0]->num;
        if(CardsOnTable[1]->suit == Suit::diamond && CardsOnTable[1]->num > leadingCard){
            WinningPtr = second;
            leadingCard = CardsOnTable[1]->num;
        }
        if(CardsOnTable[2]->suit == Suit::diamond && CardsOnTable[2]->num > leadingCard){
            WinningPtr = third;
            leadingCard = CardsOnTable[2]->num;
        }
        if(CardsOnTable[3]->suit == Suit::diamond && CardsOnTable[3]->num > leadingCard){
            WinningPtr = fourth;
        }
    }else if (CardsOnTable[0]->suit == Suit::club){
        WinningPtr = first;
        leadingCard = CardsOnTable[0]->num;
        if(CardsOnTable[1]->suit == Suit::club && CardsOnTable[1]->num > leadingCard){
            WinningPtr = second;
            leadingCard = CardsOnTable[1]->num;
        }
        if(CardsOnTable[2]->suit == Suit::club && CardsOnTable[2]->num > leadingCard){
            WinningPtr = third;
            leadingCard = CardsOnTable[2]->num;
        }
        if(CardsOnTable[3]->suit == Suit::club && CardsOnTable[3]->num > leadingCard){
            WinningPtr = fourth;
        }
    }else {
        WinningPtr = first;
        leadingCard = CardsOnTable[0]->num;
        if(CardsOnTable[1]->suit == Suit::heart && CardsOnTable[1]->num > leadingCard){
            WinningPtr = second;
            leadingCard = CardsOnTable[1]->num;
        }
        if(CardsOnTable[2]->suit == Suit::heart && CardsOnTable[2]->num > leadingCard){
            WinningPtr = third;
            leadingCard = CardsOnTable[2]->num;
        }
        if(CardsOnTable[3]->suit == Suit::heart && CardsOnTable[3]->num > leadingCard){
            WinningPtr = fourth;
        }
    }
    TurnPtr = WinningPtr;
    if(WinningPtr == &User || WinningPtr == &TM){
        userTeamTricks +=1;
        cout << "\n\nYour team won the hand. ";
    } else {
        computerTeamTricks +=1;
        cout << "\n\nYour team lost the hand. ";
    }
        cout << "\n\nYour team: \nScore: " << userTeamScore << "\nBid: " << userTeamBid << " Tricks: " <<  userTeamTricks << "\n\nOpponents: \nScore "<< computerTeamScore << "\nBid: " << computerTeamBid << " Tricks: " << computerTeamTricks;
    
    cout << endl;
    CardsOnTable.clear();
}

//playCard() includes the algorithms for what card to play for
//computer players.

void Game::playCard(Player* _Player){
    if(CardsOnTable.empty()){
        if(_Player->getDiamonds().size() >= _Player->getClubs().size() && _Player->getDiamonds().size() >= _Player->getHearts().size() && !_Player->getDiamonds().empty()){
            CardsOnTable.push_back(_Player->playDiamond((int)_Player->getDiamonds().size()-1));
        }else if(_Player->getClubs().size() >= _Player->getHearts().size() && _Player->getClubs().size() >= _Player->getDiamonds().size() && !_Player->getClubs().empty()){
            CardsOnTable.push_back(_Player->playClub((int)_Player->getClubs().size()-1));
        }else if(!_Player->getHearts().empty()){
            CardsOnTable.push_back(_Player->playHeart((int)_Player->getHearts().size()-1));
        }else {
            CardsOnTable.push_back(_Player->playSpade((int)_Player->getSpades().size()-1));
            trump = true;
        }
        
    }else if (CardsOnTable.front()->suit == Suit::diamond){
        if(!_Player->getDiamonds().empty()){
            CardsOnTable.push_back(_Player->playDiamond((int)_Player->getDiamonds().size()-1));
        }else if(!_Player->getSpades().empty()){
            CardsOnTable.push_back(_Player->playSpade((int)_Player->getSpades().size()-1));
            trump = true;
        }else if(!_Player->getClubs().empty()){
            CardsOnTable.push_back(_Player->playClub((int)_Player->getClubs().size()-1));
        }
        else {
            CardsOnTable.push_back(_Player->playHeart((int)_Player->getHearts().size()-1));
        }
        
    }else if (CardsOnTable.front()->suit == Suit::club){
        if(!_Player->getClubs().empty()){
            CardsOnTable.push_back(_Player->playClub((int)_Player->getClubs().size()-1));
        }else if(!_Player->getSpades().empty()){
            CardsOnTable.push_back(_Player->playSpade((int)_Player->getSpades().size()-1));
            trump = true;
        }else if(!_Player->getDiamonds().empty()){
            CardsOnTable.push_back(_Player->playDiamond((int)_Player->getDiamonds().size()-1));
            
        }else {
            CardsOnTable.push_back(_Player->playHeart((int)_Player->getHearts().size()-1));
        }
    }else if (CardsOnTable.front()->suit == Suit::heart){
        if(!_Player->getHearts().empty()){
            CardsOnTable.push_back(_Player->playHeart((int)_Player->getHearts().size()-1));
        }else if(!_Player->getSpades().empty()){
            CardsOnTable.push_back(_Player->playSpade((int)_Player->getSpades().size()-1));
            trump = true;
        }else if(!_Player->getDiamonds().empty()){
            CardsOnTable.push_back(_Player->playDiamond((int)_Player->getDiamonds().size()-1));
            
        }else {
            CardsOnTable.push_back(_Player->playClub((int)_Player->getClubs().size()-1));
        }
    }else if(!_Player->getSpades().empty()){
        CardsOnTable.push_back(_Player->playSpade((int)_Player->getSpades().size()-1));
        trump = true;
    }else if(!_Player->getClubs().empty()){
        CardsOnTable.push_back(_Player->playClub((int)_Player->getClubs().size()-1));
        
    }else if(!_Player->getHearts().empty()){
        CardsOnTable.push_back(_Player->playHeart((int)_Player->getHearts().size()-1));
        
    }else
        CardsOnTable.push_back(_Player->playDiamond((int)_Player->getDiamonds().size()-1));
    
    
    
    if(_Player == &OPP1){
        //std::this_thread::sleep_for(std::chrono::milliseconds(300));
        cout << "\nOpponent 1 plays:  " << cardToString(CardsOnTable.back()) << " ";
    }else if(_Player == &OPP2){
        //std::this_thread::sleep_for(std::chrono::milliseconds(300));
        cout << "\nOpponent 2 plays:  " << cardToString(CardsOnTable.back()) << " ";
    }else {
        //std::this_thread::sleep_for(std::chrono::milliseconds(300));
        cout << "\nTeam mate plays:  " << cardToString(CardsOnTable.back()) << " ";
    }
}

void Game::userTurn(){
    bool done = false;
    int count=1;
    int selection;
    int diamonds = (int)User.getDiamonds().size();
    int clubs = (int)User.getClubs().size();
    int hearts = (int)User.getHearts().size();
    int spades = (int)User.getSpades().size();
    cout << "\n\nChoose which card to play.";
    
    for(auto const& i : User.getDiamonds()){
        cout << "\nEnter " << count << " for " << cardToString(i);
        count++;
    }
    for(auto const& i : User.getClubs()){
        cout << "\nEnter " << count << " for " << cardToString(i);
        count++;
    }
    for(auto const& i : User.getHearts()){
        cout << "\nEnter " << count << " for " << cardToString(i);
        count++;
    }
    for(auto const& i : User.getSpades()){
        cout << "\nEnter " << count << " for " << cardToString(i);
        count++;
    }
    
    while(!done){
        cout << endl;
        cin >> selection;
        if(selection > diamonds+hearts+clubs+spades || selection < 1){
            cout << "Invalid selection";
            continue;
        }
        if(!CardsOnTable.empty()){
            if(CardsOnTable.front()->suit == Suit::diamond && !User.getDiamonds().empty()){
                if(selection>diamonds){
                    cout << "\nInvalid selection. You must play a card of the suit that is lead.";
                    continue;
                }
            }else if(CardsOnTable.front()->suit == Suit::club && !User.getClubs().empty()){
                if(selection <= diamonds || selection > diamonds+clubs){
                    cout << "\nInvalid selection. You must play a card of the suit that is lead.";
                    continue;
                }
            }else if(CardsOnTable.front()->suit == Suit::heart && !User.getHearts().empty()){
                if(selection <= diamonds+clubs || selection > diamonds+clubs+hearts){
                    cout << "\nInvalid selection. You must play a card of the suit that is lead.";
                    continue;
                }
            }else if(CardsOnTable.front()->suit == Suit::spade && !User.getSpades().empty()){
                if(selection <= diamonds+clubs+hearts){
                    cout << "\nInvalid selection. You must play a card of the suit that is lead.";
                    continue;
                }
            }
        }
        if(selection <= diamonds){
            CardsOnTable.push_back(User.playDiamond(selection-1));
        }else if(selection > diamonds && selection <= clubs+diamonds){
            CardsOnTable.push_back(User.playClub(selection-diamonds-1));
        }else if(selection > diamonds+clubs && selection <= diamonds+clubs+hearts){
            CardsOnTable.push_back(User.playHeart(selection-diamonds-clubs-1));
        }else{
            CardsOnTable.push_back(User.playSpade(selection-diamonds-clubs-hearts-1));
            trump = true;
        }
        done = true;
    }
}




void Game::tallyPoints(){
    cout << "\n\n----------Round Over.----------\n";
    if(computerTeamTricks == computerTeamBid){
        computerTeamScore += computerTeamBid*10;
    }else if(computerTeamTricks > computerTeamBid){
        computerTeamScore += computerTeamBid*10;
        computerTeamScore += computerTeamTricks-computerTeamBid;
        computerTeamBags += computerTeamTricks-computerTeamBid;
    }else{
        cout << "\nOpponent team did not make their bid and get no points.";
    }
    
    if(userTeamTricks == userTeamBid){
        userTeamScore += userTeamBid*10;
    }else if(userTeamTricks > userTeamBid){
        userTeamScore += userTeamBid*10;
        userTeamScore += userTeamTricks-userTeamBid;
        userTeamBags += userTeamTricks-userTeamBid;
    }else{
        cout << "\nYour team did not make your bid and gets no points.";
    }
    
    if(computerTeamBags >= 10){
        computerTeamScore -= 110;
        computerTeamBags -= 10;
        cout << "\nOpponent team got 10 bags and looses 100 points.";
    }
    
    if(userTeamBags >= 10){
        userTeamScore -= 110;
        userTeamBags -= 10;
        cout << "\nYour team got 10 bags and looses 100 points.";
    }
    
    if(computerTeamScore >= winningScore){
        cout << "\nFinal Score: Your Team: " << userTeamScore << " Opponents: " << computerTeamScore << "\nOpponent team wins. You lose";
        gameOver = true;
    }
    if(userTeamScore >= winningScore){
        cout << "\nFinal Score: Your Team: " << userTeamScore << " Opponents: " << computerTeamScore << "\nYour team wins!!!";
        gameOver = true;
    }
    cout << "\n\nYour team: \nScore: " << userTeamScore << "\nBid: " << userTeamBid << " Tricks: " <<  userTeamTricks << "\n\nOpponents: \nScore "<< computerTeamScore << "\nBid: " << computerTeamBid << " Tricks: " << computerTeamTricks << endl;
    computerTeamTricks=0;
    userTeamTricks=0;
    
}
           

