#ifndef _GRAPH_INCIDENCE_MATRIX_H_
#define _GRAPH_INCIDENCE_MATRIX_H_

class GraphIM{ // graph in incidence matrix
private:
    int **graph;
    int numOfVertexes;
    int numOfEdges;
    int weight; //weight of the whole graph
public:
    GraphIM();
    ~GraphIM();
    void fillGraphFromFile(bool);
    void printGraph();
    void setNumOfVertexes(int);
    void setNumOfEdges(int);
    int getNumOfVertexes();
    int getNumOfEdges();
    int findElement(int, int);
    int getStartingVertexOfEdge(int);
    int getEndingVertexOfEdge(int);
    void addDirectedEdge(int, int, int, int);
    void addUndirectedEdge(int, int, int, int);
    void addVertexes(int);
};

#endif