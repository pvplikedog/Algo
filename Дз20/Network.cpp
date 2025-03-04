#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

// Not working if has multiple edges(why should we need it?).
class Network {
   public:
    Network(int max_vertex) : max_vertex(max_vertex) {
        adj.resize(max_vertex + 1);
    }

    void add_edge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, 0);  // Doing so we can make flow work correctly.
    }

    // Dinic algo.
    int find_max_flow(int s, int t) {
        // flow.clear(); use if map
        flow = std::vector<std::vector<int>>(
            adj.size(), std::vector<int>(adj.size(), 0));  // use if vector
        int maxFlow = 0;
        while (bfs(s, t)) {
            cur_edge = std::vector<int>(adj.size(), 0);
            int addflow = dfs(s, (int)1e9, t);
            while (addflow != 0) {
                maxFlow += addflow;
                addflow = dfs(s, (int)1e9, t);
            }
        }
        return maxFlow;
    }

   private:
    int max_vertex;
    std::vector<std::vector<std::pair<int, int>>> adj;

    // All this needed for Dinic:
    std::vector<int> dist;
    // std::map<std::pair<int, int>, int> flow;  // Use if n is big(slower).
    std::vector<std::vector<int>> flow;  // Use if n is not so big(faster).
    std::vector<int> cur_edge;

    bool bfs(int s, int t) {
        dist = std::vector<int>(adj.size(), (int)1e9);
        dist[s] = 0;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto p : adj[u]) {
                if (dist[p.first] == (int)1e9 &&
                    (p.second - flow[u][p.first] > 0)) {
                    dist[p.first] = dist[u] + 1;
                    q.push(p.first);
                }
            }
        }
        return dist[t] != (int)1e9;
    }

    int dfs(int u, int minC, int t) {
        if (u == t || minC == 0) return minC;
        while (cur_edge[u] < adj[u].size()) {
            int v = adj[u][cur_edge[u]].first;
            if (dist[v] == dist[u] + 1) {
                int delta = dfs(
                    v, std::min(minC, adj[u][cur_edge[u]].second - flow[u][v]),
                    t);
                if (delta != 0) {
                    flow[u][v] += delta;
                    flow[v][u] -= delta;
                    return delta;
                }
            }
            cur_edge[u]++;
        }
        return 0;
    }
};

signed main() {
    // Tests from task P1 set7:

    // Test1:
    // 4 5
    // 1 2 2
    // 1 3 1
    // 2 4 2
    // 2 3 1
    // 3 4 1

    Network network1(4);
    network1.add_edge(1, 2, 2);
    network1.add_edge(1, 3, 1);
    network1.add_edge(2, 4, 2);
    network1.add_edge(2, 3, 1);
    network1.add_edge(3, 4, 1);

    // MaxFlow should be 3:
    assert(network1.find_max_flow(1, 4) == 3);
    std::cout << "Test1 passed\n";

    // Test2:
    // 4 5
    // 1 2 2
    // 1 3 1
    // 2 4 1
    // 2 3 1
    // 3 4 1

    Network network2(4);
    network2.add_edge(1, 2, 2);
    network2.add_edge(1, 3, 1);
    network2.add_edge(2, 4, 1);
    network2.add_edge(2, 3, 1);
    network2.add_edge(3, 4, 1);

    // MaxFlow should be 3:
    assert(network2.find_max_flow(1, 4) == 2);
    std::cout << "Test2 passed\n";

    return 0;
}