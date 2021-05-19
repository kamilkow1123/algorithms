#ifndef _QUEUE_H_
#define _QUEUE_H_

struct Edge{
    int vertexStart;
    int vertexEnd;
    int weight;

    Edge(){
        this->vertexStart = 0;
        this->vertexEnd = 0;
        this->weight = 0;
    }

    Edge(int vertexStart, int vertexEnd, int weight){
        this->vertexStart = vertexStart;
        this->vertexEnd = vertexEnd;
        this->weight = weight;
    }
};

class Queue{
private:
    Edge *heap;
    int heapPosition;
public:
    Queue(int);
    ~Queue();
    Edge front();
    void push(Edge);
    void pop();
};

#endif