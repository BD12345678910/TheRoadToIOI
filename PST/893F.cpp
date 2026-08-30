#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
int n, Q, R;
int A[100005];
vector<int> G[100005];
int dep[100005], dfn[100005], out[100005], cnt, cc;
vector<pair<int,int>> layer[100005];
int root[100005];
// notice there are n updates, 
int t[2000000], lc[2000000], rc[2000000];

void dfs(int x, int pa){
	dfn[x] = ++cnt;
	dep[x] = dep[pa]+1;
	layer[dep[x]].push_back({dfn[x], A[x]});
	for (int v : G[x]){
		if (pa == v) continue;
		dfs(v, x);
	}
	out[x] = cnt;
}

int update(int x, int l, int r, int q, int v){
	int nx = ++cc;
	t[nx] = t[x];
	lc[nx] = lc[x];
	rc[nx] = rc[x];
	if (l == r){
		t[nx] = v;
		return nx;
	}
	int mid = (l+r)>>1;
	if (q <= mid) lc[nx] = update(lc[x], l, mid, q, v);
	if (q > mid) rc[nx] = update(rc[x], mid+1, r, q, v);
	t[nx] = min(t[lc[nx]], t[rc[nx]]);
	return nx;
}

int query(int x, int l, int r, int ql, int qr){
	if (!x || (ql <= l && r <= qr)) return t[x];
	if (qr < l || ql > r) return INF;
	int mid = (l+r)>>1;
	return min(query(lc[x], l, mid, ql, qr), 
		query(rc[x], mid+1, r, ql, qr));
}

int main(){
	cin >> n >> R; t[0] = INF;
	for (int i = 1; i <= n; i++){
		cin >> A[i];
	}
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(R, R);
	for (int i = 1; i <= n; i++){
		root[i] = root[i-1];
		for (auto [x, val] : layer[i]){
			root[i] = update(root[i], 1, n, x, val);
		}
	}
	cin >> Q; int last = 0;
	while (Q--){
		int x, k; cin >> x >> k;
		x = (x+last) % n + 1;
		k = (k+last) % n;
		// cout << x << ' ' << k << endl;
		// cout << dep[x]+k << ' ' << dfn[x] << endl;
		last = query(root[min(dep[x]+k, n)], 1, n, dfn[x], out[x]);
		cout << last << '\n';
	}

	return 0;
}