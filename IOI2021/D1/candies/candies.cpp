// #include "candies.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,long long> pil;
// segment tree that supports:
// suffix maximum, suffix minimum
// range add
// point query
const ll INF = 1e18;
pil mn[800006], mx[800006];
ll su[800006], lz[800006];

pil mmn(pil y, pil z){
    if (y.second < z.second) return y;
    else return z;
}

pil mmx(pil y, pil z){
    if (y.second > z.second) return y;
    else return z;
}

void pull(int x){
    mn[x] = mmn(mn[x<<1], mn[x<<1|1]);
    mx[x] = mmx(mx[x<<1], mx[x<<1|1]);
    su[x] = su[x<<1]+su[x<<1|1];
}

void build(int x, int l, int r){
    if (l == r){
        mn[x] = {l, 0};
        mx[x] = {l, 0};
        su[x] = 0;
        lz[x] = 0;
        return;
    }
    int mid = (l+r)>>1;
    build(x<<1, l, mid);
    build(x<<1|1, mid+1, r);
    pull(x);
}

int push(int x, int l, int r){
    int mid = (l+r)>>1;
    if (lz[x]){
        lz[x<<1] += lz[x];
        lz[x<<1|1] += lz[x];
        mn[x<<1].second += lz[x];
        mn[x<<1|1].second += lz[x];
        mx[x<<1].second += lz[x];
        mx[x<<1|1].second += lz[x];
        su[x<<1] += lz[x] * (mid-l+1);
        su[x<<1|1] += lz[x] * (r-mid);
        lz[x] = 0;
    }
    return mid;
}

void update(int x, int l, int r, int ql, int qr, int v){
    if (ql <= l && r <= qr){
        lz[x] += v;
        mn[x].second += v;
        mx[x].second += v;
        su[x] += 1LL*(r-l+1)*v;
        return;
    }
    int mid = push(x, l, r);
    if (ql <= mid) update(x<<1, l, mid, ql, qr, v);
    if (qr > mid) update(x<<1|1, mid+1, r, ql, qr, v);
    pull(x);
}

ll point(int x, int l, int r, int q){
    if (l == r) return mn[x].second;
    int mid = push(x, l, r);
    if (q <= mid) return point(x<<1,l,mid,q);
    else return point(x<<1|1,mid+1,r,q);
}

pil querymn(int x, int l, int r, int ql, int qr){
    if (qr < l || r < ql) return {0, INF};
    if (ql <= l && r <= qr) return mn[x];
    int mid = push(x, l, r);
    return mmn(querymn(x<<1, l, mid, ql, qr),
        querymn(x<<1|1, mid+1, r, ql, qr));
}

pil querymx(int x, int l, int r, int ql, int qr){
    if (qr < l || r < ql) return {0, -INF};
    if (ql <= l && r <= qr) return mx[x];
    int mid = push(x, l, r);
    return mmx(querymx(x<<1, l, mid, ql, qr),
        querymx(x<<1|1, mid+1, r, ql, qr));
}

vector<pair<int,int>> event[200005];
ll ans[200005];
vector<int> distribute_candies(vector<int> C, vector<int> L,
    vector<int> R, vector<int> V) {
    int n = C.size();
    int q = L.size();

    build(1, 0, q);  
    for (int i = 0; i < q; i++){
        event[L[i]+1].push_back({i+1, V[i]});
        event[R[i]+2].push_back({i+1, -V[i]});
    }
    
    for (int i = 1; i <= n; i++){
        for (auto [where, v]: event[i]){
            // range update add v;
            update(1, 0, q, where, q, v);
        }
        ll endpunkt = point(1, 0, q, q);
        ll c = C[i-1];
        if (querymx(1, 0, q, 0, q).second - querymn(1, 0, q, 0, q).second < c){
            ans[i] = endpunkt - querymn(1, 0, q, 0, q).second;
        } else {
            int l = 0, r = q, pos = -1;
            while (l <= r){
                int mid = (l+r)>>1;
                if (querymx(1, 0, q, mid, q).second - querymn(1, 0, q, mid, q).second >= c){
                    l = mid+1;
                    pos = mid;
                } else {
                    r = mid-1;
                }
            } 
            pil minimum = querymn(1, 0, q, pos, q);
            pil maximum = querymx(1, 0, q, pos, q);
            // cout << point(1,0,q,0) << point(1,0,q,1) << point(1,0,q,2) << endl;
            // cout << pos << ' ' << minimum.first << ' ' << maximum.first << endl;
            if (minimum.first < maximum.first){
                ans[i] = c + endpunkt - maximum.second;
            } else {
                ans[i] = endpunkt - minimum.second;
            }
        }
    }

    return vector<int>(ans+1, ans+1+n);
}


