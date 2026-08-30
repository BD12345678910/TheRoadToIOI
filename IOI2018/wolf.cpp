#include <bits/stdc++.h>
using namespace std;

int n, m, Q;
vector<int> G[200005];

struct Tree{
	int _f[200005];
	int find(int x){
		if (_f[x]==x) return x;
		else return _f[x] = find(_f[x]);
	}

	vector<int> GG[200005];
	int fa[200005][19];
	int dfn[200005], out[200005];
	int rev[200005];
	int cnt;

	void dfs(int x){
		dfn[x] = ++cnt;
		rev[cnt] = x;
		for (int i = 1; i <= 17; i++){
			fa[x][i] = fa[fa[x][i-1]][i-1];
		}
		for (int v : GG[x]){
			dfs(v);
		}
		out[x] = cnt;
	}
	void traverse(){
		for (int i = 1; i <= n; i++){
			if (fa[i][0] == i) dfs(i);
		}
	}
} L, R;

int rt[200005];
int t[8000006], lc[8000006], rc[8000006];
int cn;

int update(int x, int l, int r, int q){
	int nx = ++cn;
	lc[nx] = lc[x], rc[nx] = rc[x];
	t[nx] = t[x];
	if (l == r){
		t[nx]++;
		return nx;
	}
	int mid = (l+r)>>1;
	if (q <= mid) 	lc[nx] = update(lc[x], l, mid, q);
	else 			rc[nx] = update(rc[x], mid+1, r, q);
	t[nx] = t[lc[nx]]+t[rc[nx]];
	return nx;
}

int query(int x, int l, int r, int ql, int qr){
	if (ql > r || qr < l) return 0;
	if (ql <= l && r <= qr) return t[x];
	int mid = (l+r)>>1;
	return query(lc[x], l, mid, ql, qr)+query(rc[x], mid+1, r, ql, qr);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> Q;
	for (int i = 1; i <= n; i++){
		L._f[i] = R._f[i] = i;
	}
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		a++; b++;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	
	// connect backward: L
	for (int i = 1; i <= n; i++){
		for (int v : G[i]){
			if (v < i){
				int x = L.find(v), y = L.find(i);
				if (x != y){
					if (x > y) swap(x, y);
					L._f[x] = y;
					L.fa[x][0] = y;
				}
			}
		}
	}

	// connect forward: R
	for (int i = n; i >= 1; i--){
		for (int v : G[i]){
			if (v > i){
				int x = R.find(v), y = R.find(i);
				if (x != y){
					if (x < y) swap(x, y);
					R._f[x] = y;
					R.fa[x][0] = y;
				}
			}
		}
	}

	for (int i = 1; i <= n; i++){
		if (L.fa[i][0]) L.GG[L.fa[i][0]].push_back(i);
		else L.fa[i][0] = i;
		if (R.fa[i][0]) R.GG[R.fa[i][0]].push_back(i);
		else R.fa[i][0] = i;
	}

	L.traverse(); R.traverse();

	for (int i = 1; i <= n; i++){
		rt[i] = rt[i-1];
		int x = L.rev[i];
		rt[i] = update(rt[i], 1, n, R.dfn[x]);
	}

	while (Q--){
		int s, e, l, r; 
		cin >> s >> e >> l >> r;
		s++; e++; l++; r++;
		for (int i = 17; i >= 0; i--){
			if (R.fa[s][i] >= l) s = R.fa[s][i];
		}
		for (int i = 17; i >= 0; i--){
			if (L.fa[e][i] <= r) e = L.fa[e][i];
		}
		// consider if L's e subtree has: [s.dfn, s.out] 
		int big = query(rt[L.out[e]], 1, n, R.dfn[s], R.out[s]);
		int small = query(rt[L.dfn[e]-1], 1, n, R.dfn[s], R.out[s]);
		if (big > small) cout << 1 << '\n';
		else cout << 0 << '\n';
	}

	return 0;
}
