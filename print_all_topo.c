#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<stack>
#include<vector>


using namespace std;

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
    G->array = (struct List*)malloc(G->V * sizeof(struct List));
    for(int i=0;i<G->V;i++){
        G->array[i].head = NULL;
    }

    return G;
}

struct Node* new_node(int data){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void addEdge(struct Graph* G, int src,int dest){
    struct Node* N = new_node(dest);
    N->next = G->array[src].head;
    G->array[src].head = N;

    N = new_node(src);
    N->next = G->array[dest].head;
    G->array[dest].head = N;
}

void addEdge_DW(struct Graph* G, int src,int dest,int** W,int x){
    struct Node* N = new_node(dest);
    N->next = G->array[src].head;
    G->array[src].head = N;

    W[src][dest] = x;
}

void addEdge_D(struct Graph* G, int src,int dest){
    struct Node* N = new_node(dest);
    N->next = G->array[src].head;
    G->array[src].head = N;
    return;
    
}

void printGraph(struct Graph* G){
    struct Node* temp = NULL;

    for(int i=0;i<G->V;i++){
        cout << "\nAdj List of " << i << ": ";
        for(temp = G->array[i].head;temp != NULL;temp = temp->next){
            cout << temp->data << " ";
        }
    }
}

void BFS(struct Graph* G,int s){
    
    int* visited = (int* )malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }

    queue<int > Q;
    Q.push(s);
    visited[s] = 1;
    struct Node* temp = NULL;
    while(!Q.empty()){
        s = Q.front();
        cout << s << " ";
        Q.pop();
        for(temp = G->array[s].head;temp!=NULL;temp = temp->next){
            if( !visited[temp->data] ){
                visited[temp->data] = 1;
                Q.push(temp->data);
            }
        } 
    }

}

void DFS(struct Graph* G,int x,int* visited){
    //int* visited = (int*)malloc(G->V * sizeof(int));
    /*
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }
    */
    visited[x] = 1;
    cout << x << " ";
    stack<int > S;
    S.push(x);

    while(!S.empty()){
        struct Node* temp;
        x = S.top();
        for(temp = G->array[x].head;temp!=NULL;temp=temp->next){
            if(visited[temp->data] != 1){
                cout << temp->data << " ";
                visited[temp->data] = 1;
                S.push(temp->data);
                break;
            }
        }

        if(temp == NULL){
            S.pop();
        }
    }
   cout << "\n";

}

void DFS_util(struct Graph* G,int visited[],int s){
    visited[s] = 1;
    cout << s << " ";
    struct Node* temp;
    for(temp = G->array[s].head;temp!=NULL;temp=temp->next){
        if(!visited[temp->data]){
            DFS_util(G,visited,temp->data);
        }
    }

}


void DFS_rec(struct Graph* G,int x){
    int* visited = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }
    DFS_util(G,visited,x);
}

int max(int a,int b){
    return a>b?a:b;
}

void topological_sort(struct Graph* G){
    int* indegree = (int*)malloc(G->V * sizeof(int));
    int* LPT = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        indegree[i] = 0;
        LPT[i] = 0;
    }

    struct Node* temp = NULL;
    for(int i=0;i<G->V;i++){
        for(temp = G->array[i].head;temp!=NULL;temp = temp->next){
            ++indegree[temp->data];
        }
    }

    queue<int> Q;

    for(int i=0;i<G->V;i++){
        if(indegree[i] == 0) Q.push(i);
    }

    while(!Q.empty()){
        int s = Q.front();
        Q.pop();
        indegree[s] = -1;
        cout << s << " ";
        for(temp = G->array[s].head;temp!=NULL;temp=temp->next){
            --indegree[temp->data];
            LPT[temp->data] = max(LPT[temp->data] , 1 + LPT[s]);
            if(indegree[temp->data] == 0){
                Q.push(temp->data);
            }
        }


    }

    for(int i=0;i<G->V;i++){
        cout << "\nLPT to " << i << " = " << LPT[i];
    }

}

void fillOrder(struct Graph* G,int s,int* visited,stack<int> &stk){
    visited[s] = 1;
    struct Node* temp = NULL;
    for(temp=G->array[s].head;temp!=NULL;temp=temp->next){
        if(!visited[temp->data]){
            fillOrder(G,temp->data,visited,stk);
        }
    }
    stk.push(s);
}

struct Graph* rev_graph(struct Graph* G){
    struct Graph* G_r = createGraph(G->V);

    for(int i=0;i<G->V;i++){
        struct Node* temp = NULL;
        for(temp=G->array[i].head;temp!=NULL;temp=temp->next){
            addEdge_D(G_r,temp->data,i);
        }
    }

    return G_r;
}

void kosaraju(struct Graph* G){
    stack<int> stk;

    int* visited = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }

    for(int i=0;i<G->V;i++){
        if(!visited[i])
        fillOrder(G,i,visited,stk);
    }

    struct Graph* G_r = rev_graph(G);
    printGraph(G_r);
    cout << "\n";
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }

    while(!stk.empty()){
        int i = stk.top();
        stk.pop();
        if(!visited[i]){
            
            DFS(G_r,i,visited);
            
        }
    }
}
/*
void countpath_util(struct Graph* G,int s,int d,int * visited,int& pathCount){
    visited[s] = 1;
    if(s==d) ++pathCount;

    else{
        struct Node* temp = NULL;
        for(temp=G->array[s].head;temp!=NULL;temp=temp->next){
            if(!visited[temp->data]){
                countpath_util(G,temp->data,d,visited,pathCount);
            }
        }
    }

    visited[s] = false;
}

int countPaths(struct Graph* G,int s,int d){
    int* visited = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
    }

    int pathcount = 0;
    countpath_util(G,s,d,visited,pathCount);
    return pathcount;
}
*/

void topo_util(struct Graph* G,int* visited, int * indegree, vector<int> &V){
    bool flag = false;

    for(int i=0;i<G->V;i++){
        if(!visited[i] && indegree[i]==0){

            
            struct Node* temp = NULL;
            for(temp=G->array[i].head;temp!=NULL;temp=temp->next){
                --indegree[temp->data];
            }

            V.push_back(i);
            visited[i] = 1;
            topo_util(G,visited,indegree,V);

            visited[i] = 0;
            V.erase(V.end() - 1);
            for(temp=G->array[i].head;temp!=NULL;temp=temp->next){
                ++indegree[temp->data];
            }

            flag = true;

        }
    }

    if(!flag){
        for(int i=0;i<V.size();i++)
            cout << V[i] << " ";
        
        cout << "\n";
    }
}

void topo(struct Graph* G){
    int* visited = (int*)malloc(G->V * sizeof(int));
    int* indegree = (int*)malloc(G->V * sizeof(int));
    for(int i=0;i<G->V;i++){
        visited[i] = 0;
        indegree[i] = 0;
    }
    for(int i=0;i<G->V;i++){
        struct Node* temp = NULL;
        for(temp=G->array[i].head;temp!=NULL;temp=temp->next){
            ++indegree[temp->data];
        }
    }
    vector<int> V;

    topo_util(G,visited,indegree,V);
}

int main(){

    struct Graph* G = createGraph(3);

    int** W = (int**)malloc(G->V * sizeof(int*));
    for(int i=0;i<G->V;i++){
        W[i] = (int*)malloc(sizeof(int));
    }

    for(int i=0;i<G->V;i++){
        for(int j=0;j<G->V;j++){
            W[i][j] = 0;
        }
    }

    addEdge_D(G,0,1);
    addEdge_D(G,0,2);
    //addEdge_D(G,2,0);

    
    

    printGraph(G);
    cout << "\n";
    topo(G);

    return 0;
}
