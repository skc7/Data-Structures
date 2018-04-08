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


struct Node* newNode(int data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
}

struct Graph* createGraph(int V){
    struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
    G->V = V;
    G->array = (struct List*)malloc(V * sizeof(struct List));

    for(int i=0;i<V;i++){
        G->array[i].head = NULL;
    }
    return G;
}

void addEdge(struct Graph* G,int src,int dest){
    struct Node* new_node = newNode(dest);
    new_node->next = G->array[src].head;
    G->array[src].head = new_node;

    new_node = newNode(src);
    new_node->next = G->array[dest].head;
    G->array[dest].head = new_node;

}


void addEdge_DAG(struct Graph* G,int src,int dest){
    struct Node* new_node = newNode(dest);
    new_node->next = G->array[src].head;
    G->array[src].head = new_node;

}

void addEdge_DAG_W(struct Graph* G,int src,int dest,int ** W, int x){
    struct Node* new_node = newNode(dest);
    new_node->next = G->array[src].head;
    G->array[src].head = new_node;
    W[src][dest] = x;

    /*
    new_node = newNode(src);
    new_node->next = G->array[dest].head;
    G->array[dest].head = new_node;
    W[dest][src] = x;
    */
}

void printGraph(struct Graph* G){
    struct Node* temp = NULL;

    for(int i=0;i<G->V;i++){
        temp = G->array[i].head;
        printf("\nAdj list of node %d ",i);
        while(temp != NULL){
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

/*
int head=0;
int tail=0;
int Q[1000];

void enqueue(int x){
    Q[tail] = x;
    tail++;
}

int dequeue(){
    int x = Q[head];
    head++;
    return x;
}
*/


void enqueue(struct Node** head,int x){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = x;

    if(*head == NULL){
        new_node->next = *head;
        *head = new_node;
    }
    else{
        struct Node* temp = *head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = NULL;
    }
}

int dequeue(struct Node** head){
    int x = (*head)->data;
    *head = (*head)->next;
    return x;
}

int Q_front(struct Node** head){
    return (*head)->data;
}

int Q_empty(struct Node** head){
    if(*head == NULL){
        return 1;
    }

    else return 0;
}

void BFS(struct Graph* G,int start){
    //int visisted[G->V];
    int* visited = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }
    struct Node* Qhead = NULL;
    enqueue(&Qhead,start);
    visited[start] = 1;

    while(!Q_empty(&Qhead)){
        int x = Q_front(&Qhead);
        
        struct Node* temp = G->array[x].head;
        dequeue(&Qhead);
        printf("%d ",x);
        while(temp != NULL){
            if(visited[temp->data] != 1){
                visited[temp->data] = 1;
                enqueue(&Qhead,temp->data);
            }
            temp = temp->next;
        }
    }
}

void push(struct Node** head,int x){
    
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    //newNode->next = NULL;

    newNode->next = *head;
    *head = newNode;

    return;

}


int pop(struct Node** head){
    int x = (*head)->data;
    *head = (*head)->next;

    return x;
}

int stk_front(struct Node** head){
    return (*head)->data;
}

int S_empty(struct Node** head){
    if(*head == NULL){
        return 1;
    }

    else return 0;
}

void DFS(struct Graph* G,int start){
    int* visited = (int*)malloc(G->V * sizeof(int));
   
    int* pre = (int*)malloc(G->V * sizeof(int));
    int* post = (int*)malloc(G->V * sizeof(int));
    int count = 0;

    for(int i=0;i<G->V;i++){
        visited[i] = 0;
        pre[i] = 0;
        post[i] = 0;
    }

    struct Node* stk = NULL;
    struct Node* temp = NULL;
    push(&stk,start);
    visited[start] = 1;
    printf("%d ",start);

    pre[start] = count;
    count++;

    while(S_empty(&stk) != 1){
        int x = stk_front(&stk);
        

        for(temp = G->array[x].head; temp != NULL;temp = temp->next){
            if(visited[temp->data] != 1){
                visited[temp->data] = 1;
                push(&stk,temp->data);

                pre[temp->data] = count;
                count++;

                printf("%d ",temp->data);
                break;
            }
        }

        if(temp == NULL){
            

            int y = stk_front(&stk);
            post[y] = count;
            count++;

            pop(&stk); 

        }


    }



    for(int i=0;i<G->V;i++){
        
        printf("\npre[%d] = %d",i,pre[i]);
        printf("\npost[%d] = %d",i,post[i]);
    }

}

int max(int a ,int b){
    if(a >= b) return a;
    else return b;
}

int min(int a ,int b){
    if(a <= b) return a;
    else return b;
}

void topological_sort(struct Graph* G){
    int indegree[G->V];
    int LPT[G->V];

    for(int i=0;i<G->V;i++){
        indegree[i] = 0;
        LPT[i] = 0;
    }

    struct Node* temp = NULL;

    for(int i=0;i<G->V;i++){
        temp = G->array[i].head;
        while(temp!=NULL){
            ++indegree[temp->data];
            temp = temp->next;
        }
    }


    struct Node* Q = NULL;
    for(int i=0;i<G->V;i++){
        if(indegree[i] == 0){
            enqueue(&Q,i);
        }
    }

    while(Q_empty(&Q) != 1){
        int x = Q_front(&Q);
        indegree[x] = -1;
        dequeue(&Q);
        printf("%d ",x);
        for(temp=G->array[x].head;temp != NULL;temp = temp->next){
            --indegree[temp->data];
            LPT[temp->data] = max(LPT[temp->data],1+x);

            if(indegree[temp->data] == 0){
                enqueue(&Q,temp->data);
            }
        }
    }

    for(int i=0;i<G->V;i++){
        
        printf("\nLPT[%d] = %d",i,LPT[i]);
    }
}


void Djikstras(struct Graph* G,int ** weight,int s){
    int* visited = (int*)malloc(G->V * sizeof(int));
    int* distance = (int*)malloc(G->V * sizeof(int));

    for(int i=0;i<G->V;i++){
        visited[i] = 0;
        distance[i] = 1000000000;
    }

    
    int min_index = s;

    
    distance[s] = 0;
    struct Node* temp = NULL;

    for(int i=0;i<G->V;i++){
        int min = 1000000000;
        for(int j=0;j<G->V;j++){
            if(visited[j] == 0 && distance[j] < min){
                min = distance[j];
                min_index = j;
            }
        }

        visited[min_index] = 1;
        for(temp = G->array[min_index].head;temp != NULL;temp = temp->next){
            if(visited[temp->data] == 0 && distance[temp->data] > distance[min_index] + weight[min_index][temp->data]){
                distance[temp->data] = distance[min_index] + weight[min_index][temp->data];
            }
        }

        

    }


    for(int i=0;i<G->V;i++){
        printf("\ndistance[%d] = %d",i,distance[i]);
    }

    
}


void BellmanFord(struct Graph* G,int** weight,int s){
    
    int* distance = (int*)malloc(G->V * sizeof(int));

    for(int i=0;i<G->V;i++){
        distance[i] = 1000000000;
    }

    distance[s] = 0;

    for(int i=0;i<G->V;i++){
        for(int j=0;j<G->V;j++){
            struct Node* temp = NULL;

            for(temp = G->array[j].head;temp != NULL; temp = temp->next){
                distance[temp->data] = min(distance[temp->data] , distance[j] + weight[j][temp->data]);
            }
        }
    }

    for(int i=0;i<G->V;i++){
        printf("\ndistance[%d] = %d",i,distance[i]);
    }


}

void Prims(struct Graph* G,int** weight){

    int** TE = (int**)malloc(G->V * sizeof(int*));
    for(int i=0;i<G->V;i++){
        TE[i] = (int*)malloc(2 * sizeof(int));
    }


    int* visited = (int*)malloc(G->V * sizeof(int));
    int* Nbr_TV = (int*)malloc(G->V * sizeof(int));
    int* Dist_TV = (int*)malloc(G->V * sizeof(int));

    


    for(int i=0;i<G->V;i++){
        visited[i] = 0;
        Nbr_TV[i] = -1;
        Dist_TV[i] = 9999;
    }

    visited[0] = 1;
    struct Node* temp = NULL;
    for(temp=G->array[0].head;temp!=NULL;temp=temp->next){
        Nbr_TV[temp->data] = 0;
        Dist_TV[temp->data] = weight[0][temp->data];
    }
    int min_index;

    for(int i=1;i<G->V;i++){
        int min = 9999;
        for(int j=1;j<G->V;j++){
            if(visited[j] == 0 && Dist_TV[j] < min){
                min = Dist_TV[j];
                min_index = j;
            }
        }
    

        visited[min_index] = 1;
        TE[min_index][0] = min_index;
        TE[min_index][1] = Nbr_TV[min_index];

        for(temp=G->array[min_index].head;temp!=NULL;temp=temp->next){
            if(visited[temp->data] == 0 && Dist_TV[temp->data] > weight[min_index][temp->data]){
                Dist_TV[temp->data] = weight[min_index][temp->data];
                Nbr_TV[temp->data] = min_index;
            }
        }
    }

    for(int i=1;i<G->V;i++){
        printf("\nNbr_TV[%d] = %d with weight = %d",i,Nbr_TV[i],weight[Nbr_TV[i]][i] );
    }

}

int main(){

    struct Graph* G = createGraph(7);

    int** weight = (int**)malloc(G->V * sizeof(int*));
    for(int i=0;i<G->V;i++){
        weight[i] = (int*)malloc(G->V * sizeof(int));
    }

    
    addEdge_DAG_W(G,0,1,weight,10);
    addEdge_DAG_W(G,0,2,weight,18);
    addEdge_DAG_W(G,1,2,weight,6);
    addEdge_DAG_W(G,2,3,weight,70);
    addEdge_DAG_W(G,1,4,weight,20);
    addEdge_DAG_W(G,4,5,weight,10);
    addEdge_DAG_W(G,4,6,weight,10);
    addEdge_DAG_W(G,5,6,weight,5);
    

    printGraph(G);

    Prims(G,weight);

    

    return 0;
}
