#include "soccer.h"
#include <bits/stdc++.h>
using namespace std;
const int NN = 2005;
bool grid[NN][NN];
int s[NN][NN];
int l[NN], r[NN];

void mx(int &x, int y){
    if (y > x) x = y;
}

int check(int L, int R, int lx, int rx){
    return (s[R][rx]-s[L-1][rx]-s[R][lx-1]+s[L-1][lx-1]);
}

int biggest_stadium(int N, vector<vector<int>> F)
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            grid[i+1][j+1] = F[i][j];
            s[i+1][j+1] = s[i][j+1]+s[i+1][j]-s[i][j]+F[i][j];
        }
    }

    for (int j = 1; j <= N; j++){
        for (int i = 1; i <= N; i++){
            if (!grid[i][j]) r[j] = i;
            if (!grid[i][j] && !l[j]) l[j] = i;
        }
        if (!l[j]) continue;
        if (check(l[j], r[j], j, j)){
            return 0;
        }
    }

    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    int ans = 0;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            if (!grid[i][j]) r[i] = j;
            if (!grid[i][j] && !l[i]) l[i] = j;
        }
        if (!l[i]) continue;
        if (check(i, i, l[i], r[i])){
            return 0;
        }
        // cout << l[i] << ' ' << r[i] << endl;
        ans += r[i]-l[i]+1;
    }

    for (int i = 1; i <= N; i++){
        if (!l[i]) continue;
        for (int j = i+1; j <= N; j++){
            if (!l[j]) continue;
            if (l[i] <= l[j] && r[j] <= r[i]) continue;
            if (l[j] <= l[i] && r[i] <= r[j]) continue;
            return 0;
        }
    }

    return ans;
}





