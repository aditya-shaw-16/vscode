#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// Floyd-Warshall algorithm
void calculateShortestDistances(vector<vector<int>>& graph){
    int vertices = graph.size();
    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX && graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}
int main() {
    vector<vector<int>> graph = {
        {0, 5, INT_MAX, 10},
        {INT_MAX, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    calculateShortestDistances(graph);
    cout << "Shortest path distances:" << endl;
    for (const auto& row : graph) {
        for (int val : row) {
            if (val == INT_MAX)
                cout << "INF ";
            else
                cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}
