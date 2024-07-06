#include <iostream>
#include <vector>

class DisjointSets{
private:
    std::vector<int> parent;
    std::vector<int> rank;
public:
    DisjointSets(int n){
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    int find(int x){
        if (parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY){
            if (rank[rootX] < rank[rootY]){
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY]){
                parent[rootY] = rootX;
            }
            else{
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};
int main(){
    int n, m;
    std::cout << "Enter number of vertices: ";
    std::cin >> n;
    std::cout << "Enter number of edges: ";
    std::cin >> m;
    DisjointSets ds(n);
    bool cycleDetected = false;
    for (int i = 0; i < m; i++){
        int u, v;
        std::cout << "Enter vertices of edge " << i + 1 << " (u v): ";
        std::cin >> u >> v;
        if (ds.find(u) == ds.find(v)){
            cycleDetected = true;
            break;
        }
        else{
            ds.unionSets(u, v);
        }
    }
    if (cycleDetected){
        std::cout << "Graph contains a cycle.\n";
    }
    else{
        std::cout << "Graph doesn't contain a cycle.\n";
    }
    return 0;
}
