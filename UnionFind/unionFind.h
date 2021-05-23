#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include "../PriorityQueue/queue.h"
struct UnionNode{
    int up;
    int rank;
};

class UnionFind{
private:
    UnionNode *set; // array to store id of graph's vertices
public:
    UnionFind(int n); //create array
    ~UnionFind();
    void makeSet(int v);
    int findSet(int v);
    void unionSets(Edge e);
};

#endif