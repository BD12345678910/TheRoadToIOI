#include "prison.h"
#include <bits/stdc++.h>
using namespace std;

// BASE 3!
// row: x on whiteboard, column: seen in bag table[x][0]
int table[50][5003];

vector<vector<int>> devise_strategy(int n) {
    int bt = 1, pow = 0;
    while (3*bt <= n){
        bt *= 3;
        pow++;
    }
    // bt <= 7, expected 31: 48.5 points

    // 4 numbers per "trit":
    int cnt = 0;
    for (int i = pow; i >= 0; i--){
        table[cnt][0] = 0;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            table[cnt][j] = cnt+1+cur;
        }

        table[cnt+1][0] = 1;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            if (cur == 0) table[cnt+1][j] = cnt+4;
            else table[cnt+1][j] = -1;
        }

        table[cnt+2][0] = 1;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            if (cur == 1) table[cnt+2][j] = cnt+4;
            else if (cur == 2) table[cnt+2][j] = -1;
            else table[cnt+2][j] = -2;
        }

        table[cnt+3][0] = 1;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            if (cur == 2) table[cnt+3][j] = cnt+4;
            else table[cnt+3][j] = -2;
        }
        cnt += 4;
        bt /= 3;
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


