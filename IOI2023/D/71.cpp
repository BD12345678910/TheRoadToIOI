#include "beechtree.h"
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> p, C;
vector<pair<int,int>> G[2005];
int ans[2005];
int sz[2005];
bool rep[2005];
int col[200005];
int num[2005];
// ord is the final order
// P is a list of fronts
// Q is a series of queues by color
vector<int> ord;
priority_queue<pair<int,int>> P;
queue<int> Q[200005];

void add_ch(int x){
    for (auto [v, c] : G[x]){
        if (Q[c].empty()) P.push({sz[v], c});
        Q[c].push(v);
    }
}

int solve(int X){
    if (rep[X]) return 0;
    ord.clear();
    int cnt = 0;
    add_ch(X); ord.push_back(X); num[X] = 0;
    while (!P.empty()){
        auto [szz, c] = P.top(); P.pop();
        int x = Q[c].front(); Q[c].pop();
        // remove it from the queue, and add its children
        if (!Q[c].empty()) P.push({sz[Q[c].front()], c});
        add_ch(x); ord.push_back(x); num[x] = ++cnt;
    }

    // brute force checking:
    for (int i = 0; i <= m; i++) col[i] = 0;
    for (int x : ord){
        if (x == X) continue;
        if (col[C[x]] != num[p[x]]){
            return 0;
        }
        col[C[x]]++;
    }
    return 1;
}

void dfs_solve(int x){
    ans[x] = solve(x);
    for (auto [v, _] : G[x]){
        dfs_solve(v);
    }
}

void dfs_pre(int x){
    set<int> color;
    sz[x] = 1;
    for (auto [v, w]: G[x]){
        dfs_pre(v);
        sz[x] += sz[v];
        rep[x] = (rep[x] || rep[v]);
        if (color.count(w)) {
            rep[x] = 1;
        } else {
            color.insert(w);
        }
    }
}

vector<int> beechtree(int N, int M, vector<int> P, vector<int> CC){
    n = N; m = M; p = P; C = CC;
    for (int i = 1; i < N; i++){
        G[P[i]].push_back({i, CC[i]});
    }
    dfs_pre(0);
    dfs_solve(0);
    return vector<int>(ans, ans+N);
}