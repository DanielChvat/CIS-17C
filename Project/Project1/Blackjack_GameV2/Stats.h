/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Stats.h
 * Author: Daniel
 *
 * Created on October 27, 2022, 3:40 PM
 */
#include <fstream>
#include <map>
#include <set>
using namespace std;

#ifndef STATS_H
#define STATS_H

struct Stats{
    char cols; //Number of Cols in 2d Array
    char card[52];
    char suit[52];
    map<char, int> m; //Map to translate card faces to integer values
    set<char> uCard; //Set of Unique Cards in the deck
};



#endif /* STATS_H */
