#include <bits/stdc++.h>
using namespace std;
const int INFF = 2e9+99;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef vector<int> vint;

int fa[100005], sz[100005];
int find(int x){
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
int tans[100005];

vector<ll> calculate_costs(vint W, vint A, vint B, vint E) {
    int n = (int)W.size();
    int q = (int)E.size();
    vector<ll> R;
    
    sort(W.begin(), W.end());
    vector<pair<int,int>> gaps;
    for (int i = 0; i < n-1; i++){
        gaps.push_back({W[i+1]-W[i], i});
    }
    sort(gaps.begin(), gaps.end());
    for (int i = 0; i < n; i++) fa[i] = i, sz[i] = 1;

    vector<pair<int,int>> queries; int cnt = 0;
    for (int Q: E){
        queries.push_back({Q, cnt++});
    }  
    sort(queries.begin(), queries.end());
    int curr = 0;
    ll ans = 2*n;
    for (int i = 0; i < cnt; i++){
        while (curr < n && gaps[curr].first <= queries[i].first){
            // combine 
            int y = find(gaps[curr].second+1);
            int x = find(gaps[curr].second);
            ans -= (sz[x]+1)/2*2;
            ans -= (sz[y]+1)/2*2;
            fa[y] = x;
            sz[x] += sz[y];
            ans += (sz[x]+1)/2*2;
            curr++;
        }
        tans[queries[i].second] = ans;
    }

    for (int i = 0; i < q; i++){
        R.push_back(tans[i]);
    }

    return R;
}




