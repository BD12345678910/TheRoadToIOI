#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int N = 300005;
const int NODE = 6200000;
int n;
int a[N];
int root[N];
int t[NODE], lc[NODE], rc[NODE], cnt;

int update(int x, int l, int r, int q){
	int nx = ++cnt;
	lc[nx] = lc[x];
	rc[nx] = rc[x];
	t[nx] = t[x];
	if (l == r){
		t[nx]++;
		return nx;
	}
	int mid = (l+r)>>1;
	if (q <= mid) lc[nx] = update(lc[x], l, mid, q);
	else rc[nx] = update(rc[x], mid+1, r, q);
	t[nx] = t[lc[nx]]+t[rc[nx]];
	return nx;
}

int query(int x, int y, int l, int r, int f){
	if (l == r){
		return l;
	}
	int mid = (l+r)>>1;
	int ret = INF;
	if (t[lc[x]]-t[lc[y]] >= f){
		ret = min(ret, query(lc[x], lc[y], l, mid, f));
	} 
	if (t[rc[x]]-t[rc[y]] >= f){
		ret = min(ret, query(rc[x], rc[y], mid+1, r, f));
	}
	return ret;
}

int main(){
	int q;
	cin >> n >> q; t[0] = 0;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++){
		root[i] = update(root[i-1], 1, n, a[i]);
	}
	while (q--){
		int l, r, k; cin >> l >> r >> k;
		int want;
		if ((r-l+1)%k==0) want = (r-l+1)/k+1;
		else want = (r-l+1+k)/k;
		int ret = query(root[r], root[l-1], 1, n, want);
		if (ret == INF) ret = -1;
		cout << ret << '\n';
	}
	return 0;
}

