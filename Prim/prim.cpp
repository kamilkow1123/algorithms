#include<iostream>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
#include "../PriorityQueue/queue.cpp"
using namespace std;

void primAL(GraphAL *graph, int src, bool printResult){ //adjacency list
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){ //if graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }
    int edges = graph->getNumOfEdges(); //number of edges
	bool *visited = new bool[vertexes]; //boolean array to mark visted/unvisted for each vertex
    GraphAL *mst = new GraphAL();
    mst->addVertexes(vertexes);

	//set the vertexes with infinity distance and mark them unvisited
	for(int i = 0; i < vertexes; i++)
	{
		visited[i] = false;
	}

    visited[src] = true; //source vertex is set to be visited
    int v = 0;
    Edge e;
    Queue *q = new Queue(edges);

    for(int i = 0; i < vertexes - 1; i++){
        for(Node *ver = graph->getList(v); ver; ver = ver->next){
            if(!visited[ver->vertex]){
                e.vertexStart = v;
                e.vertexEnd = ver->vertex;
                e.weight = ver->edge;
                q->push(e); //add the edge to the queue
            }
        }

        do{
            e = q->front();
            q->pop();
        } while(visited[e.vertexEnd]);

        mst->addUndirectedEdge(e.vertexStart, e.vertexEnd, e.weight);

        visited[e.vertexEnd] = true;
        v = e.vertexEnd;
    }

    if(printResult){
        cout<<endl<<" MST from Prim's algorithm in adjacency list:"<<endl;
        mst->printGraph();
    }

    delete q;
    delete [] visited;
}

void primIM(GraphIM *graph, int src, bool printResult){
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){ //if graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }
    int edges = graph->getNumOfEdges(); //number of edges
	bool *visited = new bool[vertexes]; //boolean array to mark visted/unvisted for each vertex
    GraphIM *mst = new GraphIM();
    mst->addVertexes(vertexes);

	//set the vertexes with infinity distance and mark them unvisited
	for(int i = 0; i < vertexes; i++)
	{
		visited[i] = false;
	}

    visited[src] = true; //source vertex is set to be visited
    int v = 0;
    Edge e;
    Queue *q = new Queue(edges);

    for(int i = 0; i < vertexes - 1; i++){
        for(int j = 0; j < edges; j++){
            if(graph->findElement(v,j) > 0 && !visited[graph->getEndingVertexOfUndirectedEdge(j,v)]){
                e.vertexStart = v;
                e.vertexEnd = graph->getEndingVertexOfUndirectedEdge(j,v);
                e.weight = graph->findElement(v,j);
                q->push(e); //add the edge to the queue
            }
        }

        do{
            e = q->front();
            q->pop();
        } while(visited[e.vertexEnd]);

        mst->addUndirectedEdge(e.vertexStart, e.vertexEnd, e.weight);

        visited[e.vertexEnd] = true;
        v = e.vertexEnd;
    }

    if(printResult){
        cout<<endl<<" MST from Prim's algorithm in incidence matrix:"<<endl;
        mst->printGraph();
    }

    delete q;
    delete [] visited;
}