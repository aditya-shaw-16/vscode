#include <stdio.h>
#include <limits.h>
//code from amdurkar sanket shivanand(2k21/se/27)
#define MAX_NODES 100


int minDistance(int distances[], int visited[], int num_nodes) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < num_nodes; v++) {
        if (visited[v] == 0 && distances[v] <= min) {
            min = distances[v];
            min_index = v;
        }
    }

    return min_index;
}

// Dijkstra's algorithm function using 
void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int num_nodes, int distances[]) {
    int visited[MAX_NODES];   

    
    for (int i = 0; i < num_nodes; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    distances[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < num_nodes - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        // u is always equal to src in the first iteration.
        int u = minDistance(distances, visited, num_nodes);

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Update distance value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < num_nodes; v++) {
            // Update distance[v] only if it is not in visited, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of distance[v]
            if (!visited[v] && graph[u][v] && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
            }
        }
    }
}

// Function to print routing table for a node
void print_routing_table(int node_index, int distances[], int num_nodes) {
    printf("Routing table for Node %d:\n", node_index);
    for (int i = 0; i < num_nodes; i++) {
        if (i != node_index) {
            if (distances[i] != INT_MAX) {
                printf(" -> Node %d: Cost %d\n", i, distances[i]);
            } else {
                printf(" -> Node %d: Not Reachable\n", i);
            }
        }
    }
    printf("\n");
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Unable to open the file graph.txt\n");
        return 1;
    }

    int num_nodes;
    fscanf(file, "%d", &num_nodes);

    int graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < num_nodes; i++) {
    
        for (int j = 0; j < num_nodes; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    // Compute routing table for each node
    for (int i = 0; i < num_nodes; i++) {
        int distances[MAX_NODES];
        dijkstra(graph, i, num_nodes, distances);
        print_routing_table(i, distances, num_nodes);
    }

    return 0;
}


/* The graph.txt file is 
9  (number of nodes used)
(adjacency matrix for links and cost)
0 4 8 0 0 0 0 0 0
4 0 11 8 0 0 0 0 0
8 11 0 0 7 1 0 0 0
0 8 0 0 2 0 7 4 0
0 0 7 2 0 6 0 0 0
0 0 1 0 6 0 0 2 0
0 0 0 7 0 0 0 14 9
0 0 0 4 0 2 14 0 10
0 0 0 0 0 0 9 10 0



*/