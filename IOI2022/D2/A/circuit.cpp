#include "circuit.h"
#include <bits/stdc++.h>
typedef long long ll;
const ll MOD = 1000002022;
using namespace std;

int n, m;
vector<int> T[200005];
ll W[200005];
ll coeff[200005];
ll sz[200005];

void calc_sz(int x){
    sz[x] = 1;
    int cnt = 0;
    for (int v : T[x]){
        cnt++;
        calc_sz(v);
        sz[x] = sz[x] * sz[v] % MOD;
    }
    if (cnt > 0) 
    sz[x] = sz[x] * cnt % MOD;
}

void calc_coeff(int x, ll P){
    if (x >= n){
        coeff[x] = P;
        return;
    }
    int s = T[x].size();
    ll suma = 1;
    vector<ll> leftt, rightt;
    for (int i = 0; i < s; i++){
        suma = suma * sz[T[x][i]] % MOD;
        leftt.push_back(suma);
    }
    suma = 1;
    for (int i = s-1; i >= 0; i--){
        suma = suma * sz[T[x][i]] % MOD;
        rightt.push_back(suma);
    }
    reverse(rightt.begin(), rightt.end());
    for (int i = 0; i < s; i++){
        ll curr = P;
        if (i > 0) curr = curr*leftt[i-1]%MOD;
        if (i < s-1) curr = curr*rightt[i+1]%MOD;
        calc_coeff(T[x][i], curr);
    }
}

ll csum[400005], t[400005];
bool flip[400005];

void build(int x, int l, int r, vector<int> &a){
    if (l == r){
        csum[x] = coeff[l+n];
        if (a[l]) t[x] = csum[x];
        else t[x] = 0;
        return;
    }
    int mid = (l+r)>>1;
    build(x<<1, l, mid, a);
    build(x<<1|1, mid+1, r, a);
    csum[x] = (csum[x<<1]+csum[x<<1|1])%MOD;
    t[x] = (t[x<<1]+t[x<<1|1])%MOD;
}

void init(int N, int M, vector<int> P, vector<int> A){ 
    n = N, m = M;
    for (int i = 1; i < N+M; i++){
        T[P[i]].push_back(i);
    }
    calc_sz(0);
    calc_coeff(0, 1);
    build(1, 0, M, A);
}

int down(int x, int l, int r){
    int mid = (l+r)>>1;
    if (flip[x]){
        flip[x<<1] ^= 1;
        t[x<<1] = (csum[x<<1]-t[x<<1]+MOD)%MOD;
        flip[x<<1|1] ^= 1;
        t[x<<1|1] = (csum[x<<1|1]-t[x<<1|1]+MOD)%MOD;
        flip[x] = 0;
    }
    return mid;
}

void toggle(int x, int l, int r, int ql, int qr){
    if (ql <= l && r <= qr){
        flip[x] ^= 1;
        t[x] = (csum[x]-t[x]+MOD)%MOD;
        return;
    }
    int mid = down(x, l, r);
    if (ql <= mid) toggle(x<<1, l, mid, ql, qr);
    if (qr > mid) toggle(x<<1|1, mid+1, r, ql, qr);
    t[x] = (t[x<<1] + t[x<<1|1]) % MOD;
}

int count_ways(int L, int R) {
    toggle(1, 0, m, L-n, R-n);
    return t[1];
}

