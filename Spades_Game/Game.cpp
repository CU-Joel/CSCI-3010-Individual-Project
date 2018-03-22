//
//  Game.cpp
//  Spades Project
//
//  Created by Joel Davidson on 2/20/18.
//  Copyright © 2018 Joel Davidson. All rights reserved.
//
#include "Deck.hpp"
#include "Game.hpp"

Game::Game(){
    winningScore = 200;
    trump = false;
    gameOver = false;
    DealerPtr = &User;
    setWhoseTurn(&OPP1);
    first = &OPP1;
    second = &TM;
    third = &OPP2;
    fourth = &User;
}

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
        //cout << "\nOpponent 1 is the dealer. It is your team mate's turn to start the bidding.";
    }else if(DealerPtr == &OPP1){
        DealerPtr = &TM;
        TurnPtr = &OPP2;
        first = &OPP2;
        second = &User;
        third = &OPP1;
        fourth = &TM;
        //cout << "\nYour team mate is the dealer. It is Opponent 2's turn to start the bidding.";
    }else if(DealerPtr == &TM){
        DealerPtr = &OPP2;
        TurnPtr = &User;
        first = &User;
        second = &OPP1;
        third = &TM;
        fourth = &OPP2;
        //cout << "\nOpponent 2 is the dealer. It is your turn to start the bidding.";
    }else {
        DealerPtr = &User;
        TurnPtr = &OPP1;
        first = &OPP1;
        second = &TM;
        third = &OPP2;
        fourth = &User;
        //cout << "\nYou are the dealer. It is Opponent 1's turn to start the bidding.";
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

int Game::getWhoseTurn(){
    if(TurnPtr == &User){
        return 1;
    }else if(TurnPtr == &OPP1){
        return 2;
    }else if(TurnPtr == &TM){
        return 3;
    }else{
        return 4;
    }
}

void Game::getBid(){
    userTeamBid = 0;
    computerTeamBid = 0;
    vector<string> sv = User.displayHand();
    emit sendHand(sv);
    Opp1Bid = 0;
    Opp2Bid = 0;
    TMBid = 0;

    for(int i=0; i<4; i++){
        if (TurnPtr != &User){
            //qDebug() << "in the if turnPtr != &user statement";
            bid(TurnPtr);
            moveWhoseTurn();
        } else {
            //qDebug() << "in the else turnPtr = &user statement";
            emit getUserBid();
            moveWhoseTurn();
        }
    }
    //emit printText("All bids in.");
}
/************************************************************/
/*bid function includes the logic used by computer opponents.
 It */
/************************************************************/

void Game::bid(Player* _Player){
    qDebug() << "in the bid()";
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
    //qDebug() << "made it through the for loops";
    if(!count)
        count = 1;
    if(_Player == &OPP1){ 
        Opp1Bid = count;
        computerTeamBid += count;
    } else if(_Player == &OPP2){
        Opp2Bid = count;

        string message;
        if(DealerPtr==&User){
            message ="Opponent 1 bid "+to_string(Opp1Bid)+"\nTeamMate bid "+to_string(TMBid)+"\nOpponent 2 bid "+to_string(Opp2Bid)+"\nYour turn to bid. Enter your bid below.";
        }else if(DealerPtr==&OPP1){
            message ="TeamMate bid "+to_string(TMBid)+"\nOpponent 2 bid "+to_string(Opp2Bid)+"\nYour turn to bid. Enter your bid below.";
        }else if(DealerPtr==&TM){
            message ="Opponent 2 bid "+to_string(Opp2Bid)+"\nYour turn to bid. Enter your bid below.";
        }else
            message ="Enter your bid below.";
        emit printText(message);
        computerTeamBid += count;


    } else {
        TMBid = count;
        userTeamBid += count;
    }
}

void Game::setUserBid(int bid){

    if(bid > 13 || bid < 1){
        emit getUserBid();
        emit printText("Invalid selection. Enter bid below.");
    }else
        userTeamBid += bid;
}

void Game::takeTurn(){

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
    //Determine the winner of the hand
    if(trump){
        if(CardsOnTable[0]->num > CardsOnTable[1]->num && CardsOnTable[0]->num>CardsOnTable[2]->num && CardsOnTable[0]->num > CardsOnTable[3]->num){
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
        emit printText("Your team won the hand. ");
    } else {
        computerTeamTricks +=1;
        emit printText("Your team lost the hand. ");
    }
        //cout << "\n\nYour team: \nScore: " << userTeamScore << "\nBid: " << userTeamBid << " Tricks: " <<  userTeamTricks << "\n\nOpponents: \nScore "<< computerTeamScore << "\nBid: " << computerTeamBid << " Tricks: " << computerTeamTricks;
    vector<string> sv = User.displayHand();
    emit sendHand(sv);
    trump = false;
    CardsOnTable.clear();
}

//playCard() includes the algorithms for what card to play for
//computer players.

void Game::playCard(int i){
    Player* _Player;
    if(i==2){
        _Player = &OPP1;
    }else if(i==3){
        _Player = &TM;
    }else if(i==4){
        _Player = &OPP2;
    }else{
        qDebug() << "error. wrong player number.";
    }

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
        emit printText("Your Turn");// << cardToString(CardsOnTable.back()) << " ";
        emit putOpp1Card(cardToString(CardsOnTable.back()));
    }else if(_Player == &OPP2){
        emit printText("Your Turn");// << cardToString(CardsOnTable.back()) << " ";
        emit putOpp2Card(cardToString(CardsOnTable.back()));
    }else {
        emit printText("Your Turn");// << cardToString(CardsOnTable.back()) << " ";
        emit putTMCard(cardToString(CardsOnTable.back()));
    }
}


int Game::userTurn(int selection){
    qDebug() << "selection received.";
    bool done = false;
    int count=1;

    int diamonds = (int)User.getDiamonds().size();
    int clubs = (int)User.getClubs().size();
    int hearts = (int)User.getHearts().size();
    int spades = (int)User.getSpades().size();

    
    while(!done){
        //cout << endl;
        //cin >> selection;
        if(selection > diamonds+hearts+clubs+spades || selection < 1){
            emit printText("Invalid selection");
            continue;
        }
        if(!CardsOnTable.empty()){
            if(CardsOnTable.front()->suit == Suit::diamond && !User.getDiamonds().empty()){
                if(selection>diamonds){
                    emit printText("Invalid selection. You must play a card of the suit that is lead.");
                    return 0;
                }
            }else if(CardsOnTable.front()->suit == Suit::club && !User.getClubs().empty()){
                if(selection <= diamonds || selection > diamonds+clubs){
                    emit printText("Invalid selection. You must play a card of the suit that is lead.");
                    return 0;
                }
            }else if(CardsOnTable.front()->suit == Suit::heart && !User.getHearts().empty()){
                if(selection <= diamonds+clubs || selection > diamonds+clubs+hearts){
                    emit printText("Invalid selection. You must play a card of the suit that is lead.");
                    return 0;
                }
            }else if(CardsOnTable.front()->suit == Suit::spade && !User.getSpades().empty()){
                if(selection <= diamonds+clubs+hearts){
                    emit printText("Invalid selection. You must play a card of the suit that is lead.");
                    return 0;
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
    emit putPlayerCard(cardToString(CardsOnTable.back()));
    return 1;
}




void Game::tallyPoints(){
    //cout << "\n\n----------Round Over.----------\n";
    if(computerTeamTricks == computerTeamBid){
        computerTeamScore += computerTeamBid*10;
    }else if(computerTeamTricks > computerTeamBid){
        computerTeamScore += computerTeamBid*10;
        computerTeamScore += computerTeamTricks-computerTeamBid;
        computerTeamBags += computerTeamTricks-computerTeamBid;
    }else{
        //cout << "\nOpponent team did not make their bid and get no points.";
    }
    
    if(userTeamTricks == userTeamBid){
        userTeamScore += userTeamBid*10;
    }else if(userTeamTricks > userTeamBid){
        userTeamScore += userTeamBid*10;
        userTeamScore += userTeamTricks-userTeamBid;
        userTeamBags += userTeamTricks-userTeamBid;
    }else{
        //cout << "\nYour team did not make your bid and gets no points.";
    }
    
    if(computerTeamBags >= 10){
        computerTeamScore -= 110;
        computerTeamBags -= 10;
        //cout << "\nOpponent team got 10 bags and looses 100 points.";
    }
    
    if(userTeamBags >= 10){
        userTeamScore -= 110;
        userTeamBags -= 10;
        //cout << "\nYour team got 10 bags and looses 100 points.";
    }
    
    if(computerTeamScore >= winningScore){
        //cout << "\nFinal Score: Your Team: " << userTeamScore << " Opponents: " << computerTeamScore << "\nOpponent team wins. You lose";
        gameOver = true;
    }
    if(userTeamScore >= winningScore){
        //cout << "\nFinal Score: Your Team: " << userTeamScore << " Opponents: " << computerTeamScore << "\nYour team wins!!!";
        gameOver = true;
    }
    //cout << "\n\nYour team: \nScore: " << userTeamScore << "\nBid: " << userTeamBid << " Tricks: " <<  userTeamTricks << "\n\nOpponents: \nScore "<< computerTeamScore << "\nBid: " << computerTeamBid << " Tricks: " << computerTeamTricks << endl;
    computerTeamTricks=0;
    userTeamTricks=0;
    
}

string Game::getScore(){
    string s = "\n\nYour team: \nScore: "+to_string(userTeamScore) +"\nBid: "+to_string(userTeamBid)+ " Tricks: "+to_string(userTeamTricks)+"\n\nOpponents: \nScore "+to_string(computerTeamScore)+"\nBid: "+to_string(computerTeamBid)+" Tricks: "+to_string(computerTeamTricks);
    return s;
}
           

