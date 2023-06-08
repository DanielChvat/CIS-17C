/*
*File: main.cpp
*Author: Daniel Chvat
*Created on June 4 2023, 12:23 PM
*Purpose: Blackjack Card Game with STL concepts in CIS/CSC 17C as well as Recursion, Recursive Sorts
*Trees, and Graphs
*Project Length: 1624 Lines
*/

//System Libraries
#include <iostream> //Input Output Library
#include <ctime>    //Time Library
#include <string>   //String Library
#include <cmath>    //Math Library
#include <cstdlib>  //C Standard Library
#include <iomanip>  //Formatting Library
#include <fstream>  //File Input Output Library
#include <vector>   //Vector Library
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
using namespace std;
//User Libraries
#include "Game.h"
#include "Card.h"
#include "MyVctr.h"
#include "Face.h"
#include "Player.h"
#include "File.h"
#include "Stats.h"
#include "Deck.h"
#include "Tree.h"
#include "Graph.h"
//Global Constants

//Mathematical/Physics/Conversions/Higher Dimensioned Arrays
const unsigned char PERCENT=100;
//Function Prototypes
void stats(File *, const int, const char *, const char *);
void wrtBin(Stats, File *);
int prtion(int[], int, int);
void qSort(int[], int, int);
void swap(int[], int, int);
Stats *readBin(File *);
bool hasWon(int, int, int limit=21);
string getSuit(char *, int);
void destroy(Stats *);
void srtVals(MyVctr<int> &, Stats *);
void print(char);
//Execution begins here
int main(){
    //Declare Variables
    int prvVal = 0;
    const char NFILES = 3;
    File **file = new File*[NFILES];
    Player player;
    Game game;
    char again='\0';
    float chng=0;
    float bet=0;
    char hit = '\0';
    bool win = false;
    char info = '\0';
    //Initialize Variables
    //Create all 3 file classes
    for(int i=0; i<NFILES; i++)file[i] = new File();
    file[0]->setName("Cards.dat");
    file[1]->setName("Suits.dat");
    file[2]->setName("Stats.dat");
    file[0]->getFile()->open(file[0]->getName(), ios::in|ios::out|ios::binary|ios::trunc);
    file[1]->getFile()->open(file[1]->getName(), ios::in|ios::out|ios::binary|ios::trunc);
    file[2]->getFile()->open(file[2]->getName(), ios::in|ios::out|ios::binary|ios::trunc);
    Deck deck;
    
    file[0]->getFile()->write(deck.getCrd(), sizeof(char)*deck.getNCrd());
    file[1]->getFile()->write(deck.getSut(), sizeof(char)*deck.getNCrd());
    //Map Inputs to Outputs
    //Generate Random Deck of Cards with suits into two different files
    file[0]->getFile()->close();
    file[1]->getFile()->close();
    file[2]->getFile()->close();
    //Display Results
    //Game Play
    do{
        game.setPVal(0);
        game.setDVal(0);
        //crdwSut="";
        //Open the Cards.dat and Suits.dat files to be read and used later on in the game
        file[0]->getFile()->open(file[0]->getName(), ios::in|ios::binary);
        file[1]->getFile()->open(file[1]->getName(), ios::in|ios::binary);
        cout<<endl;
        cout<<"You Currently Have "<<fixed<<setprecision(2)<<player.getMny()<<" Dollars Left!"<<endl;
        //Ensure player has more than 0 Dollars Left
        if(player.getMny()>0){
            cout<<"How Much Would You Like to Bet on This Game?"<<endl;
            cin>>bet;
            player.setBet(bet);
            //Check if the bet is valid
            while(player.getBet()>player.getMny() || player.getBet()<0){
                cout<<"That Bet is Not Valid!"<<endl;
                cout<<"Please Enter How Much You Wish to Bet:"<<endl;
                cin>>bet;
                player.setBet(bet);
                player.mkBet();
            }
            //Grab a card from the cards file to start the player with
            if(game.getIdx()<deck.getNCrd()){
                //Fill cards and Suits Table to be printed later
                //Display a message of the card and its suit that the player received
                //Calculate the current value of all the players cards         
                game.setPVal(game.getCVal(deck.getVec(), prvVal));
                cout<<endl;
                cout<<"You Received: "<<deck.trnslte(true,game.getIdx())<<" of "<<deck.trnslte(false, game.getIdx())<<endl;
                cout<<endl;
                cout<<"Your Cards Total Value is Currently: "<<game.getPVal()<<endl<<endl;
                try{
                    ++game;
                }catch(string error){
                    cout<<error;
                    exit(-1);
                }
            }else{
                cout<<"No cards left in deck to draw from";
                exit(0);
            }
            game.incDVal(rand()%11+1);
            cout<<"The Dealers Shown Card Value is: "<<game.getDVal()<<endl<<endl;
            cout<<"Would You Like to Hit (Y/N)"<<endl;
            cin>>hit;
            player.setHit(hit);
            if(game.getIdx()<deck.getNCrd()){
                do{
                    if(player.getHit()=='Y'||player.getHit()=='y'){
                        
                        if(game.getIdx()<deck.getNCrd()){
                            //Calculate the current value of all the players cards         
                            game.setPVal(game.getCVal(deck.getVec(), prvVal));
                            cout<<endl;
                            //Display Message to player saying the card they received their current total card value and the dealers show card value
                            cout<<"You Received: "<<deck.trnslte(true, game.getIdx())<<" of "<<deck.trnslte(false, game.getIdx())<<endl;
                            cout<<endl;
                            cout<<"Your Cards Total Value is Currently: "<<game.getPVal()<<endl<<endl;
                            cout<<"The Dealers Shown Card Value is: "<<game.getDVal()<<endl<<endl;
                            try{
                                ++game;
                            }catch(string error){
                                cout<<error;
                                exit(-1);
                            }
                        }else{
                            //Tell the player there are no cards left in the deck and exit program
                            cout<<"No cards left in deck to draw from";
                            exit(0);
                        }
                        if(game.getPVal()<21){
                            cout<<"Would you like to hit (Y/N)"<<endl;
                            cin>>hit;
                            player.setHit(hit);
                        }else player.setHit('N');
                    }
                }while(game.getIdx()<deck.getNCrd() && (player.getHit()=='Y'||player.getHit()=='y'));
                //Increase dealers card value by a random value from 1 to 10 if their total card value is less than 17
                while(game.getDVal()<17)game.incDVal(rand()%11+1);
            }
            //Check if the player has won
            win=hasWon(game.getPVal(), game.getDVal());
            player.setWin(win);
            cout<<endl<<endl<<"Results:"<<endl;
            if(player.getWin()){
                //Pay out the bet at a 3:2 Ratio(found on blackjack.org) if the player has won
                chng=player.getPCW();
                //Display message saying player won
                cout<<"Congratulations You Have Won :) "<<endl;
                cout<<"Your Total Card Value Was: "<<game.getPVal()<<endl;
                cout<<"The Dealer's Total Card Value Was: "<<game.getDVal()<<endl;
                cout<<"Your New Balance is $"<<player.getMny()<<endl;
                cout<<"Your money increased by around "<<fixed<<setprecision(0)<<round(chng)<<"%"<<endl;
            }else if(game.getPVal()==game.getDVal() ||(game.getPVal()>21 && game.getDVal()>21)){
                //Display a message saying nobody won
                cout<<"Your Total Card Value Was: "<<game.getPVal()<<endl;
                cout<<"The Dealer's Total Card Value Was: "<<game.getDVal()<<endl;
                cout<<"Nobody Wins"<<endl;
            }else{
                chng=player.getPCL();
                cout<<endl;
                //Display message saying player lost
                cout<<"Sorry You Lost :( "<<endl;
                cout<<"Your Total Card Value Was: "<<game.getPVal()<<endl;
                cout<<"The Dealer's Total Card Value Was: "<<game.getDVal()<<endl;
                cout<<"Your New Balance is "<<fixed<<setprecision(2)<<player.getMny()<<endl;
                //Display how much player's money decreased and round to the nearest Value
                cout<<"Your money decreased by around "<<fixed<<setprecision(0)<<round(player.getPrc()-chng)<<"%"<<endl;
            }
        }
        if(player.getMny()>0){
            cout<<"Would you like to play again?(Y/N)"<<endl;
            cin>>again;
            player.setAgn(again);
            
        }
        prvVal+=game.getPVal();
    }while(player.getMny()>0 && (player.getAgn()=='Y'||player.getAgn()=='y'));
    //Write Game Stats into file
    //Close Files Correctly
    file[0]->getFile()->close();
    file[1]->getFile()->close();
    file[2]->getFile()->close();
    stats(file[2], deck.getNCrd(), deck.getCrd(), deck.getSut());
    Stats *stats = readBin(file[2]);
    //Ask Player if they want to see info about the game
    cout<<"Would You Like To See Some Info About The Game?(Y/N)"<<endl;
    cin>>info;
    game.setInfo(info);
    if(game.getInfo()=='Y' || game.getInfo()=='y'){
        cout<<endl<<endl;
        cout<<"Stats: "<<endl;
        cout<<"-------"<<endl; 
        cout<<endl<<"Heres A List Of All The Cards That Were In The Deck With Their Suits"<<endl<<endl;
        cout<<"Card:        ";
        int cVals[stats->cols];
        for(int i=0; i<deck.getNCrd();i++){
            cout<<stats->card[i];
            cVals[i] = stats->m[stats->card[i]]; //Bidirectional Iterator
        }
        cout<<endl;
        
        cout<<"Sorted Card: ";
        Tree tree;
        for(int i=0; i<deck.getNCrd(); i++)tree.insert(static_cast<int>(stats->card[i]));
        tree.inOrder(tree.root);
        cout<<endl;
        //sort(stats->card, stats->card + stats->cols);
        //for_each(stats->card, stats->card+stats->cols, print);
        for(int i=0; i<stats->cols; i++)stats->uCard.insert(stats->card[i]);
        cout<<endl;
        cout<<"Suit:        ";
        list<char>::iterator it; //Bidirectional Iterator
        for(it = stats->s.begin(); it!=stats->s.end(); it++)cout<<*it;
        cout<<endl;
        cout<<"Sorted Suit: ";
        sort(stats->suit, stats->suit + stats->cols);
        for_each(stats->suit, stats->suit+stats->cols, print);
        cout<<endl<<endl;
        cout<<"Card Values:        ";
        for(int i=0; i<deck.getNCrd();i++)cout<<cVals[i]<<" ";
        //Sort the Card Values
        srtVals(deck.getVec(), stats);
        cout<<endl;
        cout<<"Unique Card Faces in Deck: ";
        set<char>::iterator itr;
        for(itr = stats->uCard.begin(); itr!=stats->uCard.end();itr++)cout<<*itr<<" "; //Bidirectional Iterator
        cout<<endl;
        cout<<"Unique Card Suits in Deck: ";
        Graph<char> g;
        for(int i=1; i<deck.getNCrd(); i++){
            g.insert(stats->suit[0], stats->suit[i]);
            g.insert(stats->suit[i-1], stats->suit[i]); //Proof of Concept to show that this is a graph and not a tree
        }
        g.print(stats->suit[0]);
        cout<<endl;
        cout<<"Stats for Graph Used to Determine Unique Suits in Deck: "<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<"Number of Vertices: "<<deck.getNCrd()<<endl;
        cout<<"Number of Edges   : "<<g.nEdges<<endl;
        cout<<endl;
        cout<<"Tree Used To Store Cards: "<<endl;
        cout<<"------------------------------"<<endl<<endl;
        tree.display(tree.root, 0);
    }
    
    cout<<endl<<endl<<"Thanks For Playing ";
    player.printNm();
    cout<<endl;
    //De-Allocate Memory
    destroy(stats);
    //Exit Stage Right
    return 0;
}
bool hasWon(int pVal, int dVal, int limit){
    if(pVal>dVal && pVal<=limit || (pVal<=21 && dVal>21))return true;
    else return false;
}

//Get Initial Values for player structure
void stats(File *f, const int NCARDS, const char *a, const char *b){
    Stats s;
    s.cols=NCARDS;
    //Row 1 is Cards
    //Row 2 is Suits
    for(int i=0; i<s.cols; i++){
        s.card[i]=a[i];
        s.suit[i]=b[i];
    }
    wrtBin(s, f);

}

void wrtBin(Stats s, File *f){
    f->getFile()->open(f->getName(),ios::out|ios::binary);
    f->getFile()->write(&s.cols, sizeof(char));
    for(int i=0; i<s.cols; i++)f->getFile()->write(&s.card[i], sizeof(char));
    for(int i=0; i<s.cols; i++)f->getFile()->write(&s.suit[i], sizeof(char));
    f->getFile()->close();
}
Stats *readBin(File *f){
    Stats *s = new Stats;
    long cursor=0L;
    map<char, int>::iterator it = s->m.begin();
    s->m.insert(pair<char, int>('A', 1));
    s->m.insert(pair<char, int>('2', 2));
    s->m.insert(pair<char, int>('3', 3));
    s->m.insert(pair<char, int>('4', 4));
    s->m.insert(pair<char, int>('5', 5));
    s->m.insert(pair<char, int>('6', 6));
    s->m.insert(pair<char, int>('7', 7));
    s->m.insert(pair<char, int>('8', 8));
    s->m.insert(pair<char, int>('9', 9));
    s->m.insert(pair<char, int>('T', 10));
    s->m.insert(pair<char, int>('Q', 10));
    s->m.insert(pair<char, int>('K', 10));
    s->m.insert(pair<char, int>('J', 10));
    f->getFile()->open(f->getName(),ios::in|ios::binary);
    f->getFile()->seekg(cursor, ios::beg);
    f->getFile()->read(&s->cols, sizeof(char));
    char *c = new char[s->cols];
    for(int i=0; i<s->cols; i++)f->getFile()->read(&c[i], sizeof(char));
    copy(c, c+s->cols, s->card);
    for(int i=0; i<s->cols; i++)f->getFile()->read(&s->suit[i], sizeof(char));
    for(int i=0; i<s->cols; i++)s->s.push_back(s->suit[i]);
    return s;
    f->getFile()->close();
}

void srtVals(MyVctr<int> &v, Stats *s){
    //Copy the vector into an int array for sorting
    int temp[v.size()];
    for(int i=0; i<v.size(); i++)temp[i]=v[i];
    qSort(temp, 0, (sizeof(temp) / sizeof(temp[0]))-1);
    cout<<endl;
    
    cout<<"Sorted Card Values: ";
    for(int i=0; i<v.size(); i++){
        s->vals.push(temp[i]);
        cout<<s->vals.top()<<" ";
    }
    
    cout<<endl;
    cout<<endl;
}

//De-Allocate Memory
void destroy(Stats *stats){
    delete stats;
}

void print(char n){
    cout<<n;
}

int prtion(int arr[], int low, int high) {
  if (high == low)
    return high;
  else if (high == (low + 1)) {
    if (arr[high] < arr[low])
      swap(arr, low, high);
    return high;
  }

  int mid = (high + low) / 2;

  if (arr[mid] != arr[high])
    swap(arr, mid, high);

  int pivot = high;
  int i = low;
  int j = high - 1;

  while (i < j) {
    while (arr[i] < arr[pivot])
      i++;
    while (arr[i] >= arr[pivot] && arr[j] >= arr[pivot] && j > i)
      j--;
    if (arr[j] < arr[pivot] && j > i)
      swap(arr, i, j);
  }

  if (arr[i] != arr[pivot])
    swap(arr, i, pivot);
  return i;
}

void qSort(int arr[], int low, int high) {
  if (low < high) {
    int p = prtion(arr, low, high);
    qSort(arr, low, p - 1);
    qSort(arr, p + 1, high);
  }
}

void swap(int arr[], int a, int b) {
  arr[a] = arr[a] ^ arr[b];
  arr[b] = arr[b] ^ arr[a];
  arr[a] = arr[a] ^ arr[b];
}