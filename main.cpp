#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

void print_vector(const std::vector<int> &);

class Graph {
  public:
    int E;
    int V;

    std::vector<int> L;

    std::map<int, std::vector<int>> adjacency_list;

    Graph() {};

    ~Graph() {};

    void initialise() {
        std::cin >> E >> V;

        for (int i = 0; i < E - 1; i++) {
            int u;
            int v;

            std::cin >> u >> v;

            adjacency_list[u - 1].push_back(v - 1);
            adjacency_list[v - 1].push_back(u - 1);
        }

        L.resize(V);

        for (int &l : L) {
            std::cin >> l;
            --l;
        }
    }

    void add_edges(const std::set<std::pair<int, int>> edges) {
        for (auto [u, v] : edges) {
            adjacency_list[u].push_back(v);
            adjacency_list[v].push_back(u);
        }
    }

    void output() {
        for (const auto &[k, v] : adjacency_list) {
            std::cout << k << ": ";
            print_vector(v);
        }
    }
};

struct Edge {
    int u;
    int v;
    int d;

    bool operator<(const Edge &other) const {
        return d > other.d;
    }
};

void print_vector(const std::vector<int> &vec) {
    int n = vec.size();

    std::cout << "[";

    for (int i = 0; i < n; i++) {
        std::cout << vec[i];

        if (i < n - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

std::vector<std::vector<int>> get_distances(const std::vector<int> &L, std::map<int, std::vector<int>> &adjacency_list, int E) {
    std::stack<int> S;

    std::vector<std::vector<int>> D(E, std::vector<int>(E, -1));

    for (int t : L) {
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

std::vector<std::pair<int, int>> get_metric_closure(const std::vector<int> &L, const std::vector<std::vector<int>> &D, int E) {
    std::priority_queue<Edge> PQ;

    std::vector<bool> visited(E, false);

    std::vector<std::pair<int, int>> LE;

    PQ.push(Edge{L[0], L[0], 0});

    while (!PQ.empty()) {
        auto [u, p, w] = PQ.top();
        PQ.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        if (p != u) {
            LE.push_back({p, u});
        }

        for (int v : L) {
            if (v != u) {
                PQ.push(Edge{v, u, D[u][v]});
            }
        }
    }

    return LE;
}

std::vector<int> get_path(std::map<int, int> &parent, int destination) {
    int current = destination;

    std::vector<int> path = {destination};

    while (parent[current] != -1) {
        current = parent[current];
        path.push_back(current);
    }

    return path;
}

int find_first_node(std::set<int> &TV, std::vector<int> &path, int n) {
    for (int i = 0; i < n; i++) {
        if (TV.find(path[i]) != TV.end()) {
            return i;
        }
    }

    return -1;
}

int find_first_node_reverse(std::set<int> &TV, std::vector<int> &path, int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (TV.find(path[i]) != TV.end()) {
            return i;
        }
    }

    return -1;
}

void merge_subpath(std::set<std::pair<int, int>> &TE, std::set<int> &TV, std::vector<int> &path, int l, int r, int n) {
    while (l < r) {
        TV.insert(path[l]);

        if (l + 1 < n) {
            TE.insert(std::make_pair(path[l], path[l + 1]));
        }

        ++l;
    }
}

void merge_path(std::set<std::pair<int, int>> &TE, std::set<int> &TV, std::vector<int> &path) {
    int n = path.size();

    if (n < 2 || TV.empty()) {
        merge_subpath(TE, TV, path, 0, n, n);

        return;
    }

    int i = find_first_node(TV, path, n);
    int j = find_first_node_reverse(TV, path, n);

    if (i != -1) {
        merge_subpath(TE, TV, path, 0, i, n);
    }

    if (j != -1) {
        merge_subpath(TE, TV, path, j, n, n);
    }
}

Graph get_steiner_graph(Graph G) {
    Graph T;

    bool found;

    std::set<int> TV;

    std::vector<int> path;

    std::set<std::pair<int, int>> TE;

    std::vector<std::vector<int>> D = get_distances(G.L, G.adjacency_list, G.E);

    std::vector<std::pair<int, int>> LE = get_metric_closure(G.L, D, G.E);

    for (auto [a, b] : LE) {
        std::queue<int> Q;

        std::map<int, int> parent;

        std::vector<bool> visited(G.V, false);

        Q.push(a);
        found = false;
        parent[a] = -1;
        visited[a] = true;

        while (!(Q.empty() || found)) {
            int n = Q.size();

            for (int i = 0; i < n; i++) {
                int u = Q.front();
                Q.pop();

                if (u == b) {
                    found = true;
                    break;
                }

                for (int v : G.adjacency_list[u]) {
                    if (!visited[v]) {
                        Q.push(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }
        }

        path = get_path(parent, b);

        merge_path(TE, TV, path);
    }

    T.add_edges(TE);

    return T;
}

/**
 * @brief constructs a steiner tree given that the graph edges are bidirectional (undirected).
 *
 * Input: two space separated integers denoting the number of edges (E-1), where the number
 * of each vertex will be in the range 1 <= x <= E for simplicity, i.e., 1-indexed, and
 * the number of terminal nodes (V).
 *
 * The next E-1 lines will be two separated integers denoting the edges of the input graph.
 *
 * The last line contains V separated integers, denoting the vertex number for each of the
 * terminal nodes.
 *
 * @return a steiner tree.
 */
int main() {
    Graph G;
    G.initialise();

    Graph T = get_steiner_graph(G);
    T.output();
}
