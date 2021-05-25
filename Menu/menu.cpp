#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "../Dijkstra/dijkstra.cpp"
#include "../Bellman-Ford/bellmanFord.cpp"
#include "../Prim/prim.cpp"
#include "../Kruskal/kruskal.cpp"
using namespace std;

//Graphs declarations
GraphAL *graphAL = new GraphAL();
GraphIM *graphIM = new GraphIM();

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
        do{
            edge.vertexStart = rand()%v;
            edge.vertexEnd = rand()%v;
        }while((edge.vertexStart == edge.vertexEnd) || (set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd)));
        
        edge.weight = rand()%edges;
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

    for(int i = 0; i < edges - currentEdges; i++){
        do{
            edge.vertexStart = rand()%v;
            edge.vertexEnd = rand()%v;
        }while((edge.vertexStart == edge.vertexEnd) || (*graphIM)->checkIfEdgeExists(edge.vertexStart, edge.vertexEnd));

        edge.weight = rand()%edges;
        if(!directed){
            (*graphAL)->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            (*graphIM)->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        else{
            (*graphAL)->addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            (*graphIM)->addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
    }
}

int askForStartingVertex(){
    if(graphAL->getNumOfVertexes() == 0){
        return -1;
    }

    int src;

    do{
        cout<<" Enter starting vertex: ";
        cin>>src;
    }while(src < 0 || src >= graphAL->getNumOfVertexes());

    return src;
}

void testMenu(){
    do{
        system("cls");
        cout<<" ___________TESTING___________"<<endl;
        cout<<" [1] Fill graph from the file"<<endl;
        cout<<" [2] Fill graph with random data"<<endl;
        cout<<" [3] Print graph"<<endl;
        cout<<" [4] Dijkstra's algorithm"<<endl;
        cout<<" [5] Bellman-Ford algorithm"<<endl;
        cout<<" [6] Prim's algorithm"<<endl;
        cout<<" [7] Kruskal's algorithm"<<endl;
        cout<<" [8] Delete graph"<<endl;
        cout<<" [9] Exit"<<endl;
        cout<<" Enter your choice: ";
        int choice, direction, src, vertexes;
        float density;
        cin>>choice;

        switch(choice){
            case 1: 
                if(graphAL->getNumOfVertexes() != 0){
                    cout<<" Graph is not empty!"<<endl;
                    break;
                }

                do{
                    cout<<" Undirected [0] or directed [1] graph? ";
                    cin>>direction;
                }while(direction != 0 && direction != 1);
                
                graphAL->fillGraphFromFile(direction); // false - undirected graph, true - directed
                graphIM->fillGraphFromFile(direction); // false - undirected graph, true - directed
                break;
            case 2: 
                do{
                    cout<<" Enter number of vertices: ";
                    cin>>vertexes;
                }while(vertexes <= 0 || vertexes > 1000);

                do{
                    cout<<" Enter density [%]: ";
                    cin>>density;
                }while(density < 0 || density > 100);

                do{
                    cout<<" Undirected [0] or directed [1] graph? ";
                    cin>>direction;
                }while(direction != 0 && direction != 1);

                generateGraph(&graphAL, &graphIM, vertexes, density, direction);
                break;
            case 3: 
                graphAL->printGraph();
                graphIM->printGraph();
                break;
            case 4: 
                src = askForStartingVertex();
                if(src == -1){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                dijkstraAL(graphAL, src);
                dijkstraIM(graphIM, src);
                break;
            case 5: 
                src = askForStartingVertex();
                if(src == -1){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                bellmanFordAL(graphAL, src);
                bellmanFordIM(graphIM, src);
                break;
            case 6: 
                src = askForStartingVertex();
                if(src == -1){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                primAL(graphAL, src);
                primIM(graphIM, src);
                break;
            case 7: 
                if(graphAL->getNumOfVertexes() == 0){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                kruskalAL(graphAL);
                kruskalIM(graphIM);
                break;
            case 8: 
                if(graphAL->getNumOfVertexes() == 0){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                deleteGraphAL(&graphAL);
                deleteGraphIM(&graphIM);
                break;
            case 9:
                return;
                break;
            default:
                cout<<endl<<" Wrong choice"<<endl;
                break;
        }
        cout<<" Press any key to continue ";
        getch();
    }while(true);
}

void startingMenu(){
    cout<<" ___________MENU___________"<<endl;
    cout<<" [1] Test the algorithms"<<endl;
    cout<<" [2] Run the experiment"<<endl;
    cout<<" [3] Exit"<<endl;
    cout<<" Enter your choice: ";
    int choice;
    cin>>choice;

    switch(choice){
        case 1: 
            testMenu();
            break;
        case 2: 
            // experimentMenu();
            break;
        case 3: 
            return;
            break;
        default:
            cout<<endl<<" Wrong choice!"<<endl;
            break;
    }
}