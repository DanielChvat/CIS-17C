/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 21st, 2021, 11:51 AM
 * Purpose: Fibonacci Sequence
 */

//System Level Libraries
#include <iostream>   //I/O Library
#include <cmath>      //Math Library
using namespace std;  //Library Scope

//User Libraries

//Global Constants
//Science and Math, Conversions, Higher Dimensions
//const to follow

//Function Prototypes
int fibLoop(int);//Fibonacci Loop
int fibRec(int);//Fibonacci Recursion
int fibAray(int);//Utilize an Array
int *fibDyn(int);//Utilize an Array

//Execution Starts Here
int main(int argc, char** argv){
    //Set Random Number Seed Here
    
    //Declare Variables - Known and Unknown, units, range, description
    int nLoop;
    
    //Initialize Variables
    nLoop=45;
    
    //Map inputs to outputs -> i.e. process the inputs
    cout<<"Fibonacci Sequence"<<endl;
    
    //Display the outputs
    cout<<endl<<"Sequence using For Loop and no Array"<<endl;
    for(int n=0;n<=nLoop;n++){
        cout<<fibLoop(n)<<" ";
    }
    cout<<endl<<endl;
    
    //Display the outputs
    cout<<endl<<"Sequence using For Loop and an Array"<<endl;
    for(int n=0;n<=nLoop;n++){
        cout<<fibAray(n)<<" ";
    }
    cout<<endl<<endl;
    
    //Display the outputs
    cout<<endl<<"Sequence using For Loop and return Dyanmic Array"<<endl;
    int *array=fibDyn(nLoop);
    for(int n=0;n<=nLoop;n++){
        cout<<array[n]<<" ";
    }
    cout<<endl<<endl;
    
    
    //Display the outputs
    cout<<endl<<"Sequence using Recursive Call"<<endl;
    for(int n=0;n<=nLoop;n++){
        cout<<fibRec(n)<<" ";
    }
    cout<<endl<<endl;

    
    //Clean up - File closing, memory deallocation, etc....
    delete []array;

    //Exit Stage Right!
    return 0;
}

//Function Implementations
int fibAray(int n){
    //Create array
    int *array=new int[n+1];
    int ans;
    array[0]=0;
    array[1]=1;
    for(int i=2;i<=n;i++){
        array[i]=array[i-1]+array[i-2];
    }
    ans=array[n];
    delete []array;
    return ans;
}

int *fibDyn(int n){
    //Create array
    int *array=new int[n+1];
    array[0]=0;
    array[1]=1;
    for(int i=2;i<=n;i++){
        array[i]=array[i-1]+array[i-2];
    }
    return array;
}

int fibLoop(int n){
    //Base Case
    if(n<=0)return 0;
    if(n==1)return 1;
    int fim1=1,fim2=0,fi=fim1+fim2;
    for(int i=2;i<n;i++){
        fim2=fim1;//Swap 2 with 1
        fim1=fi; //Swap 1 with calculated
        fi=fim1+fim2;  //Calculating the new value
    }
    return fi;
}

int fibRec(int n){
    //Base Case
    if(n<=0)return 0;
    if(n==1)return 1;
    //Recursive Representation
    return fibRec(n-1)+fibRec(n-2);
}