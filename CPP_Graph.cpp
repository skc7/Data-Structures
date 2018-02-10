#include<iostream>

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

    newNode =  new_Node(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
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
    return 0;
}

