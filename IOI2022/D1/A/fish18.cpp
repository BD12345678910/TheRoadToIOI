#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NINF = -1e18;
ll a[300005];
// after choosing first i, i-1 taken, i taken
ll dp[300005][2][2];

ll max_weights(int N,int M,vector<int>X,vector<int>Y,vector<int>W){
    for (int i = 0; i < M; i++){
        a[X[i]+1] = W[i];
    }
    dp[1][0][0] = 0;
    dp[1][0][1] = a[2];
    dp[1][1][0] = dp[1][1][1] = NINF;
    for (int i = 1; i < N; i++){
        dp[i+1][0][0] = max(dp[i][0][0], dp[i][1][0]);
        dp[i+1][0][1] = max(dp[i][0][0]+a[i+2]+a[i], dp[i][1][0]+a[i+2]);
        dp[i+1][1][0] = max(dp[i][0][1], dp[i][1][1]);
        dp[i+1][1][1] = max(dp[i][0][1]+a[i+2]-a[i+1], dp[i][1][1]+a[i+2]-a[i+1]);
    }
    return max(max(dp[N][0][0], dp[N][1][0]), max(dp[N][0][1], dp[N][1][1]));
}
