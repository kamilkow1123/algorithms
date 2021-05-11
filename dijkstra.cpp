#include<iostream>
#include<iomanip>
#include<climits>     
using namespace std;

// this method returns a minimum distance for the 
// vertex which is not included in visited.
int minimumDist(int dist[], bool visited[]) 
{
	int min=INT_MAX,index;
              
	for(int i=0;i<6;i++) 
	{
		if(visited[i]==false && dist[i]<=min)      
		{
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void Dijkstra(int graph[6][6],int src) // adjacency matrix used is 6x6
{
	int dist[6]; // integer array to calculate minimum distance for each node.                            
	bool visited[6];// boolean array to mark visted/unvisted for each node.
	
	// set the nodes with infinity distance
	// except for the initial node and mark
	// them unvisited.  
	for(int i = 0; i<6; i++)
	{
		dist[i] = INT_MAX;
		visited[i] = false;	
	}
	
	dist[src] = 0;   // Source vertex distance is set to zero.             
	
	for(int i = 0; i<6; i++)                           
	{
		int m=minimumDist(dist,visited); // vertex not yet included.
		visited[m]=true;// m with minimum distance included in visited.
		for(int i = 0; i<6; i++)                  
		{
			// Updating the minimum distance for the particular node.
			if(!visited[i] && graph[m][i] && dist[m]!=INT_MAX && dist[m]+graph[m][i]<dist[i])
				dist[i]=dist[m]+graph[m][i];
		}
	}
	cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i = 0; i<6; i++)                      
	{ //Printing
		char str=65+i; // Ascii values for pritning A,B,C..
		cout<<str<<"\t\t\t"<<dist[i]<<endl;
	}
}

int main()
{
    int numOfEdges, numOfVertexes;
    
    cout<<"Enter number of edges and number of vertexes: ";
    cin>>numOfEdges>>numOfVertexes;

    int **graph = new int *[numOfVertexes];

    for(int i = 0; i<numOfVertexes; ++i){
        graph[i] = new int [numOfEdges];
        for(int j = 0; j<numOfEdges; ++j)
            graph[i][j] = 0;                    //filling the array with zeros
    }

    int vertexStart, vertexEnd, distanceValue;
    for(int i = 0; i<numOfEdges; i++){
        cout<<"Enter the starting and ending vertex of the edge and distance value: ";
        cin>>vertexStart>>vertexEnd>>distanceValue;
        graph[vertexStart][i] = distanceValue;
        graph[vertexEnd][i] = -1;
    }

    //printing graph
    for(int i = 0; i<numOfVertexes; i++){
        for(int j = 0; j<numOfEdges; j++){
            cout<<setw(5)<<graph[i][j];
        }
        cout<<endl;
    }

    //deleting the array
    for(int i = 0; i<numOfVertexes; i++) delete [] graph[i];
    delete [] graph;

	// Dijkstra(graph,0);
	return 0;	                        
}