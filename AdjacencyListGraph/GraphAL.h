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

class GraphAL{ // graph in adjacency list
private:    
    Node **array;
    int numOfVertexes;
    int numOfEdges;
    int weight; //weight of the whole graph
public:
    GraphAL();
    ~GraphAL();
    void fillGraphFromFile(bool);
    void printGraph();
    void setNumOfVertexes(int);
    void setNumOfEdges(int);
    int getNumOfVertexes();
    int getNumOfEdges();
    Node *getList(int);
    void addNode(int, int, int);
};

#endif