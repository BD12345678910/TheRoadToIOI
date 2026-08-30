#include "sphinx.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> find_colours(int N, vector<int> X, vector<int> Y) {
    vector<int> ans(N);
    vector<bool> same(N);
    for (int i = 0; i < N-1; i++){
        // consider if i and i+1 are same...
        int ex;
        if (i == 0 || i == N-2){
            ex = 2;
        } else {
            ex = 3;
        }
        vector<int> E;
        for (int k = 0; k < i; k++) E.push_back(N);
        E.push_back(-1);
        E.push_back(-1);
        for (int k = i+2; k < N; k++) E.push_back(N);
        int res = perform_experiment(E);
        same[i] = (res == ex);
    }
    ans[0] = 0;
    for (int i = 1; i < N; i++){
        if (same[i-1]) ans[i] = ans[i-1];
        else ans[i] = ans[i-1]+1;
    }
    return ans;
}
