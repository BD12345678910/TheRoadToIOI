#include "prison.h"
#include <bits/stdc++.h>
using namespace std;

// row: x on whiteboard, column: seen in bag table[x][0]
int table[503][503];

vector<vector<int>> devise_strategy(int n) {
    int B = sqrt(n);
    // check Bag A
    table[0][0] = 0;
    for (int i = 1; i <= n; i++){
        table[0][i] = (i-1)/B+1;
    }
    // 1 has [1, B], 2 has [B+1, 2B] etc.

    // now check Bag B: given Bag A in [iB-B+1, iB]
    int inter = (n-1)/B+1+1;
    for (int i = 1; i < inter; i++){
        table[i][0] = 1;
        for (int j = 1; j <= n; j++){
            if (j < i*B-B+1) table[i][j] = -2;
            else if (j > i*B) table[i][j] = -1;
            else table[i][j] = inter;
        }   
    }
    // check Bag A for mod B
    table[inter][0] = 0;
    for (int i = 1; i <= n; i++){
        table[inter][i] = inter + (i-1)%B + 1;
    }

    for (int i = inter+1; i <= inter+B; i++){
        table[i][0] = 1;
        int me = i-inter-1;
        for (int j = 1; j <= n; j++){
            if ((j-1)%B > me) table[i][j] = -1;
            else table[i][j] = -2;
        }
    }
    int tot = inter + B;
    vector<vector<int>> RET;
    for (int i = 0; i <= tot; i++){
        vector<int> tmp;
        for (int j = 0; j <= n; j++){
            tmp.push_back(table[i][j]);
        }
        RET.push_back(tmp);
    }
    return RET;
}


