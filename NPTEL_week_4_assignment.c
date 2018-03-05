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

void Djikstras(struct Graph* G,int s,int* visited,int* distance,int** weight){
    
        int i,j;
        for(i=0;i<=G->V;i++){
            visited[i] = 0;
            distance[i] = 9999;
        }
        
        distance[s] = 0;
        struct Node* temp = NULL;
        
        int min_index = s;
    
        for(i=1;i<=G->V;i++){
            int min = 9999;
            for(j=1;j<=G->V;j++){
                if(visited[j]==0 && distance[j] < min){
                     min = distance[j];
                     min_index = j;
                }
            }
            //printf("\nMin_index = %d",min_index);
    
            visited[min_index] = 1;
            temp = G->array[min_index].head;
            while(temp!=NULL){
                
                if(visited[temp->data] == 0 && distance[temp->data] > distance[min_index] + weight[temp->data][min_index]){
                    distance[temp->data] = distance[min_index] + weight[temp->data][min_index];
                    //printf("\ndistance[%d]  = %d",temp->data,distance[temp->data] );
                }
                temp = temp->next;
            }
        }
    }



int main(){

    int M;
    int A;
    int B;
    scanf("%d %d %d",&M,&A,&B);
    
    int N1[M];
    int N2[M];
    int W[M];

    int i=0;
    int n1;
    int n2;
    int w;
    while(i<M){
        scanf("%d %d %d",&N1[i],&W[i],&N2[i]);
        
        ++i;
    }

    int max1 = 0;
    int max2 = 0;
    for(int i=0;i<M;i++){
        if(N1[i] > max1){
            max1 = N1[i];
        }
    }

    for(int i=0;i<M;i++){
        if(N2[i] > max2){
            max2 = N2[i];
        }
    }

    int V;
    if(max1 >= max2){
        V = max1;
    }
    else{
        V = max2;
    }

    //printf("\nNum vertices = %d",V);

    struct Graph* graph = createGraph(V);

    int** weight = (int**)malloc( (V+1)*sizeof(int*));
    for(int i=0;i<=graph->V;i++){
        weight[i] = (int*)malloc((V+1)*sizeof(int));
    }

    for(int i=0;i<=V;i++){
        for(int j=0;j<=V;j++){
            weight[i][j] = 9999;
        }
    }

    

    for(int i=0;i<M;i++){
        addEdge(graph,N1[i],N2[i],weight,W[i]);
        //printf("\nWeight[%d] = %d",i,W[i]);
    }

    
    //printGraph(graph);

    /*
    for(int i=0;i<=V;i++){
        for(int j=0;j<=V;j++){
            printf("\nweight[%d][%d] = %d",i,j,weight[i][j]);
        }
    }
    */
    int* visited = (int*)malloc( (V+1) * sizeof(int));
    int* distance = (int*)malloc( (V+1) * sizeof(int));

    Djikstras(graph,A,visited,distance,weight);

    /*
    for(int i=1;i<=graph->V;i++){
        printf("\ndistance[%d] = %d",i,distance[i]);
    }
    */
    //printf("\ndistance[%d] = %d",B,distance[B]);
    if(distance[B] != 9999){
        printf("\nYES\n");
        printf("%d",distance[B]);
    }

    else{
        printf("\nNO\n");
    }

    return 0;

}
