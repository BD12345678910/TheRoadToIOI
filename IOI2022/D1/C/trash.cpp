#include "towers.h"
#include <bits/stdc++.h>
using namespace std;
const int NINF = -6e5;
int n;
vector<int> h;
int dp[100005];

void init(int N, vector<int> H) {
    n = N; h = H;
}

// Property 1: if A<B<C and A to B and B to C, then A to C

int p[100005], tp;
priority_queue<int> wait[100005];
int best[100005];
int hh[100005];

int max_towers(int L, int R, int D) {
    dp[L] = 0;
    p[++tp] = L; hh[tp] = -h[L];
    best[tp] = NINF;
    for (int i = L+1; i <= R; i++){
        int start = tp;
        int tmpbest = -1;
        while (tp && h[i] > p[tp]) {
            if (tmpbest == -1 || dp[tmpbest] < dp[best[tp]]){
                tmpbest = best[tp];
            }
            tp--; 
        }
        for (int j = start; j > tp+1; j--){
            if (wait[j].size() < wait[j-1].size()){
                for (auto x: wait[j]){
                    wait[j-1].push(x);
                }
            } else {
                for (auto x: wait[j-1]){
                    wait[j].push(x);
                }
                swap(wait[j], wait[j-1]);
            }
        }
        p[++tp] = i;
        hh[tp] = -h[i];
        while (!wait[tp].empty()){
            auto [hv, v] = wait[tp].top();
            if (hv + D <= h[i]){
                if (dp[best[tp]] < dp[v]) 
                    best[tp] = v;
                wait[tp].pop();
            } else {
                break;
            }
        }
        if (tp > 1 && dp[best[tp-1]] > dp[best[tp]]) best[tp] = best[tp-1];
        int idx = 
    }
}



