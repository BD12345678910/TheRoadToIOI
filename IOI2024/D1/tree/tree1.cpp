#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, LL, RR;
vector<int> p, w;
vector<int> G[200005];
ll ans; ll coef[200005];
ll subt[200005];

void init(vector<int> P, vector<int> W) {
    p = P; w = W; n = (int) p.size();
    for (int i = 1; i < n; i++){
        G[p[i]].push_back(i);
    }
}

void dfs(int x){
    ll tot = 0;
    subt[x] = 0;
    for (int v : G[x]){
        dfs(v);
        tot += subt[v];
        subt[x] += subt[v];
    }
    // leaf
    if (G[x].size() == 0){
        coef[x] = LL; 
        ans += 1LL*abs(coef[x])*w[x];
    } else {
        ll left = LL-tot;
        ll right = RR-tot;
        if (left <= 0 && 0 <= right){
            coef[x] = 0;
        } else if (left > 0){
            coef[x] = left;
        } else {
            coef[x] = right;
        }
        ans += 1LL*abs(coef[x])*w[x];
    }
    subt[x] += coef[x];
}

ll query(int L, int R) {
    LL = L; RR = R;
    ans = 0;
    dfs(0);
    return ans;
}
