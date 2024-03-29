#include<iostream>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
#include "../PriorityQueue/queue.cpp"
using namespace std;

GraphAL* primAL(GraphAL *graph, int src){ //adjacency list
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){ //if graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return nullptr;
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
    int v = src;
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

    delete q;
    delete [] visited;

    return mst;
}

GraphIM* primIM(GraphIM *graph, int src){
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){ //if graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return nullptr;
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
    int v = src;
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

    delete q;
    delete [] visited;

    return mst;
}