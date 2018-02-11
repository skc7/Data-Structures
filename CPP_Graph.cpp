#include<iostream>
#include <queue>
#include <stack>

using namespace std;

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

void addEdge(struct Graph* graph, int src, int dest){
    struct Node* newNode =  new_Node(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    //newNode =  new_Node(src);
    //newNode->next = graph->array[dest].head;
    //graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph){

    int v;
    for(v=0;v<graph->V;v++){
        struct Node* pCrawl = graph->array[v].head;
        cout << "\nAdj list of vertex " << v;
        while(pCrawl){
            cout << " " << pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        cout << "\n";
        
    }
}

void BFS(struct Graph* G, int s){
    bool *visited = new bool[G->V];
    for(int i=0; i < G->V; i++){
        visited[i] = false;
    }
    queue<int> Q;
    visited[s] = true;
    Q.push(s);

    struct Node* temp = NULL;

    while(!Q.empty()){
        s = Q.front();
        cout << s << " ";        
        temp = G->array[s].head;
        Q.pop();
        while(temp != NULL){
            if(!visited[temp->dest]){
                visited[temp->dest] = true;
                Q.push(temp->dest);
            }
            temp = temp->next;

        }
    }
}

void DFS(struct Graph* G, int s){
    bool* visited = new bool[G->V];
    for(int i=0; i<G->V;i++){
        visited[i] = false;
    }

    stack<int> stk;
    visited[s] = true;
    stk.push(s);

    struct Node* temp = NULL;

    while(!stk.empty()){
        s = stk.top();
        cout << " " << s;
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

void topologicalsort_util(struct Graph* G, int v, bool visited[], stack<int> &stk){

    visited[v] = true;
    struct Node* temp = G->array[v].head; 
    while(temp != NULL){
        cout << "\nIn TU while";
        if(!visited[temp->dest]){
            cout << "\nIn TU while if " << temp->dest;
            topologicalsort_util(G,temp->dest,visited,stk);
            
        }
        temp = temp->next;
        
    }
    cout << "\nIn TU while if stkpush " << v;
    stk.push(v);
}

void TopologicalSort(struct Graph* G){
    stack <int> stk;
    bool *visited = new bool[G->V];
    for(int i=0; i< G->V;i++){
        visited[i] = false;
    }

    for(int i=0; i<G->V; i++){
        if(visited[i] == false){
            cout << "\nIn T " << i; 
            topologicalsort_util(G,i,visited,stk);
        }
            
    }

    while(stk.empty() == false){
        cout << " " << stk.top();
        stk.pop();
    }


}


int main(){

    int V=5;
    struct Graph* graph = createGraph(V);
    addEdge(graph,0,1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    printGraph(graph);
    cout << "\nDFS = ";
    DFS(graph,0);

    cout << "\nBFS = ";
    BFS(graph,0);

    cout << "\ntopo: ";
    TopologicalSort(graph);


    return 0;
}
