#include "sphinx.h"
#include <bits/stdc++.h>
using namespace std;
int n;
int tmp[255];
int query(int x, int l, int r){
    for (int i = 0; i < n; i++) tmp[i] = 0;
    tmp[x] = -1;
    int curr = l-1;
    for (int i = 0; i < n; i++){
        if (tmp[i] == 0 && curr != r){
            tmp[i] = ++curr;
        } else if (tmp[i] == 0){
            tmp[i] = n;
        }
    }
    // for (int i = 0; i < n; i++){
    //     cout << tmp[i] << ' ';
    // }
    // cout << '\n';

    vector<int> Q(tmp, tmp+n);
    return perform_experiment(Q);
}

vector<int> find_colours(int N, vector<int> X, vector<int> Y) {
    vector<int> ans(N); n = N;
    for (int i = 0; i < N; i++){
        // candidate range for color
        int l = 0, r = N-1;
        while (l < r){
            int mid = (l+r)>>1;
            // consider [l, mid];
            int res = query(i, l, mid);
            int ex = 1 + mid-l+1;
            if (res == ex){
                r = mid;
            } else {
                l = mid+1;
            }
        }
        ans[i] = l;
    } 
    return ans;
}
