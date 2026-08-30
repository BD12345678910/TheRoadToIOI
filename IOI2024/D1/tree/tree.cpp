#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, LL, RR;
vector<int> p, w;
vector<int> G[200005];
int leaf;

void dfs(int x){
    if (G[x].size()==0){
        leaf++; return;
    }
    for (int v : G[x]){
        dfs(v);
    }
}

void init(vector<int> P, vector<int> W) {
    p = P; w = W; n = (int) p.size();
    leaf = 0;
    for (int i = 1; i < n; i++){
        G[p[i]].push_back(i);
    }
    dfs(0);
}

ll query(int L, int R) {
    return 1LL*leaf*L+max(1LL*leaf*L-R, 0LL);
}



