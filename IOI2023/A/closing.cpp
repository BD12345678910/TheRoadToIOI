#include "closing.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 3003;
vector<pair<int,int>> G[MAXN];
// the spine from X to Y
ll d[2][MAXN];
bool spine[MAXN];
ll a[MAXN], b[MAXN];
// smallest cost for first i to obtain j points
ll dp[MAXN][MAXN<<1];

int sub1(int N, ll K){
    priority_queue<ll, vector<ll>, greater<ll> > P;
    for (int i = 0; i < N; i++){
        P.push(min(d[0][i], d[1][i]));
    }
    int ans = 0;
    while (!P.empty() && K - P.top() >= 0){
        K -= P.top(); 
        P.pop();
        ans++;
    }
    return ans;
}

bool dfs(int x, int pa, int target){
    if (x == target){
        spine[x] = 1;
        return 1;
    }
    for (auto [v, w] : G[x]){
        if (v == pa) continue;
        if (dfs(v, x, target)){
            spine[x] = 1;
            return 1;
        }
    }
    return 0;
}

void finddist(int x, int pa, ll dist, int idx){
    d[idx][x] =  dist;
    for (auto [v, w] : G[x]){
        if (v == pa) continue;
        finddist(v, x, dist+w, idx);
    }
}

int max_score(int N, int X, int Y, long long K,
              vector<int> U, vector<int> V, vector<int> W){
    memset(spine, 0, sizeof(spine));
    for (int i = 0; i < N; i++){
        G[i].clear();
    }
    ll ogK = K;
    for (int i = 0; i < N-1; i++){
        G[U[i]].push_back({V[i], W[i]});
        G[V[i]].push_back({U[i], W[i]});
    }
    finddist(X, X, 0, 0);
    finddist(Y, Y, 0, 1);
    dfs(X, X, Y);

    int ans = 0;
    for (int i = 0; i < N; i++){
        if (spine[i]){
            // pay by force:
            ll tmp = min(d[0][i], d[1][i]);
            K -= tmp;
            a[i] = 0;
            b[i] = max(d[0][i], d[1][i])-tmp;
        } else {
            a[i] = min(d[0][i], d[1][i]);
            b[i] = max(d[0][i], d[1][i]);
        }
    }

    if (K >= 0){
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0; dp[0][1] = a[0]; dp[0][2] = b[0];
        for (int i = 1; i < N; i++){
            // consider transfering to i, 
            for (int j = 0; j <= 2*N; j++){
                dp[i][j] = dp[i-1][j];
            }
            for (int j = 1; j <= 2*N; j++){
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]+a[i]);
            }
            for (int j = 2; j <= 2*N; j++){
                dp[i][j] = min(dp[i][j], dp[i-1][j-2]+b[i]);
            }
        }
        while (ans <= 2*N && dp[N-1][ans] <= K) {ans++;}
        ans--;
    }
    ans = max(ans, sub1(N, ogK));
    return ans;
}



