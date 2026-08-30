#include "souvenirs.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<vector<int>, ll> res;
int cnt[103];
ll p[103];
pair<vector<int>, ll> memo[103];

void buy_souvenirs(int N, long long P0) {
    for (int i = 0; i < N; i++){
        cnt[i] = 0;
        p[i] = 0;
        memo[i].first.clear(); memo[i].second = -1;
    }
    p[0] = P0;
    ll s = p[0]-1;
    while (1){
        res = transaction(s);
        for (int v : res.first){
            cnt[v]++;
        }
        memo[res.first[0]] = {res.first, s-res.second};
        // ensure that the next one moves on
        int k = res.first.size();
        if (k == 1){
            s = s - res.second - 1;
            if (res.first[0] == N-1) break;
        } else {
            s = (s-res.second)/k;
        }
    }
    // s+1 is the cost p[n-1]...
    p[N-1] = s+1;
    // when i do 2p_{i+1}, p_{i-1} cannot be chosen and p_i must be chosen
    for (int i = N-2; i >= 1; i--){
        if (memo[i].second != -1){
            // directly find the answer from memo:
            s = memo[i].second;
            for (int v : memo[i].first){
                s -= p[v];
            }
            p[i] = s;
        } else {
            res = transaction(2*p[i+1]);
            s = 2*p[i+1] - res.second;
            for (int v : res.first){
                cnt[v]++;
                s -= p[v];
            }
            p[i] = s;
        }
    }

    for (int i = 1; i < N; i++){
        while (cnt[i] < i){
            transaction(p[i]);
            cnt[i]++;
        }
    }

    return;
}
