#include "soccer.h"
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
// dp[L][R][l][r] = best with last rectangle at these bounds
int dp[N][N];
bool grid[N][N];
int s[N][N];
// going left or right last empty starting from (x, y)
int lt[N][N];
int rt[N][N];
int ml[N][N];
int mr[N][N];

void mx(int &x, int y){
    if (y > x) x = y;
}

bool check(int L, int R, int l, int r){
    return (s[R][r]-s[L-1][r]-s[R][l-1]+s[L-1][l-1]==0);
}

int biggest_stadium(int N, vector<vector<int>> F)
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            grid[i+1][j+1] = F[i][j];
            s[i+1][j+1] = s[i][j+1]+s[i+1][j]-s[i][j]+F[i][j];
        }
    }
    for (int i = 1; i <= N; i++){
        lt[i][0] = 1;
        for (int j = 1; j <= N; j++){
            if (grid[i][j]) lt[i][j] = j+1;
            else lt[i][j] = lt[i][j-1];
        }
        rt[i][N+1] = N;
        for (int j = N; j >= 1; j--){
            if (grid[i][j]) rt[i][j] = j-1;
            else rt[i][j] = rt[i][j+1];
        }
    }
    int ans = 0;
    for (int x = 1; x <= N; x++){
        for (int l = 1; l <= N; l++){
            ml[l][l] = lt[l][x];
            mr[l][l] = rt[l][x];
            for (int r = l+1; r <= N; r++){
                ml[l][r] = max(lt[r][x], ml[l][r-1]);
                mr[l][r] = min(rt[r][x], mr[l][r-1]);
            }
        }
        memset(dp, 0, sizeof(dp));
        for (int W = 1; W <= N; W++){
            for (int L = 1; L+W-1 <= N; L++){
                int R = L+W-1;
                if (!check(L,R,x,x)) continue;
                int l = ml[L][R], r = mr[L][R];
                if (l > r) dp[L][R] = 0;
                if (W == 1 || dp[L][R-1]) mx(dp[L][R], dp[L][R-1]+r-l+1);
                if (W == 1 || dp[L+1][R]) mx(dp[L][R], dp[L+1][R]+r-l+1);
                mx(ans, dp[L][R]);
            }
        }
    }

    return ans;
}





