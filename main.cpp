#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

class Graph {
  public:
    int E;
    int V;

    std::vector<int> L;

    std::map<int, std::vector<int>> adjacency_list;

    Graph() {};

    void initialise() {
        std::cin >> E >> V;

        for (int i = 0; i < E; i++) {
            int u, v;
            std::cin >> u >> v;

            adjacency_list[u].push_back(v);
            adjacency_list[v].push_back(u);
        }

        for (int &l : L) {
            std::cin >> l;
        }
    }
};

struct Edge {
    int u;
    int v;
};

struct EdgeDistance {
    int u;
    int v;
    int d;

    bool operator<(const EdgeDistance &other) {
        return d > other.d;
    }
};

std::vector<std::vector<int>> get_distances(const std::vector<int> &L, std::map<int, std::vector<int>> &adjacency_list, int E) {
    std::vector<std::vector<int>> D(E, std::vector<int>(E, -1));
    std::stack<int> S;

    for (const int t : L) {
        S.push(t);

        D[t][t] = 0;

        while (!S.empty()) {
            int n = S.size();
            for (int i = 0; i < n; i++) {
                int u = S.top();
                S.pop();

                for (int v : adjacency_list[u]) {
                    if (D[t][v] == -1) {
                        S.push(v);
                        D[t][v] = D[t][u] + 1;
                    }
                }
            }
        }
    }

    return D;
}

std::vector<std::pair<int, int>> get_metric_closure(const std::vector<int> &L) {
    std::vector<std::pair<int, int>> E;

    std::priority_queue<Edge> PQ;

    return E;
}

Graph create_steiner_graph(Graph G) {
    Graph T;

    return T;
}

// NOTE: for undirected graph with V-1 bidirectional edges, i.e., E=V-1
int main() {
    Graph G;
    G.initialise();

    Graph T = create_steiner_graph(G);
}
