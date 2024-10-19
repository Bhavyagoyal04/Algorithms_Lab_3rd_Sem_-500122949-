#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>

typedef std::pair<int, int> iPair;

void dijkstra(const std::vector<std::vector<iPair>>& graph, int src) {
    int V = graph.size();
    std::vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < V; i++) {
        std::cout << "Distance from source to " << i << " is " << dist[i] << std::endl;
    }
}

struct Edge {
    int src, dest, weight;
};

void bellmanFord(const std::vector<Edge>& edges, int V, int src) {
    std::vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            std::cout << "Graph contains negative weight cycle" << std::endl;
            return;
        }
    }

    for (int i = 0; i < V; i++) {
        std::cout << "Distance from source to " << i << " is " << dist[i] << std::endl;
    }
}

int main() {
    int V = 5;

    std::vector<std::vector<iPair>> graph(V);
    graph[0].push_back({1, 10});
    graph[0].push_back({4, 5});
    graph[1].push_back({2, 1});
    graph[2].push_back({3, 4});
    graph[4].push_back({1, 3});
    graph[4].push_back({2, 9});
    graph[4].push_back({3, 2});

    std::vector<Edge> edges = {
        {0, 1, 10}, {0, 4, 5}, {1, 2, 1}, {2, 3, 4}, {4, 1, 3}, {4, 2, 9}, {4, 3, 2}
    };

    auto start = std::chrono::high_resolution_clock::now();
    dijkstra(graph, 0);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dijkstraTime = end - start;
    std::cout << "Dijkstra's Algorithm Execution Time: " << dijkstraTime.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    bellmanFord(edges, V, 0);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> bellmanFordTime = end - start;
    std::cout << "Bellman-Ford Algorithm Execution Time: " << bellmanFordTime.count() << " seconds" << std::endl;

    return 0;
}
