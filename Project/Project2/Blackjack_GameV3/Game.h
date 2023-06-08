/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Game.h
 * Author: Daniel
 *
 * Created on December 16, 2022, 2:23 PM
 */

#ifndef GAME_H
#define GAME_H
#include "MyVctr.h"

class Game{
private:
    int pVal;
    int dVal;
    int crntIdx;
    char info;
public:
    //Default Constructor
    Game();
    
    //Mutator Functions
    void setPVal(int n){pVal=n;}
    void setDVal(int n){dVal=n;}
    void setInfo(char i){info = i;}
    void incDVal(int n){dVal+=n;}
    //Overloaded Operator
    void operator++();
    
    //Accessor Functions
    int getPVal(){return pVal;}
    int getDVal(){return dVal;}
    int getIdx(){return crntIdx;}
    char getInfo(){return info;}
    int getCVal(MyVctr<int> &, const int);
};
#endif /* GAME_H */

