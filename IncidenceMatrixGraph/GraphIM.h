#ifndef _GRAPH_INCIDENCE_MATRIX_H_
#define _GRAPH_INCIDENCE_MATRIX_H_

class GraphIM{ // graph in incidence matrix
private:
    int **graph; //two-dimensional array representing incidence matrix
    int numOfVertexes; //number of vertices in the graph
    int numOfEdges; //number of edges in the graph
    int weight; //weight of the whole graph
public:
    GraphIM(); //constructor
    ~GraphIM(); //destructor
    void fillGraphFromFile(bool); //fill the incidence matrix with data from file
    void printGraph(); //printing incidence matrix
    void setNumOfVertexes(int); //set the number of vertices
    void setNumOfEdges(int); //set the number of edges
    int getNumOfVertexes(); //get the number of vertices
    int getNumOfEdges(); //get the number of edges
    int findElement(int, int); //return the value from the array
    int getStartingVertexOfEdge(int); //get the starting vertex of the given edge
    int getEndingVertexOfEdge(int); //get the ending vertex of the given edge
    int getEndingVertexOfUndirectedEdge(int, int); //get the ending vertex of the given undirected edge
    void addDirectedEdge(int, int, int); //add directed edge to the graph
    void addUndirectedEdge(int, int, int); //add undirected edge to the graph
    void addVertexes(int); //add vertexes to the graph, without the edges
    bool checkIfEdgeExists(int, int); //return true if the given edge exist, false if it doesn't exist
};

#endif