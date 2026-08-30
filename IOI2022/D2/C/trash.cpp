#include "islands.h"
#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> rev[100005];
vector<bool> valid[100005];
vector<pair<int,int>> G[100005];
int countBack[100005];
bool alive[100005];
bool vis[100005];

void dfs_kill(int x){
    vis[x] = 1;
    vector<pair<int,int>> tmp;
    for (int i = 0; i < (int)G[x].size(); i++){
        if (!valid[x][i]) continue;
        int v = G[x][i].first;
        if (!vis[v]) dfs_kill(v);
        if (alive[v]){
            tmp.push_back(G[x][i]);
        }
    }
    if (tmp.size() == 0){
        alive[x] = 0;
    }
    G[x] = tmp;
}

variant<bool, vector<int>> find_journey
(int N, int M, vector<int> U, vector<int> V){
    for (int i = 0; i < N; i++) alive[i] = 1;
    for (int i = 0; i < M; i++){
        rev[V[i]].push_back({U[i], G[U[i]].size});
        G[U[i]].push_back({V[i], i});
        valid[U[i]].push_back(1);
        countBack[U[i]]++;
    }
    int start = 0;
    while (countBack[start] == 1){
        if (vis[start]) return false;
        alive[start] = 0;
        for (auto [x, idx] : rev[start]){
            valid[x][idx] = 0;
            countBack[x]--;
        }
        vis[start] = 1;
        for (int i = 0; i < (int)G[start].size(); i++){
            if (valid[start][i]){
                start = G[start][i].first;
                break;
            }
        }
    }
    dfs_kill(start);
    if (!alive[start]) return false;
    else return true;
}





