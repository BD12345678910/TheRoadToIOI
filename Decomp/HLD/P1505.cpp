#include <bits/stdc++.h>
using namespace std;
const int NINF = -0x3f3f3f3f;
const int INF = 0x3f3f3f3f;
int n, Q;
vector<tuple<int,int,int>> G[200005];
vector<int> child[200005];
int sone[200005];
int w[200005], tmp[200005];

struct node{
	int mx, mn, su;
	bool neg;
} t[800005];

void pull(int x){
	t[x].mx = max(t[x<<1].mx, t[x<<1|1].mx);
	t[x].mn = min(t[x<<1].mn, t[x<<1|1].mn);
	t[x].su = (t[x<<1].su+t[x<<1|1].su);
}

void negg(int x){
	int tmpp = t[x].mn;
	t[x].mn = -t[x].mx;
	t[x].mx = -tmpp;
	t[x].su = -t[x].su;
	t[x].neg ^= 1;
}

void push(int x){
	if (t[x].neg) {
		negg(x<<1);
		negg(x<<1|1);
		t[x].neg = 0;
	}
}

void build(int x, int l, int r){
	if (l == r){
		t[x] = {w[l], w[l], w[l], 0};
		return;
	}
	int mid = (l+r)>>1;
	build(x<<1, l, mid);
	build(x<<1|1, mid+1, r);
	pull(x);
}

void update(int x, int l, int r, int q, int v){
	if (l == r){
		t[x].mx = t[x].mn = t[x].su = v;
		t[x].neg = 0;
		return;
	}
	int mid = (l+r)>>1;
	push(x);
	if (q <= mid) update(x<<1,l,mid,q,v);
	else update(x<<1|1, mid+1, r, q, v);
	pull(x);
}

void negat(int x, int l, int r, int ql, int qr){
	if (ql <= l && r <= qr){
		negg(x);
		return;
	}
	int mid = (l+r)>>1;
	push(x);
	if (ql <= mid) negat(x<<1, l, mid, ql, qr);
	if (qr > mid) negat(x<<1|1, mid+1, r, ql, qr);
	pull(x);
}

int qry_min(int x, int l, int r, int ql, int qr){
	if (ql <= l && r <= qr) return t[x].mn;
	if (qr < l || ql > r) return INF;
	push(x);
	int mid = (l+r)>>1;
	return min(qry_min(x<<1, l, mid, ql, qr), qry_min(x<<1|1, mid+1, r, ql, qr));
}

int qry_max(int x, int l, int r, int ql, int qr){
	if (ql <= l && r <= qr) return t[x].mx;
	if (qr < l || ql > r) return NINF;
	push(x);
	int mid = (l+r)>>1;
	return max(qry_max(x<<1, l, mid, ql, qr), qry_max(x<<1|1, mid+1, r, ql, qr));
}

int qry_sum(int x, int l, int r, int ql, int qr){
	if (ql <= l && r <= qr) return t[x].su;
	if (qr < l || ql > r) return 0;
	push(x);
	int mid = (l+r)>>1;
	return qry_sum(x<<1, l, mid, ql, qr)+qry_sum(x<<1|1, mid+1, r, ql, qr);
}

int dfn[200005], sz[200005], heavy[200005], dep[200005], fa[200005], cnt;
int head[200005];

void dfs(int x, int pa){
	sz[x] = 1;
	for (auto [v, e, ind]: G[x]){
		if (v == pa) continue;
		child[x].push_back(v);
		dep[v] = dep[x]+1;
		fa[v] = x;
		dfs(v, x);
		tmp[v] = e;
		sone[ind] = v;
		if (!heavy[x] || sz[v] >= sz[heavy[x]]){
			heavy[x] = v;
		}
		sz[x] += sz[v];
	}
}

void dfs2(int x, int hd){
	head[x] = hd;
	dfn[x] = ++cnt;
	if (heavy[x]){
		dfs2(heavy[x], hd);
		w[dfn[heavy[x]]] = tmp[heavy[x]];
	}
	for (int v : child[x]){
		if (v == heavy[x]) continue;
		dfs2(v, v);
		w[dfn[v]] = tmp[v];
	}
}

void path_negate(int x, int y){
	while (head[x] != head[y]){
		if (dep[head[x]] < dep[head[y]]) swap(x, y);
		// interval: [dfn[head[x]], dfn[x]]
		negat(1, 1, n, dfn[head[x]], dfn[x]);
		x = fa[head[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	if (dfn[y]+1 <= dfn[x])
	negat(1, 1, n, dfn[y]+1, dfn[x]);
}

int path_min(int x, int y){
	int ret = INF;
	while (head[x] != head[y]){
		if (dep[head[x]] < dep[head[y]]) swap(x, y);
		// interval: [dfn[head[x]], dfn[x]]
		ret = min(ret, qry_min(1, 1, n, dfn[head[x]], dfn[x]));
		x = fa[head[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	if (dfn[y]+1 <= dfn[x])
	ret = min(ret, qry_min(1, 1, n, dfn[y]+1, dfn[x]));
	return ret;
}

int path_max(int x, int y){
	int ret = NINF;
	while (head[x] != head[y]){
		if (dep[head[x]] < dep[head[y]]) swap(x, y);
		// interval: [dfn[head[x]], dfn[x]]
		ret = max(ret, qry_max(1, 1, n, dfn[head[x]], dfn[x]));
		x = fa[head[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	if (dfn[y]+1 <= dfn[x])
	ret = max(ret, qry_max(1, 1, n, dfn[y]+1, dfn[x]));
	return ret;
}

int path_sum(int x, int y){
	int ret = 0;
	while (head[x] != head[y]){
		if (dep[head[x]] < dep[head[y]]) swap(x, y);
		// interval: [dfn[head[x]], dfn[x]]
		ret += qry_sum(1, 1, n, dfn[head[x]], dfn[x]);
		x = fa[head[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	if (dfn[y]+1 <= dfn[x])
	ret += qry_sum(1, 1, n, dfn[y]+1, dfn[x]);
	return ret;
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b, c; cin >> a >> b >> c;
		a++; b++;
		G[a].push_back({b,c,i});
		G[b].push_back({a,c,i});
	}
	dfs(1, 1);
	dfs2(1, 1);
	build(1, 1, n);
	cin >> Q;
	while (Q--){
		string s; int a, b; cin >> s >> a >> b;
		if (s == "C"){
			update(1, 1, n, dfn[sone[a]], b);
		} else if (s == "N"){
			a++, b++;
			path_negate(a, b);
		} else if (s == "SUM"){
			a++, b++;
			cout << path_sum(a, b) << '\n';
		} else if (s == "MAX"){
			a++, b++;
			cout << path_max(a, b) << '\n';
		} else if (s == "MIN"){
			a++, b++;
			cout << path_min(a, b) << '\n';
		}
	}

	return 0;
}