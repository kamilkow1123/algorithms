#include "../Dijkstra/dijkstra.cpp"
#include "../Bellman-Ford/bellmanFord.cpp"
#include "../Prim/prim.cpp"
#include "../Kruskal/kruskal.cpp"
#include "../Timer/timer.cpp"

float unitFactor = 1000000.0f; //microseconds
string unit = " microseconds";

void deleteGraphAL(GraphAL **graphAL, bool shouldPrint){ //delete the graph in the adjacency list
    if((*graphAL)->getNumOfVertexes() == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }

    delete *graphAL;
    *graphAL = new GraphAL();
    if(shouldPrint) cout<<" Successfully deleted list!"<<endl;
}

void deleteGraphIM(GraphIM **graphIM, bool shouldPrint){ //delete the graph in the incidence matrix
    if((*graphIM)->getNumOfVertexes() == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }

    delete *graphIM;
    *graphIM = new GraphIM();
    if(shouldPrint) cout<<" Successfully deleted matrix!"<<endl;
}

void generateGraph(GraphAL **graphAL, GraphIM **graphIM, int v, float density, bool directed, bool shouldPrint){
    if((*graphAL)->getNumOfVertexes() != 0 || (*graphIM)->getNumOfVertexes() != 0){ //if the graph is not empty, delete its content
        deleteGraphAL(graphAL, shouldPrint);
        deleteGraphIM(graphIM, shouldPrint);
        if(shouldPrint) cout<<" Successfully deleted graphs!"<<endl;
    }

    int edges = (int)((float)(((density/100) * v * (v-1))/2)); //calculate the number of edges from the given density and number of vertices

    (*graphAL)->addVertexes(v); //initialize graph with vertices, no edges yet
    (*graphIM)->addVertexes(v); //initialize graph with vertices, no edges yet

    int currentEdges = 0;
    UnionFind set(v); //we will use union find to make sure that the graph is connected
    Edge edge;
    srand(time(NULL));

    for(int i = 0; i < v; i++){
        set.makeSet(i);
    }

    while(!set.isOneSet()){ //creating connected graph
        do{
            edge.vertexStart = rand()%v;
            edge.vertexEnd = rand()%v;
        }while((edge.vertexStart == edge.vertexEnd) || (set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd))); //draw new edge if the vertices are the same or if they are in the same set

        edge.weight = (rand()%(2*edges)) + 1; //draw the edge's weight from the range <1, number of edges * 2>

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
        }while((edge.vertexStart == edge.vertexEnd) || (*graphIM)->checkIfEdgeExists(edge.vertexStart, edge.vertexEnd)); //draw new edge if the vertices are the same or if the edge already exists

        edge.weight = (rand()%(2*edges)) + 1; //draw the edge's weight from the range <1, number of edges * 2>

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
    }while(numberOfVer<0 || numberOfVer>1000); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>5000); //ask for the input again if the value is not in the expected range

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, true, false); //generate random graph for each measurement
        Timer timerAL; //set the timer for adjacency list
        dijkstraAL(*graphAL, 0); //perform Dijkstra's algorithm on the generated graph in adjacency list
        timeAL += timerAL.getTime().count() * unitFactor; //stop the timer and count the time

        Timer timerIM; //set the timer for incidence matrix
        dijkstraIM(*graphIM, 0); //perform Dijkstra's algorithm on the generated graph in incidence matrix
        timeIM += timerIM.getTime().count() * unitFactor; //stop the timer and count the time
    }
    cout<<fixed<<setprecision(0)<<" Dijkstra's algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl; //count the average time for dijkstra in adjacency list
    cout<<fixed<<setprecision(0)<<" Dijkstra's algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl; //count the average time for dijkstra in incidence matrix

    deleteGraphAL(graphAL, false); //delete the graph in adjacency list
    deleteGraphIM(graphIM, false); //delete the graph in incidence matrix
}

void bellmanFordExperiment(GraphAL **graphAL, GraphIM **graphIM){
    srand(time(NULL));
    float timeAL, timeIM;
    int numberOfVer, density, numberOfMeasurements;

    do{
        cout<<" Enter the number of vertices: ";
        cin>>numberOfVer;
    }while(numberOfVer<0 || numberOfVer>1000); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>5000); //ask for the input again if the value is not in the expected range

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, true, false); //generate random graph for each measurement
        Timer timerAL; //set the timer for adjacency list
        bellmanFordAL(*graphAL, 0, false); //perform Bellman-Ford algorithm on the generated graph in adjacency list
        timeAL += timerAL.getTime().count() * unitFactor; //stop the timer and count the time

        Timer timerIM; //set the timer for incidence matrix
        bellmanFordIM(*graphIM, 0, false); //perform Bellman-Ford algorithm on the generated graph in incidence matrix
        timeIM += timerIM.getTime().count() * unitFactor; //stop the timer and count the time
    }
    cout<<fixed<<setprecision(0)<<" Bellman-Ford algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl; //count the average time for bellman-ford in adjacency list
    cout<<fixed<<setprecision(0)<<" Bellman-Ford algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl; //count the average time for bellman-ford in incidence matrix

    deleteGraphAL(graphAL, false); //delete the graph in adjacency list
    deleteGraphIM(graphIM, false); //delete the graph in incidence matrix
}

void primExperiment(GraphAL **graphAL, GraphIM **graphIM){
    srand(time(NULL));
    float timeAL, timeIM;
    int numberOfVer, density, numberOfMeasurements;

    do{
        cout<<" Enter the number of vertices: ";
        cin>>numberOfVer;
    }while(numberOfVer<0 || numberOfVer>1000); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>5000); //ask for the input again if the value is not in the expected range

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, false, false); //generate random graph for each measurement
        Timer timerAL; //set the timer for adjacency list
        primAL(*graphAL, 0); //perform Prim's algorithm on the generated graph in adjacency list
        timeAL += timerAL.getTime().count() * unitFactor; //stop the timer and count the time

        Timer timerIM; //set the timer for incidence matrix
        primIM(*graphIM, 0); //perform Prim's algorithm on the generated graph in incidence matrix
        timeIM += timerIM.getTime().count() * unitFactor; //stop the timer and count the time
    }
    cout<<fixed<<setprecision(0)<<" Prim's algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl; //count the average time for prim in adjacency list
    cout<<fixed<<setprecision(0)<<" Prim's algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl; //count the average time for prim in incidence matrix

    deleteGraphAL(graphAL, false); //delete the graph in adjacency list
    deleteGraphIM(graphIM, false); //delete the graph in incidence matrix
}

void kruskalExperiment(GraphAL **graphAL, GraphIM **graphIM){
    srand(time(NULL));
    float timeAL, timeIM;
    int numberOfVer, density, numberOfMeasurements;

    do{
        cout<<" Enter the number of vertices: ";
        cin>>numberOfVer;
    }while(numberOfVer<0 || numberOfVer>1000); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the density [%]: ";
        cin>>density;
    }while(density<0 || density>100); //ask for the input again if the value is not in the expected range

    do{
        cout<<" Enter the number of measurements: ";
        cin>>numberOfMeasurements;
    }while(numberOfMeasurements<0 || numberOfMeasurements>5000); //ask for the input again if the value is not in the expected range

    timeAL = 0;
    timeIM = 0;
    for(int i = 0; i<numberOfMeasurements; i++){
        generateGraph(graphAL, graphIM, numberOfVer, density, false, false); //generate random graph for each measurement
        Timer timerAL; //set the timer for adjacency list
        kruskalAL(*graphAL); //perform Kruskal's algorithm on the generated graph in adjacency list
        timeAL += timerAL.getTime().count() * unitFactor; //stop the timer and count the time

        Timer timerIM; //set the timer for incidence matrix
        kruskalIM(*graphIM); //perform Kruskal's algorithm on the generated graph in incidence matrix
        timeIM += timerIM.getTime().count() * unitFactor; //stop the timer and count the time
    }
    cout<<fixed<<setprecision(0)<<" Kruskal's algorithm for adjacency list took on average: "<<timeAL/numberOfMeasurements<<unit<<endl; //count the average time for kruskal in adjacency list
    cout<<fixed<<setprecision(0)<<" Kruskal's algorithm for incidence matrix took on average: "<<timeIM/numberOfMeasurements<<unit<<endl; //count the average time for kruskal in incidence matrix

    deleteGraphAL(graphAL, false); //delete the graph in adjacency list
    deleteGraphIM(graphIM, false); //delete the graph in incidence matrix
}