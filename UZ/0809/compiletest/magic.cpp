#include "magic.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> Amina(vector<int> P) {
    int n = (int) P.size();
    vector<int> dp(n, 1);
    vector<int> last(n, 0);
    vector<int> ret = P;
    int rec = 0;
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            if (P[j] < P[i] && dp[j]+1 > dp[i]){
                dp[i] = dp[j]+1;
                last[i] = j;
            }
        }
        if (dp[i] > dp[rec]) rec = i;
    }
    if (dp[rec] >= 16){
        int curr = rec;
        for (int i = 1; i <= 16; i++){
            ret[curr] = -1;
            curr = last[curr];
        }
    } else {
        fill(dp.begin(), dp.end(), 1);
        rec = 0;
        for (int i = 1; i < n; i++){
            for (int j = 0; j < i; j++){
                if (P[j] > P[i] && dp[j]+1 > dp[i]){
                    dp[i] = dp[j]+1;
                    last[i] = j;
                }
            }
            if (dp[i] > dp[rec]) rec = i;
        }
        int curr = rec;
        for (int i = 1; i <= 17; i++){
            ret[curr] = -1;
            curr = last[curr];
        }
    }
    cerr << "ADONE" << endl;
    return ret;
}

vector<int> Billura(vector<int> Q) {
    int n = (int)Q.size();
    vector<bool> taken(n+1, 0);
    vector<int> pos, val;
    for (int i = 0; i < n; i++){
        if (Q[i] == -1) pos.push_back(i);
        else taken[Q[i]] = 1;
    }
    for (int i = 1; i <= n; i++){
        if (!taken[i]){
            val.push_back(i);
        }
    }
    if (pos.size() == 17){
        reverse(val.begin(), val.end());
    } 
    for (int i = 0; i < (int)val.size(); i++){
        Q[pos[i]] = val[i];
    }
    return Q;
}
