#include "queue.h"

Queue::Queue(int edges){
    heap = new Edge [edges]; //heap for edges
    heapPosition = 0;
}

Queue::~Queue(){
    delete [] heap;
}

Edge Queue::front(){ // return the edge from the beginning of the queue
    return heap[0];
}

void Queue::push(Edge edge){ // add edge to the heap and recreate heap
    int i, j;
    i = heapPosition++; // set i at the end of the heap
    j = (i-1) >> 1; // calculate parent's heapPosition

    // find place in the heap for the new edge
    while(i && (heap[j].weight > edge.weight)){
        heap[i] = heap[j];
        i = j;
        j = (i-1) >> 1;
    }

    heap[i] = edge; // insert edge to the heap
}

void Queue::pop(){ // remove root from the heap
    int i, j;
    Edge edge;

    if(heapPosition){
        edge = heap[--heapPosition];

        i = 0;
        j = 1;

        while(j<heapPosition){
            if((j+1 < heapPosition) && (heap[j+1].weight < heap[j].weight)) j++;
            if(edge.weight <= heap[j].weight) break;

            heap[i] = heap[j];
            i = j;
            j = (j<<1) + 1;
        }
        heap[i] = edge;
    }
}