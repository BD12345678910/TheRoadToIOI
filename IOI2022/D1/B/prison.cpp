#include "prison.h"
#include <bits/stdc++.h>
using namespace std;

// BASE 3!
// row: x on whiteboard, column: seen in bag table[x][0]
int table[50][5003];

vector<vector<int>> devise_strategy(int n) {
    if (n == 2) return {{0, -1, -2}};

    int bt = 1, pow = 0;
    while (3*bt <= n){
        bt *= 3;
        pow++;
    }

    // 4 numbers per "trit":
    int cnt = 0;
    int first = 0;
    table[0][0] = 0;
    for (int j = 1; j <= n; j++){
        int cur = (j / bt) % 3;
        table[0][j] = 1+cur;
    }

    for (int i = pow; i >= 1; i--){
        first = 1-first;
        table[cnt+1][0] = first;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            if (cur == 0) {
                int btt = bt/3;
                int curr = (j/btt) % 3;
                if (btt == 0) continue;
                if (i == 1 && curr == 0) table[cnt+1][j] = (!first?-1:-2);
                else if (i == 1 && curr == 2) table[cnt+1][j] = (first?-1:-2);
                else if (i == 1 && curr == 1) table[cnt+1][j] = cnt+4;
                else table[cnt+1][j] = cnt+4+curr;
            }
            else table[cnt+1][j] = ((first)?-1:-2);
        }
        table[cnt+2][0] = first;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            if (cur == 1) {
                int btt = bt/3;
                if (btt == 0) continue;
                int curr = (j/btt) % 3;
                if (i == 1 && curr == 0) table[cnt+2][j] = (!first?-1:-2);
                else if (i == 1 && curr == 2) table[cnt+2][j] = (first?-1:-2);
                else if (i == 1 && curr == 1) table[cnt+2][j] = cnt+4;
                else table[cnt+2][j] = cnt+4+curr;
            }
            else if (cur == 2) table[cnt+2][j] = ((first)?-1:-2);
            else table[cnt+2][j] = ((!first)?-1:-2);
        }
        table[cnt+3][0] = first;
        for (int j = 1; j <= n; j++){
            int cur = (j / bt) % 3;
            if (cur == 2) {
                int btt = bt/3;
                if (btt == 0) continue;
                int curr = (j/btt) % 3;
                if (i == 1 && curr == 0) table[cnt+3][j] = (!first?-1:-2);
                else if (i == 1 && curr == 2) table[cnt+3][j] = (first?-1:-2);
                else if (i == 1 && curr == 1) table[cnt+3][j] = cnt+4;
                else table[cnt+3][j] = cnt+4+curr;
            }
            else table[cnt+3][j] = ((!first)?-1:-2);
        }
        cnt += 3;
        bt /= 3;
    }
    cnt++;
    // last digit:
    first = 1-first;
    table[cnt][0] = first;
    for (int j = 1; j <= n; j++){
        // first is smaller
        if (j % 3 == 0) table[cnt][j] = (!first)?-1:-2;
        else table[cnt][j] = (first)?-1:-2;
    }

    int tot = cnt;
    vector<vector<int>> RET;
    for (int i = 0; i <= tot; i++){
        vector<int> tmp;
        for (int j = 0; j <= n; j++){
            if (table[i][j] > cnt) table[i][j] = 0;
            tmp.push_back(table[i][j]);
        }
        RET.push_back(tmp);
    }
    return RET;
}


