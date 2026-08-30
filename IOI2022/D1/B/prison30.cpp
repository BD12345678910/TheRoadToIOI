#include "prison.h"
#include <bits/stdc++.h>
using namespace std;

// row: x on whiteboard, column: seen in bag table[x][0]
int table[50][5003];

vector<vector<int>> devise_strategy(int n) {
    int bt = 1, pow = 0;
    while (2*bt <= n){
        bt <<= 1;
        pow++;
    }

    // 3 numbers per bit:
    int cnt = 0;
    for (int i = pow; i >= 0; i--){
        table[cnt][0] = 0;
        for (int j = 1; j <= n; j++){
            if ((j >> i) & 1) table[cnt][j] = cnt+2;
            else table[cnt][j] = cnt+1;
        }
        // table low: cnt+1
        table[cnt+1][0] = 1;
        for (int j = 1; j <= n; j++){
            if ((j >> i) & 1) table[cnt+1][j] = -1;
            else table[cnt+1][j] = cnt+3;
        }
        // table high: cnt+2
        table[cnt+2][0] = 1;
        for (int j = 1; j <= n; j++){
            if ((j >> i) & 1) table[cnt+2][j] = cnt+3;
            else table[cnt+2][j] = -2;
        }
        cnt += 3;
    }
    // last cnt is nonexistent:
    int tot = cnt-1;
    vector<vector<int>> RET;
    for (int i = 0; i <= tot; i++){
        vector<int> tmp;
        for (int j = 0; j <= n; j++){
            if (table[i][j] == cnt) table[i][j]=0;
            tmp.push_back(table[i][j]);
        }
        RET.push_back(tmp);
    }
    return RET;
}


