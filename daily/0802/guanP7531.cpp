#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1'000'000'007;
const int MAXN = 105;

ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

ll determinant(vector<vector<ll>> a) {
    int n = (int)a.size();
    ll ans = 1;

    for (int col = 0; col < n; col++) {
        int pivot = col;

        while (pivot < n && a[pivot][col] == 0)
            pivot++;

        if (pivot == n)
            return 0;

        if (pivot != col) {
            swap(a[pivot], a[col]);
            ans = (MOD - ans) % MOD;
        }

        ans = ans * a[col][col] % MOD;
        ll inv = mod_pow(a[col][col], MOD - 2);

        for (int row = col + 1; row < n; row++) {
            ll coef = a[row][col] * inv % MOD;

            for (int j = col; j < n; j++) {
                a[row][j] =
                    (a[row][j] - coef * a[col][j]) % MOD;

                if (a[row][j] < 0)
                    a[row][j] += MOD;
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll fact[MAXN];
    fact[0] = 1;

    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        string type;
        cin >> type;

        vector<string> adj(N);
        for (string &row : adj)
            cin >> row;

        int A = N;
        int B = N + 1;
        int V = N + 2;

        vector<vector<ll>> lap(V, vector<ll>(V));
        vector<int> outdeg(V);

        auto add_edge = [&](int u, int v, int count = 1) {
            outdeg[u] += count;

            // Directed Laplacian:
            // L[u][u] += number of outgoing edges
            // L[u][v] -= number of edges u -> v
            lap[u][u] = (lap[u][u] + count) % MOD;
            lap[u][v] = (lap[u][v] - count + MOD) % MOD;
        };

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (adj[i][j] == '1')
                    add_edge(i, j);
            }
        }

        int S = 0;

        for (int i = 0; i < N; i++) {
            if (type[i] == 'S') {
                add_edge(A, i);
                S++;
            }

            if (type[i] == 'R')
                add_edge(i, B);
        }

        // S distinguishable parallel edges B -> A.
        add_edge(B, A, S);

        /*
         * Matrix-Tree theorem:
         * Delete row A and column A.
         * The determinant counts in-arborescences rooted at A.
         */
        vector<vector<ll>> minor;

        for (int i = 0; i < V; i++) {
            if (i == A)
                continue;

            vector<ll> row;

            for (int j = 0; j < V; j++) {
                if (j != A)
                    row.push_back(lap[i][j]);
            }

            minor.push_back(row);
        }

        ll tree_count = determinant(minor);

        ll ans = tree_count;

        for (int v = 0; v < N; v++)
            ans = ans * fact[outdeg[v] - 1] % MOD;

        ans = ans * mod_pow(S, MOD - 2) % MOD;

        cout << ans << '\n';
    }
}