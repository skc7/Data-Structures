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

Node* new_node(int dest){
    Node* newNode = new Node;
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V){
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->array = new List[V];

    for(int v=0; v < graph->V; v++){
        graph->(*(array+v)->head) = NULL;
    }

    return graph;


}

void addEdge(Graph* graph, int src, int dest){

    struct Node* newNode = new_node(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = new_node(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph){
    int i;
    for(i=0; i < graph->V;i++){

        cout << "\n adjList of " << i;
        struct Node* pCrawl = graph->array[i].head;
        while(pCrawl){

            cout << " " << pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        
        
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