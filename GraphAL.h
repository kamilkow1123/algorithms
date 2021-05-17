#ifndef _GRAPH_ADJACENCY_LIST_H_
#define _GRAPH_ADJACENCY_LIST_H_

struct Node{
    int vertex;
    int edge;
    Node *next;

    Node(int vertex, int edge){
        this->vertex = vertex;
        this->edge = edge;
        this->next = nullptr;
    }
};

class GraphAL{
private:    
    Node **array;
    int numOfVertexes;
    int numOfEdges;
public:
    GraphAL();
    ~GraphAL();
    void fillGraphFromFile();
    void printGraph();
    void setNumOfVertexes(int);
    void setNumOfEdges(int);
    int getNumOfVertexes();
    int getNumOfEdges();
};

#endif