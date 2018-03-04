#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct List{
    struct Node* head;
};

struct Graph{
    int V;
    struct List* array; 
};


struct Graph* createGraph(int V){
    struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
    G->V = V;
    G->array = (struct List*)malloc((V+1)*sizeof(struct List));

    for(int i=0;i<=G->V;i++){
        G->array[i].head = NULL;
    }

    return G;
}

void addEdge(struct Graph* G,int u,int v,int** weight, int w){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = G->array[u].head;
    G->array[u].head = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = u;
    newNode->next = G->array[v].head;
    G->array[v].head = newNode;

    weight[u][v] = w;
    weight[v][u] = w;

}

void printGraph(struct Graph* G){
    
    for(int i=1;i<=G->V;i++){
        struct Node* pCrawl = G->array[i].head;
        printf("\nAdjList of %d = ",i);
        while(pCrawl != NULL){
            printf("%d ",pCrawl->data);
            pCrawl = pCrawl->next;
        }
    }
    

}

void DeleteGraph(struct Graph** G){
    
      for(int del=0;del<=(*G)->V;del++){
        struct Node* temp = (*G)->array[del].head;
        while(temp != NULL){
          free(temp);
          temp = temp->next;
        }
      }
    free(*G);
    return;
}

void prims(struct Graph* G,int* visited,int** weight,int* Dist_TV,int* Nbr_TV,int** TE){
    
    
    int min_index;

    visited[1] = 1;
    struct Node* temp = NULL;
    for(temp = G->array[1].head;temp!=NULL;temp=temp->next){
        Nbr_TV[temp->data] = 1;
        Dist_TV[temp->data] = weight[1][temp->data];
        //printf("\nDist_TV[%d] = %d",temp->data,Dist_TV[temp->data]);
    }

    for(int i=2;i<=G->V;i++){
        int min = 9999;
        for(int j=1;j<=G->V;j++){
            if(visited[j] == 0 && Dist_TV[j] < min){
                 min = Dist_TV[j];
                 min_index = j;
                 
            }
        }
        printf("\nmin_index = %d",min_index);

        visited[min_index] = 1;
        TE[min_index][0] = min_index;
        TE[min_index][1] = Nbr_TV[min_index];

        for(temp = G->array[min_index].head;temp != NULL; temp=temp->next){
            
            if(visited[temp->data] == 0 && Dist_TV[temp->data] > weight[min_index][temp->data]){
                Dist_TV[temp->data] = weight[min_index][temp->data];
                Nbr_TV[temp->data] = min_index;
            }
            
        }

    }


}

void kruskals(struct Graph* G){

}

int main(){
    int V=7;
    struct Graph* graph = createGraph(V);
    int** weight = (int**)malloc( (V+1)*sizeof(int*));
    for(int i=0;i<=graph->V;i++){
        weight[i] = (int*)malloc((V+1)*sizeof(int));
    }

    for(int i=0;i<=V;i++){
        for(int j=0;j<=V;j++){
            weight[i][j] = 0;
        }
    }

    addEdge(graph,1,2,weight,10);
    addEdge(graph,1,3,weight,3);
    addEdge(graph,2,3,weight,6);
    addEdge(graph,3,4,weight,70);
    addEdge(graph,2,5,weight,20);
    addEdge(graph,5,6,weight,10);
    addEdge(graph,5,7,weight,10);
    addEdge(graph,6,7,weight,5);

    

    printGraph(graph);
/*
    for(int i=1;i<=graph->V;i++){
        for(int j=1;j<=graph->V;j++){
            printf("\nweight[%d][%d] = %d",i,j,weight[i][j]);
        }
    }
*/


    int* visited = (int*)malloc((V+1)*sizeof(int));
    int* Dist_TV = (int*)malloc((V+1)*sizeof(int));
    int* Nbr_TV = (int*)malloc((V+1)*sizeof(int));
    int** TE = (int**)malloc((2)*sizeof(int*));
    for(int i=0;i<=V;i++){
        TE[i] = (int*)malloc((V+1)*sizeof(int));
    }

    for(int i=0;i<=V;i++){
        visited[i] = 0;
        Dist_TV[i] = 9999;
        Nbr_TV[i] = -1;
        for(int j=0;j<2;j++){
            TE[i][j] = -1;
        }

    }

    prims(graph,visited,weight,Dist_TV,Nbr_TV,TE);



    for(int i=1;i<=graph->V;i++){
        printf("\n");
        for(int j=0;j<2;j++){
            printf("TE[%d][%d] = %d ",i,j,TE[i][j]);
        }
        
    }


    DeleteGraph(&graph);


}
