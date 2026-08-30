#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vint;
const int INF = 2e9;

pair<int,pair<int,int>> P[100005];
pair<int,int> Query[100005];
pair<int,pair<int,int>> gap[200005]; int cnt;
int diff[100005], fa[100005], oddmn[100005], evenmn[100005];
int special[100005], sz[100005], cans[100005];
ll ans[100005], tans;
int find(int x){
    if (fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}

vector<ll> calculate_costs(vint W, vint A, vint B, vint E) {
    int n = (int)W.size(), q = (int)E.size();
    for (int i = 0; i < n; i++){
        P[i+1] = {W[i], {A[i], B[i]}};
        tans += B[i];
    }
    for (int i = 0; i < q; i++) Query[i+1] = {E[i], i};
    sort(P+1, P+n+1); sort(Query+1, Query+q+1);
    for (int i = 1; i <= n; i++) 
        diff[i] = P[i].second.first-P[i].second.second;
    for (int i = 1; i < n; i++)
        gap[++cnt] = {P[i+1].first-P[i].first, {i, i+1}};
    for (int i = 1; i < n-1; i++)
        gap[++cnt] = {P[i+2].first-P[i].first, {i, i+2}};
    sort(gap+1, gap+cnt+1);

    for (int i = 1; i <= n; i++){
        fa[i] = i; cans[i] = diff[i]; sz[i] = 1;
        tans += cans[i];
        oddmn[i] = evenmn[i] = special[i] = INF;
        if (i % 2) oddmn[i] = diff[i];
        else evenmn[i] = diff[i];
    }  

    int curr = 1;
    for (int i = 1; i <= q; i++){
        int Q = Query[i].first;
        while (curr <= cnt && gap[curr].first <= Q){
            int x = gap[curr].second.first;
            int y = gap[curr].second.second;
            if (x+1==y){
                // combine components:
                x = find(x); y = find(y);
                sz[x] += sz[y];
                fa[y] = x;
                oddmn[x] = min(oddmn[x], oddmn[y]);
                evenmn[x] = min(evenmn[x], evenmn[y]);
                special[x] = min(special[x], special[y]);
                tans -= cans[x];
                tans -= cans[y];
                if (sz[x] % 2){
                    if (x % 2) cans[x] = oddmn[x];
                    else cans[x] = evenmn[x];
                    cans[x] = min(cans[x], special[x]);
                } else {
                    cans[x] = 0;
                }
                tans += cans[x];
            } else {
                x = find(x); 
                special[x] = min(special[x], diff[y-1]);
                tans -= cans[x];
                cans[x] = min(cans[x], special[x]);
                tans += cans[x];
            }
            curr++;
        }
        ans[Query[i].second] = tans;
    }

    vector<ll> R(ans, ans+q);
    return R;
}




