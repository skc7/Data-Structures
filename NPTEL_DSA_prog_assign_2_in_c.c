#include<stdio.h>
#include<stdlib.h>


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
    G->array = (struct List*)malloc((V+1)*sizeof(struct List));
   

    for(int i=0;i<=G->V;i++){
        G->array[i].head = NULL;
    }
    return G;
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



void addEdge(struct Graph* G, int src, int dest){
    struct Node* newNode = new_node(dest);
    newNode->next = G->array[src].head;
    G->array[src].head = newNode;

    newNode = new_node(src);
    newNode->next = G->array[dest].head;
    G->array[dest].head = newNode;

}

void printGraph(struct Graph* G){
    
    for(int i=1;i<=G->V;i++){
        struct Node* pCrawl = G->array[i].head;
        printf("\nAdj list of vertex %d ",i);
        
        while(pCrawl != NULL){
            printf(" %d",pCrawl->dest);
            
            pCrawl = pCrawl->next;
        }
        
        printf("\n");
    }


}

void DFS_rec(struct Graph* G,int* visited,int* comp,int count,int s){

    
    visited[s] = 1;
    comp[s] = count;
    
    //printf(" %d",s);
    struct Node* temp = G->array[s].head;

    while(temp != NULL){
        if(visited[temp->dest] != 1){
            //comp[temp->dest] = count;
            //visited[temp->dest] = 1;
            DFS_rec(G,visited,comp,count,temp->dest);            
            
        }
        
        temp = temp->next;
    }
    
    return;
}
 


void swap(int a[],int pos1, int pos2){
    int temp = 0;
    temp = a[pos1];
    a[pos1] = a[pos2];
    a[pos2] = temp;
}

void InsertionSort(int a[],int len){
    
        for(int i=1;i<len;i++){
            int j = i;
            while(j >0 && a[j] < a[j-1]){
                swap(a,j,j-1);
                j = j-1;
            }
        }
    }




void push(struct Node** root, int x){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = x;
    newNode->next = NULL;
    
    newNode->next = *root;
    *root = newNode;
    return;
    //cout << "\n" << x << " pushed to stack" << endl;
    
}
    
int pop(struct Node** root){
    
    struct Node* temp = *root;
 /*   
    if(isEmpty(temp) == 1){
        //cout << "\nstack underflow" << endl;
        return NULL;
    }
 */   
    *root = (*root)->next;
    int popped = temp->dest;
    free(temp);
    //cout << "\n" << popped << " popped out of stack" << endl;
    return popped;
    
}

int front(struct Node* root){
    return root->dest;
}

int isEmpty(struct Node* root){
    if(root == NULL){
        return 1;
    }
    else{
        return 0;
    }
}


void DFS_iter(struct Graph* G,int* visited,int* comp,int count,int s){
    
    struct Node* stk = NULL;
    visited[s] = 1;
    comp[s] = count;
    push(&stk,s);

    struct Node* temp = NULL;

    while(!isEmpty(stk)){
        s = front(stk);
        //cout << s << " ";        
        temp = G->array[s].head;
        pop(&stk);
        while(temp != NULL){
            if(!visited[temp->dest]){
                visited[temp->dest] = 1;
                comp[temp->dest] = count;
                push(&stk,temp->dest);
            }
            temp = temp->next;

        }
    }
  return;
}





int main(){

    int N = -1;
    int M = -1;
    int K = -1;

    int i = 0;
    int a=1;


    scanf("%d %d %d",&N,&M,&K);

    if(N == 0 || K == 0){
        printf("-1\n");
        return 0;
    }

    int u[M+1];
    int v[M+1];
    int Muse[N+1];
    char temp;
    u[0] = -1;
    v[0] = -1;


    for(i=1;i<=M;i++){
        scanf("%d %d",&u[i],&v[i]);  
    }

    while(temp != '\n'){
        scanf("%d%c",&Muse[a],&temp);
        ++a;
    }

    struct Graph* graph = createGraph(N);
    
    for(i=1;i<=M;i++){
        addEdge(graph,u[i],v[i]);   
    }

    //printGraph(graph);

    int visited[N + 1];
    visited[0] = -123;
    for(int k=1; k<= N; k++){
        visited[k] = 0;
    }
    
    int comp[N + 1];
    comp[0] = -123;
    for(i=1; i<= graph->V; i++){
        comp[i] = -1;
    }

    int count = 0;
    
     
    for(i=1; i<=graph->V;i++){
        //printf("\nvisited[%d] = %d",i,visited[i]);
        if(visited[i] == 0){
            ++count;
            DFS_iter(graph,visited,comp,count,i);
        }
    }

    int m_add[count+1];
    m_add[0] = -1;
    for(i=1;i<=count;i++){
        m_add[i] = 0;
        for(int j =1;j<=graph->V;j++){
            if(comp[j] == i){
                m_add[i] = m_add[i] + Muse[j];
            }
            
        }
    }

    InsertionSort(m_add,count+1);

    int Nikhil = 1;
    int Lavanya = count;
    int output = 0;
    if(K > count){
        printf("-1\n");
        DeleteGraph(&graph);
        return 0;
    }
    
    if(K < 0 || M <0 || N < 0){
      printf("-1\n");
      DeleteGraph(&graph);
      return 0;
    }
    else{
        i = K;
        while(i != 0){
            if(Lavanya == Nikhil || i == 1){
                output = output + m_add[Lavanya];
                i = i -1;
            }
    
            else{
                output = output + m_add[Lavanya] + m_add[Nikhil];
                ++Nikhil;
                --Lavanya;
                i = i - 2;
            }
        }

        
    }

    printf("%d\n",output);
    DeleteGraph(&graph);


    return 0;
}
