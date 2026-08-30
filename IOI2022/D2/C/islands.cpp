// INCOMPLETE COME BACK TO LATER....

#include "islands.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> rev[100005];
vector<pair<int,int>> G[100005];
int deg[100005];
// alive = whether this node could possibly be part of the final route...
bool alive[100005];
queue<int> Q;
bool vis1[100005], vis2[100005];

void kill(int x){
    alive[x] = 0;
    for (int u : rev[x]){
        if (!alive[u]) continue;
        deg[u]--;
        if (!deg[u]) Q.push(u);
    }
}

void clear(){
    while (!Q.empty()){
        int x = Q.front(); Q.pop();
        if (alive[x]) kill(x);
    }
}

variant<bool, vector<int>> find_journey
(int N, int M, vector<int> U, vector<int> V){
    for (int i = 0; i < N; i++) alive[i] = 1;
    for (int i = 0; i < M; i++){
        rev[V[i]].push_back(U[i]);
        G[U[i]].push_back({V[i], i});
        deg[U[i]]++;
    }
    for (int i = 0; i < N; i++){
        if (deg[i] == 0) Q.push(i);
    }
    vector<int> pre;
    int s = 0;
    while (1){
        clear();
        if (!alive[s]) return false;
        if (deg[s] >= 2) break;
        int v = -1, id = -1;
        for (auto [to, e]: G[s]){
            if (alive[to]){
                v = to;
                id = e;
                break;
            }
        }
        pre.push_back(id);
        kill(s);
        s = v;
    }

    // we now have s that leads to two distinct cycles...
    int v1 = -1, v2 = -1;
    int p1 = -1, p2 = -1, meet = -1;
    vector<int> P1, P2;
    vector<int> E1, E2;
    for (auto [v, e] : G[s]){
        if (alive[v]){
            if (v1 == -1){
                v1 = v;
                E1.push_back(e);
            } else if (v2 == -1){
                v2 = v;
                E2.push_back(e);
                break;
            }
        }
    }
    int x = v1;
    while (!vis1[x]){
        vis1[x] = 1;
        P1.push_back(x);
        for (auto [v,e] : G[x]){
            if (alive[v] && !(x == s && e == E1[0])) {
                x = v;
                E1.push_back(e);
                break;
            }
        }
    }
    P1.push_back(x);
    p1 = x;
    // structure: v1 --> p1 (which is part of a cycle)

    bool intersect = 0;

    x = v2;
    while (true){
        if (vis1[x]){
            intersect = 1;
            break;
        } 
        if (vis2[x]) {
            break;
        }
        vis2[x] = 1;
        P2.push_back(x);
        for (auto [v,e] : G[x]){
            if (alive[v] && !(x == s && e == E2[0])){
                E2.push_back(e);
                x = v;
                break;
            }
        }
    }
    P2.push_back(x);
    if (!intersect) p2 = x;
    else meet = x;

    assert(E1.size()==P1.size());
    assert(E2.size()==P2.size());

    vector<int> ans;
    if (!intersect){
        int t = -1;
        vector<int> W1, W2;
        for (int i = 0; i < (int)E1.size(); i++){
            int e = E1[i];
            if (P1[i] == p1 && t == -1){
                t = i;
            }
            W1.push_back(e);
        }
        for (int i = t; i >= 0; i--){
            W1.push_back(E1[i]);
        }
        t = -1;
        for (int i = 0; i < (int)E2.size(); i++){ 
            int e = E2[i];
            if (P2[i] == p2 && t == -1){
                t = i;
            }
            W2.push_back(e);
        }
        for (int i = t; i >= 0; i--){
            W2.push_back(E2[i]);
        }
        for (int e: W1) ans.push_back(e);
        for (int e: W2) ans.push_back(e);
        reverse(W1.begin(), W1.end());
        reverse(W2.begin(), W2.end());
        for (int e: W1) ans.push_back(e);
        for (int e: W2) ans.push_back(e);
    } else {
        int t = -1, k = -1;
        for (int i = 0; i < (int)P1.size(); i++){
            if (P1[i]==p1 && t==-1) {
                t = i;
            }
            if (P1[i]==meet && k==-1){
                k = i;
            }
        }
        assert(t != -1);
        if (k <= t){
            for (int i = 0; i < (int)E1.size(); i++){
                ans.push_back(E1[i]);
            }
            for (int i = t; i >= 0; i--){
                ans.push_back(E1[i]);
            }
            for (int i = 0; i < (int)E2.size(); i++){
                ans.push_back(E2[i]);
            }
            for (int i = k+1; i <= t; i++){
                ans.push_back(E1[i]);
            }
            for (int i = (int)E1.size()-1; i > t; i--){
                ans.push_back(E1[i]);
            }
            for (int i = t; i >= k+1; i--){
                ans.push_back(E1[i]);
            }
            for (int i = (int)E2.size()-1; i >= 0; i--){
                ans.push_back(E2[i]);
            }
        } else {
            for (int i = 0; i < (int)E1.size(); i++){
                ans.push_back(E1[i]);
            }
            for (int i = t; i >= 0; i--){
                ans.push_back(E1[i]);
            }
            for (int i = 0; i < (int)E2.size(); i++){
                ans.push_back(E2[i]);
            }
            for (int i = k; i > t; i--){
                ans.push_back(E1[i]);
            }
            for (int i = (int)E1.size()-1; i >= k+1; i--){
                ans.push_back(E1[i]);
            }
            for (int i = (int)E2.size()-1; i >= 0; i--){
                ans.push_back(E2[i]);
            }
        }
    }
    vector<int> ret = pre;
    for (int e: ans) ret.push_back(e);
    reverse(pre.begin(), pre.end());
    for (int e: pre) ret.push_back(e);

    return ret;
}





