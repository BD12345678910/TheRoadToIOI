#include <bits/stdc++.h>
using namespace std;
const int INFF = 2e9+99;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef vector<int> vint;

vector<ll> calculate_costs(vint W, vint A, vint B, vint E) {
    int n = (int)W.size();
    int q = (int)E.size();
    vector<ll> R;
    
    sort(W.begin(), W.end());
    W.push_back(INFF);
    for (int Q: E){
        ll ans = 0;
        for (int i = 0; i < n; ){
            if (W[i+1]-W[i] <= Q){
                ans += 2;
                i += 2;
            } else {
                ans += 2;
                i++;
            }
        }
        R.push_back(ans);
    }

    return R;
}
