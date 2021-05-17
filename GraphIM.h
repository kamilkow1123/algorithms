#ifndef _GRAPH_INCIDENCE_MATRIX_H_
#define _GRAPH_INCIDENCE_MATRIX_H_

class GraphIM{ // graph in incidence matrix
private:
    int numOfVertexes;
    int numOfEdges;
    int **graph;

public:
    GraphIM();
    ~GraphIM();
    void fillGraphFromFile();
    void printGraph();
    void setNumOfVertexes(int);
    void setNumOfEdges(int);
    int getNumOfVertexes();
    int getNumOfEdges();
    int findElement(int, int);
    int getStartingVertexOfEdge(int);
    int getEndingVertexOfEdge(int);
};

#endif