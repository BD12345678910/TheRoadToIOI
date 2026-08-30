#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll psum[300005][2];

ll max_weights(int N,int M,vector<int> X,vector<int> Y,vector<int> W){
    if (N <= 2){
        ll ls = 0, rs = 0;
        for (int i = 0; i < M; i++){
            if (X[i]) rs += W[i];
            else ls += W[i];
        }
        return max(ls, rs);
    }

    ll rs = 0;
    for (int i = 0; i < M; i++) {
        if (X[i]) rs += W[i];
        psum[Y[i]][X[i]] = W[i];
    }
    for (int i = 1; i < N; i++){
        psum[i][0] += psum[i-1][0];
        psum[i][1] += psum[i-1][1];
    }
    ll ret = rs;
    for (int i = 0; i < N; i++){
        ret = max(ret, rs + psum[i][0] - psum[i][1]);
    }
    return ret;
}
