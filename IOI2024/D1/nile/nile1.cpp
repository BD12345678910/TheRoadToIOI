#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef vector<int> vint;

vector<ll> calculate_costs(vint W, vint A, vint B, vint E) {
    int n = (int)W.size();
    int q = (int)E.size();
    vector<long long> R;

    bool same = 1;
    for (int i = 1; i < n; i++){
        if (W[i] != W[1]) {same = 0; break;}
    }

    // subtask 1:
    if (same){
        int diff = INF;
        ll res = 0;
        for (int i = 0; i < n; i++){
            diff = min(diff, A[i]-B[i]);
            res += B[i];
        }
        if (n % 2){
            res += diff;
        }
        for (int i = 0; i < q; i++) R.push_back(res);
    } 
    return R;
}
