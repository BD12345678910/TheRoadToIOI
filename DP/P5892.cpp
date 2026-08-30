// great problem about PST and DP optimization

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, s, d, c;
int a[200005], b[200005], tmp[200005];

int rt[200005], cnt;
int lc[8000005], rc[8000005], t[8000005];
ll st[8000005];
ll gans;

int update(int x, int l, int r, int q){
	int nx = ++cnt;
	lc[nx] = lc[x]; rc[nx] = rc[x];
	t[nx] = t[x]; st[nx] = st[x];
	if (l == r){
		t[nx]++;
		st[nx] += b[l];
		return nx;
	}
	int mid = (l+r)>>1;
	if (q <= mid){
		lc[nx] = update(lc[x], l, mid, q);
	} else {
		rc[nx] = update(rc[x], mid+1, r, q);
	}
	t[nx] = t[lc[nx]]+t[rc[nx]];
	st[nx] = st[lc[nx]]+st[rc[nx]];
	return nx;
}	

ll ktop(int x, int y, int l, int r, int k){
	if (k >= t[x]-t[y]) return st[x]-st[y];
	if (l == r) return 1LL*k*b[l];
	int mid = (l+r)>>1;
	if (t[rc[x]]-t[rc[y]] >= k){
		return ktop(rc[x], rc[y], mid+1, r, k);
	} else {
		return st[rc[x]]-st[rc[y]]+
		ktop(lc[x], lc[y], l, mid, k-(t[rc[x]]-t[rc[y]]));
	}
}

void solve(int l, int r, int ql, int qr){
	if (l > r) return;
	int mid = (l+r)>>1;
	int opt = qr; ll rec = -1;
	for (int x = ql; x <= qr; x++){
		// query [x, mid]
		int move = s-x+mid-x;
		int rem = d-move;
		if (rem < 0) continue;
		ll res = ktop(rt[mid], rt[x-1], 1, c, rem);
		if (res > rec){
			rec = res;
			opt = x;
		}
	}
	if (rec >= 0){
		gans = max(rec, gans);
		solve(l, mid-1, ql, opt);
		solve(mid+1, r, opt, qr);
	} else {
		solve(l, mid-1, ql, opt);
	}
	
}

void solve(){
	// build persistent segment tree:
	for (int i = 1; i <= n; i++){
		rt[i] = update(rt[i-1], 1, c, a[i]);
	}
	solve(s, n, 1, s);
}

int main(){
	cin >> n >> s >> d; s++;
	for (int i = 1; i <= n; i++){
		cin >> a[i]; b[i] = a[i];
	}
	sort(b+1, b+n+1); c = unique(b+1, b+n+1)-b-1;
	for (int i = 1; i <= n; i++){
		a[i] = lower_bound(b+1, b+c+1, a[i])-b;
	}
	gans = 0;
	solve();
	reverse(a+1, a+n+1); s = n+1-s;
	for (int i = 1; i <= n; i++) rt[i] = 0;
	cnt = 0;
	solve();
	cout << gans << endl;
	return 0;
}