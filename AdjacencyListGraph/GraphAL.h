#ifndef _GRAPH_ADJACENCY_LIST_H_
#define _GRAPH_ADJACENCY_LIST_H_

struct Node{ //list's node
    int vertex; //index of the vertex
    int edge; //value of the edge
    Node *next; //pointer to the next node

    Node(int vertex, int edge){ //constructor
        this->vertex = vertex;
        this->edge = edge;
        this->next = nullptr;
    }
};

class GraphAL{ //graph in adjacency list
private:
    Node **array; //array for the lists - each list represents neighbours of the given vertex
    int numOfVertexes; //number of vertices in the graph
    int numOfEdges; //number of edges in the graph
    int weight; //weight of the whole graph
public:
    GraphAL(); //constructor
    ~GraphAL(); //descructor
    void fillGraphFromFile(bool); //fill the adjacency list with data from file
    void printGraph(); //printing adjacency list
    void setNumOfVertexes(int); //set the number of vertices
    void setNumOfEdges(int); //set the number of edges
    int getNumOfVertexes(); //get the number of vertices
    int getNumOfEdges(); //get the number of edges
    Node *getList(int); //get the neighbours of given vertex - actually the first vertex in the list
    void addVertexes(int); //add vertexes to the graph, without the edges
    void addDirectedEdge(int, int, int); //add directed edge to the graph
    void addUndirectedEdge(int, int, int); //add undirected edge to the graph
};

#endif