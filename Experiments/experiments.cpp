#include "../Dijkstra/dijkstra.cpp"
#include "../Bellman-Ford/bellmanFord.cpp"
#include "../Prim/prim.cpp"
#include "../Kruskal/kruskal.cpp"
#include "../Timer/timer.cpp"

float unitFactor = 1000000000.0f; //nanoseconds
string unit = "ns";

void deleteGraphAL(GraphAL **graphAL, bool shouldPrint){
    if((*graphAL)->getNumOfVertexes() == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }

    delete *graphAL;
    *graphAL = new GraphAL();
    if(shouldPrint) cout<<" Successfully deleted list!"<<endl;
}

void deleteGraphIM(GraphIM **graphIM, bool shouldPrint){
    if((*graphIM)->getNumOfVertexes() == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }

    delete *graphIM;
    *graphIM = new GraphIM();
    if(shouldPrint) cout<<" Successfully deleted matrix!"<<endl;
}

void generateGraph(GraphAL **graphAL, GraphIM **graphIM, int v, float density, bool directed, bool shouldPrint){
    if((*graphAL)->getNumOfVertexes() != 0 || (*graphIM)->getNumOfVertexes() != 0){
        deleteGraphAL(graphAL, shouldPrint);
        deleteGraphIM(graphIM, shouldPrint);
        if(shouldPrint) cout<<" Successfully deleted graphs!"<<endl;
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
    if(shouldPrint) cout<<" Successfully filled graph with "<<v<<" vertices and "<<currentEdges<<" edges!"<<endl;
}

void dijkstraExperiment(GraphAL **graphAL, GraphIM **graphIM){
    srand(time(NULL));
    float timeAL, timeIM;
    int numberOfVer, density, numberOfMeasurements;

    do{
        cout<<" Enter the number of vertices: ";
        cin>>numberOfVer;
    }while(numberOfVer<0 || numberOfVer>1000);

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100);

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>500);

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, true, false);
        Timer timerAL;
        dijkstraAL(*graphAL, 0, false);
        timeAL += timerAL.getTime().count() * unitFactor;

        Timer timerIM;
        dijkstraIM(*graphIM, 0, false);
        timeIM += timerIM.getTime().count() * unitFactor;
    }
    cout<<" Dijkstra's algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl;
    cout<<" Dijkstra's algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl;

    deleteGraphAL(graphAL, false);
    deleteGraphIM(graphIM, false);
}

void bellmanFordExperiment(GraphAL **graphAL, GraphIM **graphIM){
    srand(time(NULL));
    float timeAL, timeIM;
    int numberOfVer, density, numberOfMeasurements;

    do{
        cout<<" Enter the number of vertices: ";
        cin>>numberOfVer;
    }while(numberOfVer<0 || numberOfVer>1000);

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100);

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>500);

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, true, false);
        Timer timerAL;
        bellmanFordAL(*graphAL, 0, false);
        timeAL += timerAL.getTime().count() * unitFactor;

        Timer timerIM;
        bellmanFordIM(*graphIM, 0, false);
        timeIM += timerIM.getTime().count() * unitFactor;
    }
    cout<<" Bellman-Ford algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl;
    cout<<" Bellman-Ford algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl;

    deleteGraphAL(graphAL, false);
    deleteGraphIM(graphIM, false);
}

void primExperiment(GraphAL **graphAL, GraphIM **graphIM){
    srand(time(NULL));
    float timeAL, timeIM;
    int numberOfVer, density, numberOfMeasurements;

    do{
        cout<<" Enter the number of vertices: ";
        cin>>numberOfVer;
    }while(numberOfVer<0 || numberOfVer>1000);

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100);

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>500);

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, false, false);
        Timer timerAL;
        primAL(*graphAL, 0, false);
        timeAL += timerAL.getTime().count() * unitFactor;

        Timer timerIM;
        primIM(*graphIM, 0, false);
        timeIM += timerIM.getTime().count() * unitFactor;
    }
    cout<<" Prim's algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl;
    cout<<" Prim's algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl;

    deleteGraphAL(graphAL, false);
    deleteGraphIM(graphIM, false);
}

void kruskalExperiment(GraphAL **graphAL, GraphIM **graphIM){
    cout<<" Kruskal experiment"<<endl;
}