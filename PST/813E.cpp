// query [l, r]: 
// for each type we take the leftmost at most k...
// when x in [l, r]:
// this means lastk[x] < l for x to be included

#include <bits/stdc++.h>
using namespace std;

int n, k;
int a[100005];
vector<int> occur[100005];
int p[100005];
int t[2000005], lc[2000005], rc[2000005], cnt;
int root[100005];

int update(int x, int l, int r, int q, int v){
	int nx = ++cnt;
	t[nx] = t[x];
	lc[nx] = lc[x];
	rc[nx] = rc[x];
	if (l == r){
		t[nx] += v;
		return nx;
	}
	int mid = (l+r)>>1;
	if (q <= mid) lc[nx] = update(lc[x], l, mid, q, v);
	if (q > mid) rc[nx] = update(rc[x], mid+1, r, q, v);
	t[nx] = t[lc[nx]]+t[rc[nx]];
	return nx;
}

int query(int x, int l, int r, int ql, int qr){
	if (!x || ql > r || qr < l) return 0;
	if (ql <= l && r <= qr) return t[x];
	int mid = (l+r)>>1;
	return query(lc[x], l, mid, ql, qr)+query(rc[x], mid+1, r, ql, qr);
}

int main(){
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if ((int)occur[a[i]].size() >= k){
			p[i] = occur[a[i]][(int)occur[a[i]].size()-k];
		}
		occur[a[i]].push_back(i);
	}
	// for (int i = 1; i <= n; i++){
	// 	cout << p[i] << endl;
	// }
	for (int i = 1; i <= n; i++){
		root[i] = update(root[i-1], 0, n, p[i], 1);
	}
	int q; cin >> q; int last = 0;
	while (q--){
		int l, r; cin >> l >> r;
		l = (l+last) % n + 1;
		r = (r+last) % n + 1;
		if (l > r) swap(l, r);
		last = query(root[r], 0, n, 0, l-1) - query(root[l-1], 0, n, 0, l-1);
		cout << last << '\n';
	}
	return 0;
}

