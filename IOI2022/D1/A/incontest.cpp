#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NINF = -4e18;
ll dp[301][301];
ll ndp[301][301];
int grid[301][301];
ll a[301][301];

void mx(ll &x, ll y){
    if (y > x) x = y;
}

void printt(int n){
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            cout << ndp[i][j] << ' ';
        }
        cout << endl;
    }
}

ll max_weights(int N,int M,vector<int>X,vector<int>Y,vector<int>W){
    for (int i = 0; i < M; i++){
        grid[X[i]+1][Y[i]+1] = W[i];
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            a[i][j] = a[i][j-1]+grid[i][j];
        }
    }

    memset(dp, 0xc0, sizeof(dp));
    for (int i = 0; i <= N; i++){
        dp[0][i] = 0;
    }
    for (int i = 1; i < N; i++){
        // transition from i to i+1
        memset(ndp, 0xc0, sizeof(ndp));
        // case k <= j
        for (int j = 0; j <= N; j++){
            ll acc = NINF;
            for (int k = 0; k <= j; k++){
                mx(acc, dp[k][j]);
            }
            for (int nxt = 0; nxt <= j; nxt++){
                mx(ndp[j][nxt], acc+(a[i+1][j]-a[i+1][nxt]));
            }
            for (int nxt = j+1; nxt <= N; nxt++){
                mx(ndp[j][nxt], acc+(a[i][nxt]-a[i][j]));
            }
        }
        // case k > j
        for (int j = 0; j < N; j++){
            ll acc = NINF;
            for (int k = j+1; k <= N; k++){
                mx(acc, dp[k][j]);
            }
            for (int nxt = 0; nxt <= j; nxt++){
                mx(ndp[j][nxt], acc+(a[i+1][j]-a[i+1][nxt]));
            }
        }
        // case j = 0 is special
        for (int k = 0; k <= N; k++){
            for (int nxt = 0; nxt <= k; nxt++){
                mx(ndp[0][nxt], dp[k][0]);
            }
            for (int nxt = k+1; nxt <= N; nxt++){
                mx(ndp[0][nxt], dp[k][0]+a[i][nxt]-a[i][k]);
            }
        }
        
        // printt(N);
        memcpy(dp, ndp, sizeof(ndp));
    }   
    ll acc = 0;
    for (int j = 0; j <= N; j++){
        for (int k = 0; k <= N; k++){
            mx(acc, dp[j][k]);
        }
    }
    return acc;
}






