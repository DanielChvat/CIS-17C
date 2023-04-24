/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Player.h
 * Author: Daniel
 *
 * Created on December 15, 2022, 6:58 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "AbsPlayer.h"
#include <queue>
using namespace std;
class Player:public AbsPlayer{
private:
    queue<char> name;
    bool win;
    char again;
    char hit;
    float money;
    float strtMny;
    float bet;
    float prcChng;
    static char PERCENT;
public:
    //Default Constructor
    Player();
    
    //Copy Constructor
    Player(const Player &);
    
    //Destructor 
    ~Player();
    
    //Mutator Functions
    void setWin(bool);
    void setAgn(char);
    void setHit(char);
    void setMny(float);
    void setSMny(float);
    void setBet(float);
    void init();
    void mkBet();
    
    //Accessor Functions
    float getPCL();
    float getPCW();
    bool getWin();
    char getAgn();
    char getHit();
    float getMny();
    float getSMny();
    float getBet();
    char getPrc() const;
    
    void printNm();
};


#endif /* PLAYER_H */

