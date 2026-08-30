#include "mosaic.h"
#include <bits/stdc++.h>
using namespace std;

bool a[5003][5003];
int su[5003][5003];

vector<long long> mosaic(vector<int> X, vector<int> Y,
    vector<int> T, vector<int> B,
    vector<int> L, vector<int> R) {
    int Q = (int)T.size();
    int N = (int)X.size();

    for (int i = 1; i <= N; i++){
        a[1][i] = X[i-1];
        a[i][1] = Y[i-1];
        su[1][i] = su[1][i-1]+a[1][i];
        su[i][1] = su[i-1][1]+a[i][1];
    }
    for (int i = 2; i <= N; i++){
        for (int j = 2; j <= N; j++){
            a[i][j] = (!a[i-1][j] && !a[i][j-1]);
            su[i][j] = su[i-1][j] + su[i][j-1] - su[i-1][j-1] + a[i][j];
        }
    }

    bool flag = 1;
    for (int i = 4; i <= N; i++){
        for (int j = 4; j <= N; j++){
            if (i >= j){
                int d = j-3;
                if (a[i][j] != a[i-d][j-d]) flag = 0;
            } else {
                int d = i-3;
                if (a[i][j] != a[i-d][j-d]) flag = 0;
            }
        }
    }

    vector<long long> ans;
    for (int i = 0; i < Q; i++){
        int t = T[i]+1, b = B[i]+1, l = L[i]+1, r = R[i]+1;
        ans.push_back(su[b][r]-su[b][l-1]-su[t-1][r]+su[t-1][l-1]);
    }
    return ans;
}
