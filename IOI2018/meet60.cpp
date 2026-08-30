// consider the merging of segments
// dp[a][b](segment)
// = best cost to have a as max to the left and 
// b as max to the right of the chosen point
// notice a or b = max(segment)

#include <bits/stdc++.h>
using namespace std;

int n, q;
int a[100005];
const int INF = 0x3f3f3f3f;

struct node{
	int mx;
	int pre[21], suf[21];
	// cost[i][mx] and cost[mx][i]
	int L[21], R[21];
	node(){
		mx = 0;
		for (int i = 0; i <= 20; i++){
			L[i] = R[i] = INF;
			pre[i] = suf[i] = INF;
		}
	}
	node(int x){
		mx = a[x];
		for (int i = 0; i <= 20; i++){
			L[i] = R[i] = INF;
			pre[i] = suf[i] = INF;
		}
		L[a[x]] = R[a[x]] = a[x]; 
		for (int i = 1; i <= 20; i++){ 
			pre[i] = suf[i] = max(i, a[x]); 
		}
	}
} t[400005];

void put(node& A, int hL, int hR, int val){
	if (hR == A.mx) A.L[hL] = min(A.L[hL], val);
	if (hL == A.mx) A.R[hR] = min(A.R[hR], val);
}

int find_min(const node& A){
	int ans = INF;
	for (int i = 1; i <= 20; i++){
		ans = min(ans, A.L[i]);
		ans = min(ans, A.R[i]);
	}
	return ans;
}

node merge(const node& A, const node& B){
	node C = node(); C.mx = max(A.mx, B.mx);
	for (int h = 1; h <= 20; h++){
		C.pre[h] = A.pre[h] + B.pre[max(h, A.mx)];
		C.suf[h] = A.suf[max(h, B.mx)] + B.suf[h];
	}
	// pivot inside A: 
	for (int h = 1; h <= 20; h++){
		if (A.L[h] != INF){
			put(C, h, C.mx, A.L[h]+B.pre[A.mx]);
		}
		if (A.R[h] != INF){
			put(C, A.mx, max(h, B.mx), A.R[h]+B.pre[h]);
		}
	}
	// pivot inside B:
	for (int h = 1; h <= 20; h++){
		if (B.L[h] != INF){
			put(C, max(A.mx, h), B.mx, A.suf[h]+B.L[h]);
		}
		if (B.R[h] != INF){
			put(C, C.mx, h, A.suf[B.mx]+B.R[h]);
		}
	}
	return C;
}

void build(int x, int l, int r){
	if (l == r){
		t[x] = node(l);
		return;
	}
	int mid = (l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x] = merge(t[x<<1], t[x<<1|1]);
}

node query(int x, int l, int r, int ql, int qr){
	if (ql <= l && r <= qr){
		return t[x];
	}
	int mid = (l+r)>>1;
	node ret; bool alr = 0;
	if (ql <= mid) ret = query(x<<1, l, mid, ql, qr), alr = 1;
	if (qr > mid){
		if (alr) ret = merge(ret, query(x<<1|1, mid+1, r, ql, qr));
		else ret = query(x<<1|1, mid+1, r, ql, qr);
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	build(1, 1, n);
	while (q--){
		int l, r; cin >> l >> r; l++, r++;
		cout << find_min(query(1, 1, n, l, r)) << '\n';
	} 
	return 0;
}