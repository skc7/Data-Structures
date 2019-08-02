#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;


class Graph{
public:
    Graph(int V) : vertices_(V) {
        adj = new std::vector<int>[V];
    };

    void addEdge(int v, int w);

    void BFS(int s);

    void DFS_iter(int s);

    void DFS_rec(int s);

private:
    void DFS_util(int s, bool visited[]);
    int vertices_;
    std::vector<int> *adj;
};



void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
    //adj[w].push_back(v);
}

void Graph::BFS(int s){
    bool* visited = new bool[vertices_];
    for(int i = 0; i < vertices_; ++i){
        visited[i] = false;
    }

    visited[s] = true;
    queue<int> Q;
    Q.push(s);

    while(! Q.empty()){
        s = Q.front();
        cout << " " << s;

        Q.pop();

        for(auto a = adj[s].begin(); a != adj[s].end(); ++a){
            if( !visited[*a]){
                visited[*a] = true;
                Q.push(*a);
            }
        } 
    }
    return;
}

void Graph::DFS_iter(int s){
    bool* visited = new bool[vertices_];
    for(int i=0; i<vertices_; ++i){
        visited[i] = false;
    }
    stack<int> S;
    S.push(s);
    visited[s] = true;
    cout << " " << s;
    while( !S.empty()){
        int x = S.top();

        auto i = adj[x].begin();
        for(i = adj[x].begin(); i != adj[x].end(); ++i){
            if(!visited[*i]){
                cout << " " << *i; 
                S.push(*i);
                visited[*i] = true;
                break;
            }
        }

        if(i == adj[x].end()){
            S.pop();
        }
    }
    return;
}

void Graph::DFS_util(int s, bool visited[]){
    visited[s] = true;
    cout << " " << s;

    for(auto x = adj[s].begin(); x != adj[s].end(); ++x){
        if( visited[*x] == false){
            DFS_util(*x,visited);
        }
    }
}

void Graph::DFS_rec(int s){
    bool* visited = new bool[vertices_];
    for(int i=0; i<vertices_; ++i){
        visited[i] = false;
    }
    DFS_util(s,visited);
}

int main(){

    Graph G(4);
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,2);
    //G.addEdge(2,0);
    G.addEdge(2,3);
    //G.addEdge(3,3);
    G.DFS_iter(1);
    cout << "\n";
    
    G.DFS_rec(1);
    return 0;
}