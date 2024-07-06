#include <iostream>
#include <vector>
#define NODE 5
using namespace std;

int graph[NODE][NODE] = {{0, 1, 1, 1, 1},
                         {1, 0, 1, 0, 0},
                         {1, 1, 0, 0, 0},
                         {1, 0, 0, 0, 1},
                         {1, 0, 0, 1, 0}}; 
void traverse(int u, bool visited[]){
    visited[u] = true;
    for (int v = 0; v < NODE; v++){
        if (graph[u][v]){
            if (!visited[v])
                traverse(v, visited);
        }
    }
}
bool isConnected(){
    bool *vis = new bool[NODE];
    for (int u; u < NODE; u++){
        for (int i = 0; i < NODE; i++)
            vis[i] = false;N
        traverse(u, vis);
        for (int i = 0; i < NODE; i++){
            if (!vis[i]) 
                return false;
        }
    }
    return true;
}
int hasEulerianCircuit(){
    if (isConnected() == false) 
        return 0;
    vector<int> degree(NODE, 0);
    int oddDegree = 0;
    for (int i = 0; i < NODE; i++){
        for (int j = 0; j < NODE; j++){
            if (graph[i][j])
                degree[i]++; 
        }
        if (degree[i] % 2 != 0)
            oddDegree++;        
    }
    if (oddDegree == 0){
        return 1;
    }
    return 0;
}
int main(){
    if (hasEulerianCircuit()){
        cout << "The graph has Eulerian Circuit." << endl;
    }
    else{
        cout << "The graph has No Eulerian Circuit." << endl;
    }
}
