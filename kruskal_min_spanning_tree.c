#include<stdio.h>
#include<stdlib.h>

struct Edge{
    int src;
    int dest;
    int weight;
};

struct Graph{
    int V,E;
    struct Edge* edge;
};

struct Graph* createGraph(int V,int E){
    struct Graph* G = (struct Graph*)malloc(sizeof(Graph));
    G->V = V;
    G->E = E;

    G->edge = (struct Edge*)malloc(E*sizeof(struct Edge));

    return G;
}



int find(int parent[],int i){
    if(parent[i] == -1){
        return i;
    }
    return find(parent,parent[i]);
}

void Union(int parent[],int x,int y){
    int xset = find(parent,x);
    int yset = find(parent,y);
    parent[xset] = yset;
}

int isCycle(struct Graph* G){
    int *parent = (int*)malloc(G->V * sizeof(int));

    for(int i=0;i<G->V;i++){
        parent[i] = -1;
    }

    for(int i=0;i<G->E;i++){
        int x = find(parent,G->edge[i].src);
        int y = find(parent,G->edge[i].dest);

        if(x==y){
            return 1;
        }
        Union(parent,x,y);
    }
    return 0;
}

void swap(struct Edge* a,int pos1, int pos2){
    struct Edge temp;
    temp.src = a[pos1].src;
    temp.dest = a[pos1].dest;
    temp.weight = a[pos1].weight;

    a[pos1].src = a[pos2].src;
    a[pos1].dest = a[pos2].dest;
    a[pos1].weight = a[pos2].weight;

    a[pos2].src = temp.src;
    a[pos2].dest = temp.dest;
    a[pos2].weight = temp.weight;
}

void InsertionSort(struct Edge* a,int len){
    
        for(int i=1;i<len;i++){
            int j = i;
            while(j >0 && a[j].weight < a[j-1].weight){
                swap(a,j,j-1);
                j = j-1;
            }
        }
    }

void kruskals(struct Graph* G,int** TE){
    struct Edge* rank = (struct Edge*)malloc(G->V * sizeof(struct Edge));
    for(int i=0;i<G->V;i++){
        rank[i].src = G->edge[i].src;
        rank[i].dest = G->edge[i].dest;
        rank[i].weight = G->edge[i].weight;
        
    }

    InsertionSort(rank,G->V);

    int *parent = (int*)malloc(G->V * sizeof(int));
    
    for(int i=0;i<G->V;i++){
        parent[i] = -1;
    }

    

    int TE_len = G->V - 1;
    int i = 0;
    int j = 0;
    
        for(int i=0;i<G->E;i++){
            if(find(parent,rank[i].src) != find(parent,rank[i].dest)){
                TE[j][0] = rank[i].src;
                TE[j][1] = rank[i].dest;
                ++j;
                for(int k=0;k<G->V;k++){
                    if(find(parent,k) == find(parent,rank[i].dest)){
                        Union(parent,k,rank[i].src);
                    }
                }
                
                if(j == TE_len-2){
                    break;
                }
                
            }
        }
    
}


int main(){

    int V=3,E=3;
    struct Graph* G = createGraph(V,E);
    G->edge[0].src = 0;
    G->edge[0].dest = 1;
    G->edge[0].weight = 1;

    G->edge[1].src = 1;
    G->edge[1].dest = 2;
    G->edge[1].weight = 10;

    G->edge[2].src = 0;
    G->edge[2].dest = 2;
    G->edge[2].weight = 5;

    int** TE = (int**)malloc((2)*sizeof(int*));
    for(int i=0;i<=V;i++){
        TE[i] = (int*)malloc((G->V - 1)*sizeof(int));
    }

    kruskals(G,TE);

    for(int i=0;i<=(G->V)-2;i++){
        printf("\n");
        for(int j=0;j<2;j++){
            printf("\nTE[%d][%d] = %d ",i,j,TE[i][j]);
        }
        
    }

    return 0;

}
