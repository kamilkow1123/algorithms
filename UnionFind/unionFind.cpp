#include "unionFind.h"

UnionFind::UnionFind(int n){
    set = new UnionNode[n];
    this->numOfVer = n;
}

UnionFind::~UnionFind(){
    delete [] set;
}

void UnionFind::makeSet(int v){
    set[v].up = v;
    set[v].rank = 0;
}

int UnionFind::findSet(int v){
    if(set[v].up != v){
        set[v].up = findSet(set[v].up);
    }
    return set[v].up;
}

void UnionFind::unionSets(Edge edge){
    int root1, root2;

    root1 = findSet(edge.vertexStart); //find the root of the tree with vertexStart
    root2 = findSet(edge.vertexEnd); //find the root of the tree with vertexEnd

    if(root1 != root2){ //roots must be different
        if(set[root1].rank > set[root2].rank){ //compare roots ranks
            set[root2].up = root1;             //root1 is greater, union root2
        }
        else{
            set[root1].up = root2; //root2 is greater, union root1
            if(set[root1].rank == set[root2].rank){
                set[root2].rank++;
            }
        }
    }
}

bool UnionFind::isOneSet(){
    int firstParent = findSet(0);

    for(int i = 1; i < this->numOfVer; i++){
        if(firstParent != findSet(i)) return false;
    }
    return true;
}

void UnionFind::printSet(){
    cout<<"Set: ";
    for(int i = 0; i < this->numOfVer; i++){
        cout<<findSet(i)<<" ";
    }
    cout<<endl;
}