#include<stdio.h>
#include<stdlib.h>

struct Node{
    int dest;
    Node* next;
};

struct List{
    struct Node* head;
};

struct Graph{
    int V;
    struct List* array;
};

struct Node* new_Node(int dest){
    Node* newNode = new Node;
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
};

struct Graph * createGraph(int V){

    struct Graph* graph = new Graph;
    graph->V = V;
    graph->array = new List[V];
    int i;
    for(i=0;i<V;i++){
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int** weight,int w){
    struct Node* newNode =  new_Node(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode =  new_Node(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;

    weight[src][dest] = w;
    weight[dest][src] = w;

}



void printGraph(struct Graph* graph){

    int v;
    for(v=0;v<graph->V;v++){
        struct Node* pCrawl = graph->array[v].head;
        printf("\nAdj list of vertex %d   ",v);
        while(pCrawl){
            printf("%d ",pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
        
    }
}



void Djikstras(struct Graph* G,int s,int* visited,int* distance,int** weight){

    int i,j;
    for(i=0;i<G->V;i++){
        visited[i] = 0;
        distance[i] = 9999;
    }

    distance[s] = 0;
    struct Node* temp = NULL;
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            if(visited[j]==false && distance[j] < 9999)
                break;
        }
        visited[j] = 1;
        temp = G->array[j].head;
        while(temp!=NULL){
            
            if(visited[temp->dest] == 0 && distance[temp->dest] > distance[j] + weight[temp->dest][j]){
                distance[temp->dest] = distance[j] + weight[temp->dest][j];
            }
            temp = temp->next;
        }
    }
}

int main(){

    int V=5;
    int** weight = (int**)malloc(V * sizeof(int*));
    for(int i=0;i<V;i++){
        weight[i] = (int*)malloc(V * sizeof(int));
    }




    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1,weight,1);
    addEdge(graph, 0, 4,weight,2);
    addEdge(graph, 1, 2,weight,3);
    addEdge(graph, 1, 3,weight,4);
    addEdge(graph, 1, 4,weight,5);
    addEdge(graph, 2, 3,weight,6);
    addEdge(graph, 3, 4,weight,7);
    printGraph(graph);

    int* visited = (int*)malloc(graph->V * sizeof(int));
    int* distance = (int*)malloc(graph->V * sizeof(int));

    Djikstras(graph,0,visited,distance,weight);

    for(int i=0;i<graph->V;i++){
        printf("\ndistance[%d] = %d",i,distance[i]);
    }
    
    return 0;
}