#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vint;
const ll INFFF = 1e18;

struct Data{
    ll w, a, b;
} D[100005];

bool cmp(Data A, Data B){
    return A.w < B.w;
}

ll dp[100005], dpx[100005], diff[100005];

vector<ll> calculate_costs(vint W, vint A, vint B, vint E) {
    int n = (int)W.size();
    vector<ll> R;

    for (int i = 0; i < n; i++){
        D[i+1] = {W[i], A[i], B[i]};
    }
    sort(D+1, D+n+1, cmp);
    ll asum = 0;
    for (int i = 1; i <= n; i++){
        asum += D[i].a;
        diff[i] = D[i].b-D[i].a;
    }

    for (int Q : E){
        for (int i = 0; i <= n; i++){
            dp[i] = dpx[i] = INFFF;
        }
        dp[0] = dpx[0] = dp[1] = dpx[1] = 0;
        for (int i = 2; i <= n; i++){
            dp[i] = INFFF;
            if (D[i].w-D[i-1].w <= Q){
                dp[i] = min(dpx[i-2] + diff[i-1] + diff[i], dp[i]);
            }
            if (i > 2 && D[i].w-D[i-2].w <= Q){
                dp[i] = min(dpx[i-3] + diff[i-2] + diff[i], dp[i]);
            }
            dpx[i] = min(dp[i], dpx[i-1]);
        }
        R.push_back(asum+dpx[n]);
    }

    return R;
}




