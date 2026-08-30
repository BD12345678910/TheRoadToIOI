/*
Do these in order:

Full lazy dynamic segment tree.
kth order statistic on [1, 10^9]
Merge?
Maintain min and count?

*/

/*
Furthermore, how to calculate MAXNODES?

Recall that at most 2H partials and 2H contained:
Hence roughly H = log2(RANGE) = 30
Maxnodes <= 4HQ = 4*200000*30 = 24e6!
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e9;
const int MAXNODE = 24000000;
ll t[MAXNODE], lz[MAXNODE];
int lc[MAXNODE], rc[MAXNODE], cnt;

// not very useful here, but extendable
int newNode(){
	int nx = ++cnt;
	lz[nx] = 0;
	t[nx] = 0;
	lc[nx] = rc[nx] = 0;
	return nx;
}

int push_down(int x, int l, int r){
	int mid = (l+r)>>1;
	if (!lz[x]) return mid;
	
	if (!lc[x]) lc[x] = ++cnt;
	lz[lc[x]] += lz[x];
	t[lc[x]] += lz[x]*(mid-l+1);

	if (!rc[x]) rc[x] = ++cnt;
	lz[rc[x]] += lz[x];
	t[rc[x]] += lz[x]*(r-mid);

	lz[x] = 0;
	return mid;
}

void update(int &x, int l, int r, int ql, int qr, ll v){
	if (!x) x = newNode();
	if (ql <= l && r <= qr){
		t[x] += v*(r-l+1);
		lz[x] += v;
		return;
	}
	int mid = push_down(x, l, r);
	if (ql <= mid) update(lc[x], l, mid, ql, qr, v);
	if (qr > mid) update(rc[x], mid+1, r, ql, qr, v);
	t[x] = t[lc[x]]+t[rc[x]];
}

ll query(int x, int l, int r, int ql, int qr){
	if (!x || qr < l || ql > r) return 0;
	if (ql <= l && r <= qr) return t[x];
	int mid = push_down(x, l, r);
	return query(lc[x], l, mid, ql, qr)+query(rc[x], mid+1, r, ql, qr);
}

int main(){
	int q, rt = 0; cin >> q;
	while (q--){
		int op, l, r; cin >> op >> l >> r;
		if (op == 1){
			int v; cin >> v;
			update(rt, 1, N, l, r, v);
		} else {
			cout << query(rt, 1, N, l, r) << '\n';
		}
	}
	return 0;
}




