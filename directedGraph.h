#ifndef _DIRECTED_GRAPH_H_
#define _DIRECTED_GRAPH_H_

class DirectedGraph{
private:
    int numOfVertexes;
    int numOfEdges;
    int **graph;

public:
    DirectedGraph();
    ~DirectedGraph();
    void fillGraphFromFile();
    void printGraph();
    void setNumOfVertexes(int);
    void setNumOfEdges(int);
    int getNumOfVertexes();
    int getNumOfEdges();
    int findElement(int, int);
};

#endif