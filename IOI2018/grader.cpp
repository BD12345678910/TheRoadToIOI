#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <cstdlib>

// ------------------------------------------------------------
//  PROBLEM SPECIFIC GLOBALS
// ------------------------------------------------------------
static int N, M, A, B, S, T;
static std::vector<int> U, V;
static int query_count = 0;
static const int QUERY_LIMIT = 51;

// ------------------------------------------------------------
//  SHORTEST PATH COMPUTATION (graders Dijkstra)
// ------------------------------------------------------------
static long long compute_shortest_path(const std::vector<int>& w) {
    std::vector<std::vector<std::pair<int, long long>>> adj(N);
    for (int i = 0; i < M; ++i) {
        adj[U[i]].push_back({V[i], w[i]});
        adj[V[i]].push_back({U[i], w[i]});
    }

    std::vector<long long> dist(N, std::numeric_limits<long long>::max());
    dist[S] = 0;
    using pll = std::pair<long long, int>;
    std::priority_queue<pll, std::vector<pll>, std::greater<pll>> pq;
    pq.push({0, S});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        if (u == T) break;
        for (auto [v, wgt] : adj[u]) {
            if (dist[v] > d + wgt) {
                dist[v] = d + wgt;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[T];
}

// ------------------------------------------------------------
//  GRADER FUNCTION THAT YOU CALL
// ------------------------------------------------------------
int ask(const std::vector<int>& w) {
    if (++query_count > QUERY_LIMIT) {
        std::cerr << "Too many queries!" << std::endl;
        std::exit(0);
    }
    if ((int)w.size() != M) {
        std::cerr << "ask(): argument size must be M" << std::endl;
        std::exit(0);
    }
    for (int x : w) {
        if (x != A && x != B) {
            std::cerr << "ask(): weights must be exactly A or B" << std::endl;
            std::exit(0);
        }
    }
    return (int)compute_shortest_path(w);
}

// ------------------------------------------------------------
//  YOUR FUNCTION (declaration)
// ------------------------------------------------------------
extern std::pair<int, int> find_pair(
    int N, const std::vector<int>& U, const std::vector<int>& V, int A, int B
);

// ------------------------------------------------------------
//  MAIN
// ------------------------------------------------------------
int main() {
    // Read input: N M A B S T, then M edges (U V)
    std::cin >> N >> M >> A >> B >> S >> T;
    U.resize(M);
    V.resize(M);
    for (int i = 0; i < M; ++i) {
        std::cin >> U[i] >> V[i];
    }

    std::pair<int, int> answer = find_pair(N, U, V, A, B);
    
    // Check
    if ((answer.first == S && answer.second == T) ||
        (answer.first == T && answer.second == S)) {
        std::cout << "OK" << std::endl;
        std::cout << "Queries used: " << query_count << std::endl;
        return 0;
    } else {
        std::cout << "WRONG ANSWER" << std::endl;
        std::cout << "Expected: " << S << " " << T << std::endl;
        std::cout << "Got: " << answer.first << " " << answer.second << std::endl;
        return 1;
    }
}