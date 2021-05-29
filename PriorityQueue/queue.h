#ifndef _QUEUE_H_
#define _QUEUE_H_

struct Edge{
    int vertexStart; //starting vertex of the edge
    int vertexEnd; //ending vertex of the edge
    int weight; //weight of the edge
};

class Queue{
private:
    Edge *heap; //heap with the edges
    int heapPosition;
public:
    Queue(int); //constructor
    ~Queue(); // destructor
    Edge front(); //get the edge from the heap's root
    void push(Edge); //add new edge to the heap
    void pop(); //remove the root from the heap
};

#endif