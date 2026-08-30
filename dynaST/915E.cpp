#include <bits/stdc++.h>
using namespace std;

int n, q;

int cnt, root;
int lazy[15000000];
int t[15000000];
int lc[15000000], rc[15000000];

int push_down(int x, int l, int r){
	int mid = (l+r)>>1;
	if (lazy[x] == -1){
		if (!lc[x]) lc[x] = ++cnt;
		lazy[lc[x]] = -1;
		t[lc[x]] = 0;
		if (!rc[x]) rc[x] = ++cnt;
		lazy[rc[x]] = -1;
		t[rc[x]] = 0;
	} else if (lazy[x] == 1) {
		if (!lc[x]) lc[x] = ++cnt;
		lazy[lc[x]] = 1;
		t[lc[x]] = mid-l+1;
		if (!rc[x]) rc[x] = ++cnt;
		lazy[rc[x]] = 1;
		t[rc[x]] = r-mid;
	}
	lazy[x] = 0;
	return mid;
}

void update(int &x, int l, int r, int ql, int qr, int md){
	if (!x) x = ++cnt;
	if (ql <= l && r <= qr){
		if (md == 1){
			lazy[x] = -1;
			t[x] = 0;
		} else if (md == 2){
			lazy[x] = 1;
			t[x] = (r-l+1);
		}
		return;
	}
	int mid = push_down(x, l, r);
	if (ql <= mid) update(lc[x], l, mid, ql, qr, md);
	if (qr > mid) update(rc[x], mid+1, r, ql, qr, md);
	t[x] = t[lc[x]]+t[rc[x]];
	return;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	cin >> q;
	update(root, 1, n, 1, n, 2);
	while (q--){
		int l, r, k; cin >> l >> r >> k;
		update(root, 1, n, l, r, k);
		cout << t[1] << '\n';
	}
	return 0;
}




