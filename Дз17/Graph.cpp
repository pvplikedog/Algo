#include <iostream>
#include <vector>

class Graph {
   public:
    Graph(int max_vertex) : max_vertex(max_vertex) {
        adj.resize(max_vertex + 1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

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

   private:
    int max_vertex;
    std::vector<std::vector<int>> adj;

    void dfs(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << v << " ";

        for (int u : adj[v]) {
            if (!visited[u]) {
                dfs(u, visited);
            }
        }
    }
};

int main() {
    Graph g(5);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);
    g.add_edge(4, 5);

    /*
      1 -- 2
      |  / |
      | /  |
      3 -- 4
      |  /
      | /
      5
      */

    g.dfs(1);
    std::cout << g.is_eyler() << std::endl;

    g.add_edge(1, 4);

    /*
      1 -- 2
      | \/ |
      | /\ |
      3 -- 4
      |  /
      | /
      5
      */
    std::cout << g.is_eyler() << std::endl;
    return 0;
}