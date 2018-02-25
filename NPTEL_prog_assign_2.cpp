#include<stdio.h>
#include<iostream>
#include<stdlib.h>
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

void printGraph(struct Graph* G){
    
    for(int i=1;i<=G->V;i++){
        struct Node* pCrawl = G->array[i].head;
        printf("\nAdj list of vertex %d ",i);
        while(pCrawl){
            printf(" %d",pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }


}

int BFS(struct Graph* G,bool* visited,int* comp,int count,int* Muse,int s){

    int m_add = 0;
    queue<int> Q;
    visited[s] = true;
    m_add = m_add + Muse[s];
    comp[s] = count;
    //level[s] = 0;
    Q.push(s);

    struct Node* temp = NULL;

    while(!Q.empty()){
        s = Q.front();
        
        //printf(" %d",s);
        temp = G->array[s].head;
        Q.pop();
        while(temp != NULL){
            if(!visited[temp->dest]){
                visited[temp->dest] = true;
                comp[temp->dest] = count;
                m_add = m_add + Muse[temp->dest];
                Q.push(temp->dest);
            }
            temp = temp->next;
        }
    }
    return m_add;
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



int main(){

    int N = -1;
    int M = -1;
    int K = -1;
    int u[M+1];
    int v[M+1];
    int Muse[N+1];


    scanf("%d %d %d",&N,&M,&K);

    struct Graph* graph = createGraph(N);

    for(int i=1;i<=M;i++){
        scanf("%d %d",&u[i],&v[i]);  
        addEdge(graph,u[i],v[i]);   
    }

    
    int a=1;
    char temp;
    while(temp != '\n'){
        scanf("%d%c",&Muse[a],&temp);
        ++a;
    }
/*
    for(int j=1;j<=M;j++){
        printf("\nMUSE[%d] = %d",j,Muse[j]);
    }
*/  

    bool visited[graph->V + 1];
    for(int k=1; k<= graph->V; k++){
        visited[k] = false;
    }

    int comp[graph->V + 1];
    for(int i=1; i<= graph->V; i++){
        comp[i] = -1;
    }



    //printGraph(graph);    


    int count = 0;

    //printf("\nm_add = %d",BFS(graph,visited,comp,count,Muse,1));

    //BFS(graph,visited,comp,count,Muse,1);

    
    for(int i=1; i<=graph->V;i++){
        if(visited[i] == false){
            ++count;
            BFS(graph,visited,comp,count,Muse,i);
            //printf("\n");
            
        }
    }
/*
    for(int j=1;j<=graph->V;j++){
        printf("\ncomp[%d] = %d",j,comp[j]);
    }
*/
    //printf("\ncount = %d",count);
    //int m_add[count];
    int* m_add = (int*)malloc( (count+1)*sizeof(int));
    m_add[0] = -1;
    for(int i=1;i<=count;i++){
        m_add[i] = 0;
        for(int j =1;j<=graph->V;j++){
            if(comp[j] == i){
                m_add[i] = m_add[i] + Muse[j];
            }
            
        }
    }

    InsertionSort(m_add,count+1);

    /*
    printf("\nInsertion sort = ");
    for(int i=0;i<=count;i++){
        printf(" %d",m_add[i]);
    }
*/
    int Nikhil = 1;
    int Lavanya = count;
    int output = 0;
    if(K > count){
        printf("-1\n");
        return 0;
    }
    
    else{
        int i = K;
        while(i != 0){
            if(Lavanya == Nikhil){
                output = output + m_add[Nikhil];
                i = i -1;
            }
    
            else{
                output = output + m_add[Lavanya] + m_add[Nikhil];
                ++Nikhil;
                --Lavanya;
                i = i -2;
            }
        }

        
    }

    printf("%d\n",output);










/*

    for(int i=1; i<= graph->V; i++){
        //printf("\nVisited[%d] = %d",i,visited[i]);
        printf("\ncomp[%d] = %d",i,comp[i]);
    }

    for(int i=1; i<= graph->V; i++){
        printf("\nVisited[%d] = %d",i,visited[i]);
        //printf("\ncomp[%d] = %d",i,comp[i]);
    }

*/



    return 0;
}
