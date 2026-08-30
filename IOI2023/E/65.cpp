#include "overtaking.h"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m;
vector<int> w;
vector<ll> bd[1005], rec[1005];
ll t[1005][1005];
int s[1005];

void init(int LL, int N, vector<ll> T, vector<int> WW, 
    int XX, int MM, vector<int> SS){
    n = N; m = MM; w = WW; w.push_back(XX);
    for (int i = 0; i < m; i++){
        s[i] = SS[i];
    }
    for (int i = 0; i < n; i++){
        t[0][i] = T[i];
    }
    for (int i = 1; i <= m-1; i++){
        vector<ll> times;
        map<ll, vector<pair<ll,int>>> M;
        vector<ll> slow;
        map<ll, vector<pair<ll,int>>> M2;
        for (int j = 0; j < n; j++){
            ll tt = t[i-1][j]+1LL*(s[i]-s[i-1])*w[j];
            times.push_back(t[i-1][j]);
            M[t[i-1][j]].push_back({tt, j});
            if (w[j] > w[n]){
                slow.push_back(t[i-1][j]);
                M2[t[i-1][j]].push_back({tt, j});
            }
        }
        sort(times.begin(), times.end());
        times.resize(unique(times.begin(), times.end())-times.begin());
        sort(slow.begin(), slow.end());
        slow.resize(unique(slow.begin(), slow.end())-slow.begin());
        ll mx = 0, smx = 0;
        for (ll ttt : times){
            for (auto [tt, j]: M[ttt]){
                t[i][j] = max(mx, tt);
            }
            for (auto [tt, j]: M[ttt]){
                mx = max(mx, tt);
            }
        }
        for (ll ttt: slow){
            for (auto [tt, j]: M2[ttt]){
                if (w[j] > w[n]) smx = max(smx, tt);
            }
            bd[i].push_back(ttt);
            rec[i].push_back(smx);
        }
    }
    return;
}

ll arrival_time(ll Y)
{
    ll T = Y;
    for (int i = 1; i <= m-1; i++){
        ll mytime = T+1LL*(s[i]-s[i-1])*w[n];
        int idx = lower_bound(bd[i].begin(), bd[i].end(), T)-bd[i].begin()-1;
        if (idx >= 0) T = max(mytime, rec[i][idx]);
        else T = mytime;
    }
    return T;
}


