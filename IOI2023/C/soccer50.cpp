#include "soccer.h"
#include <bits/stdc++.h>
using namespace std;

// dp[L][R][l][r] = best with last rectangle at these bounds
int dp[33][33][33][33];
bool grid[33][33];
int s[33][33];

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
    for (int L = 1; L <= N; L++){
        for (int l = 1; l <= N; l++){
            for (int r = l; r <= N; r++){
                if (check(L, L, l, r))
                dp[L][L][l][r] = (r-l+1);
            }
        }
    }
    int ans = 0;
    for (int W = 1; W <= N; W++){
    for (int L = 1; L+W-1 <= N; L++){
        int R = L+W-1;
    for (int l = 1; l <= N; l++){
    for (int r = l; r <= N; r++){
        if (!dp[L][R][l][r]) continue;
        mx(ans, dp[L][R][l][r]);
        // consider transfering from dp[L][R][l][r]
        if (L > 1){
            for (int ll = l; ll <= r; ll++){
                for (int rr = ll; rr <= r; rr++){
                    if (check(L-1, L-1, ll, rr))
                    mx(dp[L-1][R][ll][rr], dp[L][R][l][r]+(rr-ll+1));
                }
            }
        }
        if (R < N){
            for (int ll = l; ll <= r; ll++){
                for (int rr = ll; rr <= r; rr++){
                    if (check(R+1, R+1, ll, rr))
                    mx(dp[L][R+1][ll][rr], dp[L][R][l][r]+(rr-ll+1));
                }
            }
        }
        if (L > 1 && R < N){
            for (int ll = l; ll <= r; ll++){
                for (int rr = ll; rr <= r; rr++){
                    if (check(L-1, L-1, ll, rr) && check(R+1, R+1, ll, rr))
                    mx(dp[L-1][R+1][ll][rr], dp[L][R][l][r]+2*(rr-ll+1));
                }
            }
        }
    }
    }
    }
    }

    return ans;
}
