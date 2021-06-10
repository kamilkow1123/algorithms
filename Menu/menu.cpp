#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "../Experiments/experiments.cpp"
using namespace std;

//Graphs declarations
GraphAL *graphAL = new GraphAL();
GraphIM *graphIM = new GraphIM();


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
        GraphAL *mstAL;
        GraphIM *mstIM;
        int **results;
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
                }while(vertexes <= 2 || vertexes > 1000);

                do{
                    cout<<" Enter density [%]: ";
                    cin>>density;
                }while(density < 0 || density > 100);

                do{
                    cout<<" Undirected [0] or directed [1] graph? ";
                    cin>>direction;
                }while(direction != 0 && direction != 1);

                generateGraph(&graphAL, &graphIM, vertexes, density, direction, true);
                break;
            case 3:
                if(graphAL->getNumOfVertexes() == 0){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                cout<<endl;
                graphAL->printGraph();
                graphIM->printGraph();
                break;
            case 4:
                if(direction == 0){
                    cout<<" Dijkstra's algorithm should be executed on directed graph!"<<endl;
                    break;
                }

                src = askForStartingVertex();
                if(src == -1){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }

                results = dijkstraAL(graphAL, src);
                cout<<endl<<" Results of the Dijkstra algorithm for adjacency list: "<<endl;
                cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
                for(int i=0; i < graphAL->getNumOfVertexes(); i++){
                    if(results[i][0] == -2) cout<<" "<<i<<"\t\t"<<"no path"<<"\t\t"<<"no path"<<endl;
                    else cout<<" "<<i<<"\t\t"<<results[i][0]<<"\t\t"<<results[i][1]<<endl;
                }

                results = dijkstraIM(graphIM, src);
                cout<<endl<<" Results of the Dijkstra algorithm for incidence matrix: "<<endl;
                cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
                for(int i=0; i < graphIM->getNumOfVertexes(); i++){
                    if(results[i][0] == -2) cout<<" "<<i<<"\t\t"<<"no path"<<"\t\t"<<"no path"<<endl;
                    else cout<<" "<<i<<"\t\t"<<results[i][0]<<"\t\t"<<results[i][1]<<endl;
                }
                cout<<endl;
                break;
            case 5:
                if(direction == 0){
                    cout<<" Bellman-Ford algorithm should be executed on directed graph!"<<endl;
                    break;
                }

                src = askForStartingVertex();
                if(src == -1){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }

                results = bellmanFordAL(graphAL, src);
                cout<<endl<<" Results of the Bellman-Ford algorithm for adjacency list: "<<endl;
                cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
                for(int i=0; i < graphAL->getNumOfVertexes(); i++){
                    if(results[i][0] == -2) cout<<" "<<i<<"\t\t"<<"no path"<<"\t\t"<<"no path"<<endl;
                    else cout<<" "<<i<<"\t\t"<<results[i][0]<<"\t\t"<<results[i][1]<<endl;
                }

                results = bellmanFordIM(graphIM, src);
                cout<<endl<<" Results of the Bellman-Ford algorithm for incidence matrix: "<<endl;
                cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
                for(int i=0; i < graphIM->getNumOfVertexes(); i++){
                    if(results[i][0] == -2) cout<<" "<<i<<"\t\t"<<"no path"<<"\t\t"<<"no path"<<endl;
                    else cout<<" "<<i<<"\t\t"<<results[i][0]<<"\t\t"<<results[i][1]<<endl;
                }
                cout<<endl;
                break;
            case 6:
                if(direction == 1){
                    cout<<" Prim's algorithm should be executed on undirected graph!"<<endl;
                    break;
                }

                src = askForStartingVertex();
                if(src == -1){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }

                mstAL = primAL(graphAL, src);
                mstIM = primIM(graphIM, src);
                cout<<endl<<" MST from Prim's algorithm in adjacency list:"<<endl;
                mstAL->printGraph();
                cout<<endl<<" MST from Prim's algorithm in incidence matrix:"<<endl;
                mstIM->printGraph();
                break;
            case 7:
                if(direction == 1){
                    cout<<" Kruskal's algorithm should be executed on undirected graph!"<<endl;
                    break;
                }

                if(graphAL->getNumOfVertexes() == 0){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }

                mstAL = kruskalAL(graphAL);
                mstIM = kruskalIM(graphIM);
                cout<<endl<<" MST from Kruskal's algorithm in adjacency list:"<<endl;
                mstAL->printGraph();
                cout<<endl<<" MST from Kruskal's algorithm in incidence matrix:"<<endl;
                mstIM->printGraph();
                break;
            case 8:
                if(graphAL->getNumOfVertexes() == 0){
                    cout<<" Graph is empty!"<<endl;
                    break;
                }
                deleteGraphAL(&graphAL, true);
                deleteGraphIM(&graphIM, true);
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

void experimentMenu(){
    do{
        system("cls");
        cout<<" ___________EXPERIMENT___________"<<endl;
        cout<<" [1] Dijkstra"<<endl;
        cout<<" [2] Bellman-Ford"<<endl;
        cout<<" [3] Prim"<<endl;
        cout<<" [4] Kruskal"<<endl;
        cout<<" [5] Exit"<<endl;
        cout<<" Enter your choice: ";
        int choice;
        cin>>choice;

        switch(choice){
            case 1:
                dijkstraExperiment(&graphAL, &graphIM);
                break;
            case 2:
                bellmanFordExperiment(&graphAL, &graphIM);
                break;
            case 3:
                primExperiment(&graphAL, &graphIM);
                break;
            case 4:
                kruskalExperiment(&graphAL, &graphIM);
                break;
            case 5:
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
            experimentMenu();
            break;
        case 3:
            return;
            break;
        default:
            cout<<endl<<" Wrong choice!"<<endl;
            break;
    }
}