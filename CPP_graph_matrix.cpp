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

void addEdge(struct Graph* G, int u, int v,int** weight,int w){
    struct Graph* g = G;
    g->Adj[u][v] = 1;
    g->Adj[v][u] = 1;
    weight[src][dest] = w;
    //weight[dest][src] = w;
}

void printGraph(struct Graph* graph){

    for(int i = 0; i < graph->V; i++){
        for(int j = 0; j < graph->V; j++){
            cout << " " << graph->Adj[i][j];
        }
        cout << "\n";
    }
}

void Flyod_walsh(struct Graph* G,int** weight){
    int w[G->V][G->V][G->V];
    for(int i=0;i<G->V;i++){
        for(int j=0;j<G->V;j++){
            w[i][j][0] = 9999;
        }
    }

    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            w[i][j][0] = weight[i][j];
        }
    }

    for(int k=1;k<G->V;k++){
        w[i][j][k] = min(w[i][j][k-1], w[i][k][k-1] +w[k][j][k-1] );
    }

}

int main(){

    int V=5;
    struct Graph* graph = createGraph(V);

    int** weight = (int**)malloc(V * sizeof(int*));
    for(int i=0;i<V;i++){
        weight[i] = (int*)malloc(V * sizeof(int));
    }

    for(int i=0;i<G->V;i++){
        for(int j=0;j<G->V;j++){
            weight[i][j] = 9999;
        }
    }


    addEdge(graph,0,1,weight,1);
    addEdge(graph, 0, 4,weight,1);
    addEdge(graph, 1, 2,weight,1);
    addEdge(graph, 1, 3,weight,1);
    addEdge(graph, 1, 4,weight,1);
    addEdge(graph, 2, 3,weight,1);
    addEdge(graph, 3, 4,weight,1);
    printGraph(graph);
    return 0;



}
