#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, cnt;
int L[400005], R[400005];
int rt[400005];
ll tans, ans = 0;
int t[4000006], cc;
int lc[4000006], rc[4000006];

void update(int &x, int l, int r, int q){
	if (!x) x = ++cc;
	if (l == r) {
		t[x] = 1;
		return;
	}
	int mid = (l+r)>>1;
	if (q <= mid) update(lc[x], l, mid, q);
	else update(rc[x], mid+1, r, q);
	t[x] = t[lc[x]]+t[rc[x]];
}

int merge(int x, int y, int l, int r){
	if (!x || !y) return x|y;
	int mid = (l+r)>>1;
	tans += 1LL*t[rc[x]]*t[lc[y]];
	lc[x] = merge(lc[x], lc[y], l, mid);
	rc[x] = merge(rc[x], rc[y], mid+1, r);
	t[x] = t[lc[x]]+t[rc[x]];
	return x;
}

void dfs(int x){
	if (!L[x]&&!R[x]){
		update(rt[x], 1, n, x);
		return;
	}
	dfs(L[x]); dfs(R[x]);
	int a = t[rt[L[x]]], b = t[rt[R[x]]];
	tans = 0;
	rt[x] = merge(rt[L[x]], rt[R[x]], 1, n);
	ans += min(tans, 1LL*a*b-tans);
}

void build(int &x){
	int tmp; cin >> tmp;
	if (tmp) x = tmp;
	else {
		x = ++cnt;
		build(L[x]);
		build(R[x]);
	}
}

int main(){
	cin >> n; cnt = n;
	int root; build(root);
	dfs(root);
	cout << ans << endl;
	return 0;
}

