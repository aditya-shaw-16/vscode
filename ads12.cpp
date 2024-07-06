#include <iostream>
#include <list>
#include <vector>

using namespace std;
class Graph{
    int V;
    list<int> *adj;
    void DFS(int v, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<bool> &ap);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void findCutVertices();
};
Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
}
void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
    adj[w].push_back(v); // Since it's an undirected graph
}
void Graph::DFS(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<bool> &ap){
    static int time = 0;
    int children = 0;

    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (auto v : adj[u]){
        if (!visited[v]){
            children++;
            parent[v] = u;
            DFS(v, visited, disc, low, parent, ap);
            low[u] = min(low[u], low[v]);
            if (low[v] >= disc[u] && parent[u] != -1)
                ap[u] = true;
            if (parent[u] == -1 && children > 1)
                ap[u] = true;
        }
        else if (v != parent[u]){
            low[u] = min(low[u], disc[v]);
        }
    }
}

void Graph::findCutVertices(){
    vector<bool> visited(V, false);
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<bool> ap(V, false);

    for (int i = 0; i < V; i++){
        if (!visited[i]){
            DFS(i, visited, disc, low, parent, ap);
        }
    }

    cout << "Cut Vertices: ";
    for (int i = 0; i < V; i++){
        if (ap[i]){
            cout << i << " ";
        }
    }
    cout << endl;
}
int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.findCutVertices();
    return 0;
}
