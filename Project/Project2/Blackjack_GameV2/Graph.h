/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Graph.h
 * Author: Daniel
 *
 * Created on June 4, 2023, 11:18 AM
 */
#include <map>
#include <utility>
#include <vector>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H
template<class T>
class Graph{
private:
    map<T, pair<bool, vector<T>>> vertex;
    void DFS(T);
public:
    int nEdges;
    Graph(){nEdges = 0;}
    void insert(T, T);
    void print(T);
};

template<class T>
void Graph<T>::DFS(T v){
    vertex[v].first = true;
    cout<<v<<" ";
    vector<T> p = vertex[v].second;
    for(int i=0; i<p.size(); i++){
        if(vertex[p[i]].first == false)DFS(p[i]);
    }
}

template<class T>
void Graph<T>::insert(T v1, T v2){
    vertex[v1].second.push_back(v2);
    vertex[v2].second.push_back(v1);
    nEdges++;
}

template<class T>
void Graph<T>::print(T v){
    DFS(v);
    cout<<endl;
}

#endif /* GRAPH_H */

