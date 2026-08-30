#include "towers.h"
#include <bits/stdc++.h>
using namespace std;
const int NINF = -6e5;
int n;
vector<int> h;
int st[2003][12];
int lg[2003];
int dp[2004];

void init(int N, vector<int> H) {
    n = N; h = H;
    for (int i = 0; i < N; i++) st[i][0] = h[i];
    for (int i = 1; i <= 11; i++){
        for (int j = 0; j+(1<<i)-1 < N; j++){
            st[j][i] = max(st[j][i-1], st[j+(1<<(i-1))][i-1]);
        }
    }
    lg[0] = -1;
    for (int i = 1; i <= N; i++){
        lg[i] = lg[i>>1]+1;
    }
}

int mx(int x, int y){
    int diff = lg[y-x+1];
    return max(st[x][diff], st[y-(1<<diff)+1][diff]);
}

int max_towers(int L, int R, int D) {
    dp[L] = 1; int ever = 1;
    for (int i = L+1; i <= R; i++){
        dp[i] = 1;
        for (int j = L; j < i-1; j++){
            if (mx(j+1, i-1) >= max(h[i], h[j])+D){
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
        ever = max(ever, dp[i]);
    }
    return ever;
}



