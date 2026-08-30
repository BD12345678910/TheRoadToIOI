#include "sphinx.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> find_colours(int N, vector<int> X, vector<int> Y) {
    vector<int> ans(N);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            vector<int> E;
            for (int k = 0; k < i; k++) E.push_back(j);
            E.push_back(-1);
            for (int k = i+1; k < N; k++) E.push_back(j);
            int res = perform_experiment(E);
            if (res == 1){
                ans[i] = j;
                break;
            }
        }
    }
    return ans;
}
