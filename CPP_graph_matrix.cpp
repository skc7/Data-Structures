#include<iostream>
#include<stdio.h>
#include <cstdlib>
using namespace std;


struct Graph{
    int V;
    int **Adj; //for 2D matrix
};

struct Graph* createGraph(int V){
    int u,v;
    struct Graph* G = new Graph;
    G->V = V;
    G->Adj = (int **)malloc(V * sizeof(int *));
    for (int i=0; i<V; i++)
         G->Adj[i] = (int *)malloc(V * sizeof(int));



    for(u = 0; u < G->V; u++){
        for(v=0; v < G->V; v++){
            G->Adj[u][v] = 0;
        }
    }
    

    return G;
}

void addEdge(struct Graph* G, int u, int v){
    struct Graph* g = G;
    g->Adj[u][v] = 1;
    g->Adj[v][u] = 1;
}

void printGraph(struct Graph* graph){

    for(int i = 0; i < graph->V; i++){
        for(int j = 0; j < graph->V; j++){
            cout << " " << graph->Adj[i][j];
        }
        cout << "\n";
    }
}


int main(){

    int V=5;
    struct Graph* graph = createGraph(V);
    addEdge(graph,0,1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    printGraph(graph);
    return 0;



}