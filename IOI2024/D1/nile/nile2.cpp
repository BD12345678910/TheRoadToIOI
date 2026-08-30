#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef vector<int> vint;

vector<ll> calculate_costs(vint W, vint A, vint B, vint E) {
    int n = (int)W.size();
    int q = (int)E.size();
    vector<long long> R;

    ll asum = 0, bsum = 0;
    for (int i = 0; i < n; i++){
        asum += A[i];
        bsum += B[i];
    }

    for (int Q : E){
        if (Q == 0){
            R.push_back(asum);
        }
        else if (Q == 1){
            if (n % 2 == 0) {
                R.push_back(bsum);
            } else {
                int diff = INF;
                for (int i = 2; i <= n-3; i += 2){
                    diff = min(diff, A[i]-B[i]);
                }
                R.push_back(bsum + diff);
            }
        }
        else if (Q >= 2){
            if (n % 2 == 0){
                R.push_back(bsum);
            } else {
                int diff = INF;
                for (int i = 0; i < n; i++){
                    diff = min(diff, A[i]-B[i]);
                }
                R.push_back(bsum+diff);
            }
        }
    }
    return R;
}
