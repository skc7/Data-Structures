#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<queue>
#include<stack>
using namespace std;

struct Node{
    int dest;
    struct Node* next;
};

struct List{
    struct Node* head;
};

struct Graph{
    int V;
    struct List* array;
};

struct Node* new_node(int dest){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->dest = dest;
    return newNode; 
}

struct Graph* createGraph(int V){
    struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
    G->V = V;
    G->array = (struct List*)malloc(V*sizeof(struct List));

    for(int i=0;i<G->V;i++){
        G->array[i].head = NULL;
    }
    return G;
}

void addEdge(struct Graph* G, int src, int dest){
    struct Node* newNode = new_node(dest);
    newNode->next = G->array[src].head;
    G->array[src].head = newNode;

    newNode = new_node(src);
    newNode->next = G->array[dest].head;
    G->array[dest].head = newNode;

}

void addEdge_DAG(struct Graph* G, int src, int dest){
    struct Node* newNode = new_node(dest);
    newNode->next = G->array[src].head;
    G->array[src].head = newNode;

    //newNode = new_node(src);
    //newNode->next = G->array[dest].head;
    //G->array[dest].head = newNode;

}

void printGraph(struct Graph* G){
    
    for(int i=0;i<G->V;i++){
        struct Node* pCrawl = G->array[i].head;
        printf("\nAdj list of vertex %d ",i);
        while(pCrawl){
            printf(" %d",pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }


}

void BFS(struct Graph* G,int s){
    bool *visited = (bool*)malloc(G->V * sizeof(bool));
    int *parent = (int*)malloc(G->V * sizeof(int));
    //int *level = (int*)malloc(G->V * sizeof(int));
    for(int i=0; i< G->V; i++){
        visited[i] = false;
        parent[i] = -1;
        //level[i] = -1;
    }
    queue<int> Q;
    visited[s] = true;
    //level[s] = 0;
    Q.push(s);

    struct Node* temp = NULL;

    while(!Q.empty()){
        s = Q.front();
        printf(" %d",s);
        temp = G->array[s].head;
        Q.pop();
        while(temp != NULL){
            if(!visited[temp->dest]){
                visited[temp->dest] = true;
                parent[temp->dest] = s;
                //printf("\nParent of %d is %d",temp->dest,s);
                Q.push(temp->dest);
            }
            temp = temp->next;
        }
    }
}


void DFS(struct Graph* G,int s){

    bool* visited = (bool*)malloc(G->V * sizeof(bool));
    for(int i=0; i<G->V;i++){
        visited[i] = false;
    }

    stack<int> stk;
    stk.push(s);
    visited[s] = true;
    struct Node* temp = NULL;

    while(!stk.empty()){
        s = stk.top();
        printf(" %d",s);
        temp = G->array[s].head;
        stk.pop();

        while(temp != NULL){
            if(!visited[temp->dest]){
                visited[temp->dest] = true;
                stk.push(temp->dest);
            }
            temp = temp->next;
        }

    }
}


int DFS_util(struct Graph* G,int s,bool* visited,int* pre,int* post){
    static int count = 0;
    visited[s] = true;
    pre[s] = count;
    //printf("\npre[%d] = %d",s,pre[s]);
    ++count;
    printf(" %d",s);
    struct Node* temp = G->array[s].head;

    while(temp != NULL){
        if(!visited[temp->dest]){
            DFS_util(G,temp->dest,visited,pre,post);
            
            post[temp->dest] = count;
            ++count; 
            //printf("\npost[%d] = %d",temp->dest,post[temp->dest]);
            
        }
        
        temp = temp->next;
    }
    
    return count;
}
 
void DFS_rec(struct Graph* G,int s){
    bool* visited = (bool*)malloc(G->V * sizeof(bool));
    int* pre = (int*)malloc(G->V * sizeof(int));
    int* post = (int*)malloc(G->V * sizeof(int));
    
    for(int i=0; i<G->V;i++){
        visited[i] = false;
        pre[i] = 0;
        post[i] = 0;
    }

    
    post[s] = DFS_util(G,s,visited,pre,post);

    for(int i=0; i<G->V;i++){
        
        printf("\npre[%d] = %d",i,pre[i]);
        printf("\npost[%d] = %d",i,post[i]);
        
    }


}

int max(int a,int b){
    if(a>b)
        return a;
    else 
        return b;
}

void TopologicalSort(struct Graph* G){
    int* indegree = (int*)malloc(G->V * sizeof(int));
    int* LPT = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        indegree[i] = 0;
        LPT[i] = 0;
    }
    struct Node* temp = NULL;
    for(int i=0;i<G->V;i++){
        temp = G->array[i].head;
        
        while(temp != NULL){
            
            if(temp->dest){
                indegree[temp->dest] = 1 + indegree[temp->dest];
                temp = temp->next;
            }
        }
    }

    for(int i=0;i<G->V;i++){
        
        printf("\nindegree[%d] = %d",i,indegree[i]);
    }

    queue<int> Q;

    for(int i=0; i<G->V;i++){
        if(indegree[i] == 0){
            Q.push(i);
        }
    }

    while(!Q.empty()){
        int s = Q.front();
        Q.pop();
        indegree[s] = -1;
        printf("\n %d",s);
        temp = G->array[s].head;
        while(temp != NULL){

            indegree[temp->dest] = indegree[temp->dest] - 1;
            LPT[temp->dest] = max(LPT[temp->dest],1+LPT[s]);
            if(indegree[temp->dest] == 0){
                Q.push(temp->dest);
            }
            temp = temp->next;
        }

    }

/*
    for(int i=0;i<G->V;i++){
        
        printf("\nLPT[%d] = %d",i,LPT[i]);
    }
*/  


}

void DFS_iter(struct Graph* G,int* visited,int* comp,int count,int s){
    
    struct Node* stk = NULL;

    push(&stk,s);
    visited[s] = 1;
    comp[s] = count;
    struct Node* temp = NULL;

    while(!isEmpty(stk)){
        s = front(stk);
              
        //temp = G->array[s].head;
        
        
        for(temp = G->array[s].head;temp!=NULL;temp=temp->next){
            if(!visited[temp->dest]){
                visited[temp->dest] = 1;
                comp[temp->dest] = count;
                push(&stk,temp->dest);
                
                break;
            }
        }
                

        if(temp == NULL){
            pop(&stk);
        }   

    }
}



int main(){

    struct Graph* graph = createGraph(5);
    addEdge_DAG(graph,0,1);
    addEdge_DAG(graph, 0, 4);
    addEdge_DAG(graph, 1, 2);
    addEdge_DAG(graph, 1, 3);
    addEdge_DAG(graph, 1, 4);
    addEdge_DAG(graph, 2, 3);
    addEdge_DAG(graph, 3, 4);
    printGraph(graph);

    //BFS(graph,0);
    //DFS_rec(graph,0);
    TopologicalSort(graph);

    return 0;
}
