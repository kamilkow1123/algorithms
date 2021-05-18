#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "GraphAL.h"
using namespace std;

GraphAL::GraphAL(){
    this->array = nullptr;
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
}

GraphAL::~GraphAL(){
    Node *temp, *temp2;
    for(int i = 0; i < numOfVertexes; i++){
        temp2 = array[i];
        while(temp2){
            temp = temp2;
            temp2 = temp2->next;
            delete temp;
        }
    }

    delete [] array;
}

void GraphAL::printGraph(){
    if(numOfVertexes == 0){
        cout<<"Graph is empty!"<<endl;
        return;
    }

    Node *temp;

    for(int i = 0; i < numOfVertexes; i++){
        cout<<"["<<i<<"] = ";
        temp = array[i];
        while(temp){
            cout<<setw(3)<<"("<<temp->vertex<<":"<<temp->edge<<")";
            if(temp->next) cout<<setw(4)<<"->";
            temp = temp->next;
        }
        cout<<endl;
    }
    cout<<endl;
}

void GraphAL::setNumOfEdges(int num){
    this->numOfEdges = num;
}

void GraphAL::setNumOfVertexes(int num){
    this->numOfVertexes = num;
}

int GraphAL::getNumOfEdges(){
    return numOfEdges;
}

int GraphAL::getNumOfVertexes(){
    return numOfVertexes;
}

void GraphAL::fillGraphFromFile(){
    if(numOfVertexes != 0){
        cout<<"Graph is not empty"<<endl;
        return;
    }

    fstream in;
    in.open("graph.txt", ios::in);

    if(in.good()){
        int numberOfEdges, numberOfVertexes;
        in>>numberOfEdges>>numberOfVertexes;

        array = new Node *[numberOfVertexes];

        for(int i = 0; i<numberOfVertexes; i++) array[i] = nullptr;

        int vertexStart, vertexEnd, distanceValue;
        Node *temp;

        for(int i = 0; i<numberOfEdges; i++){
            in>>vertexStart>>vertexEnd>>distanceValue;
            temp = new Node(vertexEnd, distanceValue);
            temp->next = array[vertexStart];
            array[vertexStart] = temp;
        }

        setNumOfEdges(numberOfEdges);
        setNumOfVertexes(numberOfVertexes);

        in.close();
    }
    else{
        cout<<"Cannot open graph.txt"<<endl;
    }
}

Node *GraphAL::getList(int ver){
    return array[ver];
}

int minimumVertex(int *dist, bool *visited, int n) 
{
	int min = -1;
              
	for(int i = 0; i < n; i++) 
	{
		if(!visited[i] && (min == -1 || dist[i] < dist[min]))      
		{ 
		    min = i;
		}
	}
	return min;
}

void dijkstra(GraphAL *graph, int src) // incidence matrix 
{
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    int edges = graph->getNumOfEdges(); // number of edges
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex                          
	bool *visited = new bool[vertexes]; // boolean array to mark visted/unvisted for each vertex
    int *previous = new int[vertexes]; // integer array of previous vertexes
	
	// set the vertexes with infinity distance and mark them unvisited 
	for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
        previous[i] = -1;
	}
	
	distance[src] = 0;   // source vertex distance is set to zero            
	
	for(int i = 0; i < vertexes; i++)                           
	{
		int min = minimumVertex(distance,visited, vertexes); // find minimum vertex
		visited[min] = true; // min with minimum distance included in visited

		for(Node *ver = graph->getList(min); ver; ver = ver->next)                  
		{
			// updating the minimum distance for the particular vertex
			if(!visited[ver->vertex] && (distance[ver->vertex] > distance[min] + ver->edge)){
                distance[ver->vertex] = distance[min] + ver->edge;
                previous[ver->vertex] = min;
            }
		}
	}
    cout<<"Results of the Dijkstra algorithm: "<<endl;
	cout<<"Vertex\tDistance from source\tPrevious vertex"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
	}
    cout<<endl;

    delete [] visited;
    delete [] distance;
    delete [] previous;
}

void bellman_ford(GraphAL *graph, int src){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    int edges = graph->getNumOfEdges(); // number of edges
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex  
    int *previous = new int[vertexes]; // integer array of previous vertexes
    bool stop;

    // set the vertexes with infinity distance
    for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
        previous[i] = -1;
	}

    distance[src] = 0;   // source vertex distance is set to zero      

    for(int i = 0; i < vertexes-1; i++){
        stop = true;
        for(int j = 0; j < vertexes; j++){
            for(Node *ver = graph->getList(j); ver; ver = ver->next){
                // updating the minimum distance for the particular vertex
                if((distance[ver->vertex] > distance[j] + ver->edge)){
                    distance[ver->vertex] = distance[j] + ver->edge;
                    previous[ver->vertex] = j;
                    stop = false;
                }
            }
        }
        if(stop) break;
    }

    // Detect negative cycle
    for(int j = 0; j < vertexes; j++){
        for(Node *ver = graph->getList(j); ver; ver = ver->next){
            if((distance[ver->vertex] > distance[j] + ver->edge)){
                cout<<"Negative cycle detected!"<<endl;
                return;
            }
        }
    }

    cout<<"Results of the Bellman-Ford algorithm: "<<endl;
	cout<<"Vertex\tDistance from source\tPrevious vertex"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
	}
    cout<<endl;

    delete [] distance;
    delete [] previous;
}

int main(){
    GraphAL *graph = new GraphAL();

    graph->fillGraphFromFile();
    graph->printGraph();

    dijkstra(graph, 0);
    bellman_ford(graph, 0);

    return 0;
}