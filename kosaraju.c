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
    //printf("\n%d pushed to stk",x);
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

void DFS(struct Graph* G,int start,int* visited){
    //int* visited = (int*)malloc(G->V * sizeof(int));
   
    int* pre = (int*)malloc(G->V * sizeof(int));
    int* post = (int*)malloc(G->V * sizeof(int));
    int count = 0;

    for(int i=0;i<G->V;i++){
        //visited[i] = 0;
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

printf("\n");
/*
    for(int i=0;i<G->V;i++){
        
        printf("\npre[%d] = %d",i,pre[i]);
        printf("\npost[%d] = %d",i,post[i]);
    }
*/
}

void fillOrder(struct Graph* G,int s,int* visited,struct Node** stk){
    visited[s] = 1;
    struct Node* temp = NULL;
    for(temp=G->array[s].head;temp!=NULL;temp=temp->next){
        if(visited[temp->data] != 1){
            fillOrder(G,temp->data,visited,stk);
        }
    }
    push(stk,s);
    //printf("\n%d pushed to stk",s);
    return;
}

struct Graph* reverse_graph(struct Graph* G){
    struct Graph* G_rev = (struct Graph*)malloc(sizeof(struct Graph));
    G_rev->V = G->V;
    G_rev->array = (struct List*)malloc(G->V * sizeof(struct List));
    for(int i=0;i<G->V;i++){
        G_rev->array[i].head = NULL;
    }

    for(int i=0;i<G->V;i++){
        struct Node* temp = NULL;
        for(temp = G->array[i].head;temp != NULL;temp = temp->next){
            addEdge_DAG(G_rev,temp->data,i);
        }
    }

    return G_rev;

}

void kosaraju(struct Graph* G){
    struct Node* stk = NULL;
    int* visited = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }

    for(int i=0;i<G->V;i++){
        if(visited[i] != 1){
            fillOrder(G,i,visited,&stk);
        }
        
    }

    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }
    struct Graph* G_rev = reverse_graph(G);
    printGraph(G_rev);

    //printf("\nstack top = %d",stk_front(&stk));
    
    while(S_empty(&stk) != 1){
        //printf("\na ");
        int i = stk_front(&stk);
        pop(&stk);
        if(visited[i] != 1){
            DFS(G_rev,i,visited);
        }
    }
        
    
    



}



int main(){

    struct Graph* G = createGraph(7);

    int** weight = (int**)malloc(G->V * sizeof(int*));
    for(int i=0;i<G->V;i++){
        weight[i] = (int*)malloc(G->V * sizeof(int));
    }

    
    addEdge_DAG(G,0,1);
    addEdge_DAG(G,1,2);
    addEdge_DAG(G,2,3);
    addEdge_DAG(G,3,0);
    addEdge_DAG(G,2,4);
    addEdge_DAG(G,4,5);
    addEdge_DAG(G,5,6);
    addEdge_DAG(G,6,4);
    
    
    //struct Graph* G_rev = reverse_graph(G);
    printGraph(G);

    printf("\n");
    //printGraph(G_rev);

    //Prims(G,weight);

    kosaraju(G);

    return 0;
}
