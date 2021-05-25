#include "../Dijkstra/dijkstra.cpp"
#include "../Bellman-Ford/bellmanFord.cpp"
#include "../Prim/prim.cpp"
#include "../Kruskal/kruskal.cpp"

void deleteGraphAL(GraphAL **graphAL){
    if((*graphAL)->getNumOfVertexes() == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }

    delete *graphAL;
    *graphAL = new GraphAL();
    cout<<" Successfully deleted list!"<<endl;
}

void deleteGraphIM(GraphIM **graphIM){
    if((*graphIM)->getNumOfVertexes() == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }

    delete *graphIM;
    *graphIM = new GraphIM();
    cout<<" Successfully deleted matrix!"<<endl;
}

void generateGraph(GraphAL **graphAL, GraphIM **graphIM, int v, float density, bool directed){
    if((*graphAL)->getNumOfVertexes() != 0 || (*graphIM)->getNumOfVertexes() != 0){
        deleteGraphAL(graphAL);
        deleteGraphIM(graphIM);
        cout<<" Successfully deleted graphs!"<<endl;
    }

    int edges = (int)((float)(((density/100) * v * (v-1))/2));

    (*graphAL)->addVertexes(v);
    (*graphIM)->addVertexes(v);

    int currentEdges = 0;
    UnionFind set(v);
    Edge edge;
    srand(time(NULL));

    for(int i = 0; i < v; i++){
        set.makeSet(i);
    }

    while(!set.isOneSet()){ //creating connected graph
        // set.printSet();
        do{
            edge.vertexStart = rand()%v;
            edge.vertexEnd = rand()%v;
        }while((edge.vertexStart == edge.vertexEnd) || (set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd)));
        
        edge.weight = (rand()%(2*edges)) + 1;

        if(!directed){
            (*graphAL)->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            (*graphIM)->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        else{
            (*graphAL)->addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            (*graphIM)->addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        currentEdges++;
        set.unionSets(edge);
    }
    //now we have a connected graph and need to add remaining edges
    while(currentEdges < edges){
        do{
            edge.vertexStart = rand()%v;
            edge.vertexEnd = rand()%v;
        }while((edge.vertexStart == edge.vertexEnd) || (*graphIM)->checkIfEdgeExists(edge.vertexStart, edge.vertexEnd));

        edge.weight = (rand()%(2*edges)) + 1;
        if(!directed){
            (*graphAL)->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            (*graphIM)->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        else{
            (*graphAL)->addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            (*graphIM)->addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        currentEdges++;
    }
    cout<<" Successfully filled graph with "<<v<<" vertices and "<<currentEdges<<" edges!"<<endl;
}