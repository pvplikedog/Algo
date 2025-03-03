#include <iostream>
#include <queue>
#include <vector>

class Graph {
   public:
    Graph(int max_vertex) : max_vertex(max_vertex) {
        adj.resize(max_vertex + 1);
        path = std::vector<std::vector<int>>(
            max_vertex + 1, std::vector<int>(max_vertex + 1, 0));
    }

    void add_edge(int u, int v, int w) { adj[u].emplace_back(v, w); }

    void dfs(int v) {
        std::vector<bool> visited(max_vertex + 1, false);
        dfs(v, visited);
        std::cout << std::endl;
    }

    bool is_eyler() {
        int odd = 0;
        for (int i = 1; i <= max_vertex; i++) {
            if (adj[i].size() % 2) {
                odd++;
            }
        }
        return odd == 0 || odd == 2;
    }

    std::vector<std::vector<int>> path;

    int dijkstra(int start, int finish, bool is_astar = false) {
        int cnt = 0;  // number of vertex visited.
        std::vector<int> dist(max_vertex + 1, (int)1e9);
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>>
            pq;
        pq.push({0 + (is_astar ? path[start][finish] : 0), start});
        while (!pq.empty()) {
            auto [cur_d, v] = pq.top();
            pq.pop();
            if (dist[v] <= cur_d) continue;
            ++cnt;
            if (v == finish) return cnt;
            dist[v] = cur_d;
            for (auto e : adj[v]) {
                pq.push(
                    {cur_d + e.second + (is_astar ? path[e.first][finish] : 0),
                     e.first});
            }
        }
        return cnt;
    }

   private:
    int max_vertex;
    std::vector<std::vector<std::pair<int, int>>> adj;

    void dfs(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << v << " ";

        for (auto u : adj[v]) {
            if (!visited[u.second]) {
                dfs(u.second, visited);
            }
        }
    }
};

int main() {
    Graph graph(8);
    graph.add_edge(1, 2, 6);
    graph.add_edge(1, 3, 5);
    graph.add_edge(1, 4, 10);
    graph.add_edge(2, 5, 6);
    graph.add_edge(3, 5, 6);
    graph.add_edge(3, 6, 7);
    graph.add_edge(4, 6, 6);
    graph.add_edge(5, 7, 4);
    graph.add_edge(6, 7, 6);
    graph.add_edge(7, 8, 3);
    std::cout << graph.dijkstra(1, 8) << " - normal Dijkstra\n";
    graph.path[1][8] = 17;
    graph.path[2][8] = 10;
    graph.path[3][8] = 13;
    graph.path[4][8] = 4;
    graph.path[5][8] = 4;
    graph.path[6][8] = 2;
    graph.path[7][8] = 1;
    graph.path[8][8] = 0;
    std::cout << graph.dijkstra(1, 8, true) << " - A*\n";

    Graph graph2(100);
    for (int i = 1; i < 100; ++i) {
        graph2.add_edge(i, i + 1, 1);
        if (i + 2 <= 100) graph2.add_edge(i, i + 2, 2);
        if (i + 5 <= 100) graph2.add_edge(i, i + 5, 5);
    }

    std::cout << graph2.dijkstra(1, 100) << " - normal Dijkstra\n";
    for (int i = 1; i <= 100; ++i) {
        graph2.path[i][100] = 100 - i;
    }
    std::cout << graph2.dijkstra(1, 100, true) << " - A*\n";
    return 0;
}