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
            s = s-res.second-1;
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
            // consider: we know everything after including i+1
            // we find the previous j for which we know an equation
            // starting from j, eliminate the stuff after including i+1
            // and obtain an equation with only the elements of 
            // (j, i] = s
            int j;
            for (j = i-1; j >= 0; j--){
                if (memo[j].second != -1) break;
            }
            // preprocesses j away
            s = memo[j].second;
            int k = 0;
            for (int v : memo[j].first){
                if (v > i) s -= p[v];
                else k++;
            }
            if (k == 1){
                s--;
            } else {
                s = s/k;
            }
            while (1){
                res = transaction(s);
                memo[res.first[0]] = {res.first, s-res.second};
                s -= res.second;
                k = 0;
                for (int v : res.first){
                    cnt[v]++;
                    if (v > i) s -= p[v];
                    else k++;
                }
                if (k == 1){
                    s--;
                    if (res.first[0] == i) break;
                } else {
                    s = s/k;
                }
            }
            // finally, s+1 is p[i]
            p[i] = s+1;
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
