#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include "../PriorityQueue/queue.h"
struct UnionNode{
    int up;
    int rank;
};

class UnionFind{
private:
    UnionNode *set;             // array to store id of graph's vertices
    int numOfVer;               // number of vertexes in the set
public:
    UnionFind(int n);           //create array
    ~UnionFind();               //delete array
    void makeSet(int v);        //make set in the array
    int findSet(int v);         //returns the root of the vertex's tree
    void unionSets(Edge e);     //union two sets into one
    bool isOneSet();
};

#endif