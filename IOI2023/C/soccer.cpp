#include "soccer.h"
#include <bits/stdc++.h>
using namespace std;
const int NN = 2005;
int dp[NN][NN];
int pos[NN][NN];
int l[NN][NN], r[NN][NN];

void mx(int &x, int y){
    if (y > x) x = y;
}

vector<pair<int,int>> bucket[NN];

int biggest_stadium(int N, vector<vector<int>> F)
{
    int ans = 0;
    for (int j = 1; j <= N; j++){
        for (int i = 1; i <= N; i++){
            dp[i][j] = 0;
            if (F[i-1][j-1]) pos[i][j] = i;
            else pos[i][j] = pos[i-1][j];
            bucket[i-pos[i][j]].push_back({i, j});
        }
    }
    for (int i = 1; i <= N; i++){
        L[i][0] = 0;
        for (int j = 1; j <= N; j++){
            if (F[i-1][j-1]) L[i][j] = j;
            else L[i][j] = L[i][j-1];
        }
        R[i][N+1];
        for (int j = 1; j <= N; j++){
            if (F[i-1][j-1]) R[i][j] = j;
            else R[i][j] = R[i][j+1];
        }
    }

    for (int d = 1; d <= n; d++){
        for (auto[i, j]: bucket[d]){
            if (pos[i][j] != i-1){
                R[i][j] = min(R[i][j], R[i-1][j]);
                L[i][j] = max(L[i][j], L[i-1][j]);
                ??
            }
            // dp[i][j] = the best stadium
            // with bottom i and 
            dp[i][j] = dp[i-1][j]+R[i][j]-L[i][j]-1;

        }
    }

    return ans;
}





