#include "beechtree.h"
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<pair<int,int>> G[200005];
map<int,int> M[200005];
int ans[200005];
int sz[200005];
set<pair<int,int>> sign[200005];

bool check(int x, int y){
    for (auto [v, c]: G[y]){
        if (!M[x].count(c)) return 0;
        int vx = M[x][c];
        if (sz[vx] < sz[v]) return 0;
    }
    return 1;
}

// merge y into x!
bool merge(int x, int y){
    if (sign[x].size() < sign[y].size()) {
        swap(sign[x], sign[y]);
    }
    for (auto P : sign[y]){
        auto it = sign[x].lower_bound(P);
        if (it != sign[x].end() && !check(it->second, P.second)){
            return 0;
        }
        if (it != sign[x].begin() && !check(P.second, (--it)->second)){
            return 0;
        }
        sign[x].insert(P);
    }
    sign[y].clear();
    return 1;
}

void dfs(int x){
    sign[x].insert({sz[x], x});
    for (auto [v,c] : G[x]){
        dfs(v);
    }
    for (auto [v, c]: G[x]){
        if (!ans[v] || !merge(x, v)){
            ans[x] = 0;
            return;
        }
    }
}

void dfs_pre(int x){
    set<int> color;
    sz[x] = 1;
    ans[x] = 1;
    for (auto [v, w]: G[x]){
        dfs_pre(v);
        sz[x] += sz[v];
        ans[x] = (ans[x] && ans[v]);
        if (color.count(w)) {
            ans[x] = 0;
        } else {
            M[x][w] = v;
            color.insert(w);
        }
    }
}

vector<int> beechtree(int N, int M, vector<int> P, vector<int> CC){
    n = N; m = M; 
    for (int i = 1; i < N; i++){
        G[P[i]].push_back({i, CC[i]});
    }
    dfs_pre(0);
    dfs(0);
    return vector<int>(ans, ans+N);
}





