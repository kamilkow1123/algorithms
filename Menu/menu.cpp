#include<iostream>
#include<conio.h>
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
        cout<<"Graph is empty!"<<endl;
        return;
    }

    delete *graphAL;
    *graphAL = new GraphAL();
    cout<<"Successfully deleted list!"<<endl;
}

void deleteGraphIM(GraphIM **graphIM){
    if((*graphIM)->getNumOfVertexes() == 0){
        cout<<"Graph is empty!"<<endl;
        return;
    }

    delete *graphIM;
    *graphIM = new GraphIM();
    cout<<"Successfully deleted matrix!"<<endl;
}

int askForStartingVertex(){
    if(graphAL->getNumOfVertexes() == 0){
        return -1;
    }

    int src;

    do{
        cout<<"Enter starting vertex: ";
        cin>>src;
    }while(src < 0 || src >= graphAL->getNumOfVertexes());

    return src;
}

void testMenu(){
    do{
        system("cls");
        cout<<"___________TESTING___________"<<endl;
        cout<<"[1] Fill graph from the file"<<endl;
        cout<<"[2] Fill graph with random data"<<endl;
        cout<<"[3] Print graph"<<endl;
        cout<<"[4] Dijkstra's algorithm"<<endl;
        cout<<"[5] Bellman-Ford algorithm"<<endl;
        cout<<"[6] Prim's algorithm"<<endl;
        cout<<"[7] Kruskal's algorithm"<<endl;
        cout<<"[8] Delete graph"<<endl;
        cout<<"[9] Exit"<<endl;
        cout<<"Enter your choice: ";
        int choice, direction, src;
        cin>>choice;

        switch(choice){
            case 1: 
                if(graphAL->getNumOfVertexes() != 0){
                    cout<<"Graph is not empty!"<<endl;
                    break;
                }

                do{
                    cout<<"Undirected [0] or directed [1] graph? ";
                    cin>>direction;
                }while(direction != 0 && direction != 1);
                
                graphAL->fillGraphFromFile(direction); // false - undirected graph, true - directed
                graphIM->fillGraphFromFile(direction); // false - undirected graph, true - directed
                break;
            case 2: 
                if(graphAL->getNumOfVertexes() != 0){
                    cout<<"Graph is not empty!"<<endl;
                    break;
                }
                
                break;
            case 3: 
                graphAL->printGraph();
                graphIM->printGraph();
                break;
            case 4: 
                src = askForStartingVertex();
                if(src == -1){
                    cout<<"Graph is empty!"<<endl;
                    break;
                }
                dijkstraAL(graphAL, src);
                dijkstraIM(graphIM, src);
                break;
            case 5: 
                src = askForStartingVertex();
                if(src == -1){
                    cout<<"Graph is empty!"<<endl;
                    break;
                }
                bellmanFordAL(graphAL, src);
                bellmanFordIM(graphIM, src);
                break;
            case 6: 
                src = askForStartingVertex();
                if(src == -1){
                    cout<<"Graph is empty!"<<endl;
                    break;
                }
                primAL(graphAL, src);
                primIM(graphIM, src);
                break;
            case 7: 
                if(graphAL->getNumOfVertexes() == 0){
                    cout<<"Graph is empty!"<<endl;
                    break;
                }
                kruskalAL(graphAL);
                kruskalIM(graphIM);
                break;
            case 8: 
                if(graphAL->getNumOfVertexes() == 0){
                    cout<<"Graph is empty!"<<endl;
                    break;
                }
                deleteGraphAL(&graphAL);
                deleteGraphIM(&graphIM);
                break;
            case 9:
                return;
                break;
            default:
                cout<<endl<<"Wrong choice"<<endl;
                break;
        }
        cout<<"Press any key to continue ";
        getch();
    }while(true);
}

void startingMenu(){
    cout<<"___________MENU___________"<<endl;
    cout<<"[1] Test the algorithms"<<endl;
    cout<<"[2] Run the experiment"<<endl;
    cout<<"[3] Exit"<<endl;
    cout<<"Enter your choice: ";
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
            cout<<endl<<"Wrong choice!"<<endl;
            break;
    }
}