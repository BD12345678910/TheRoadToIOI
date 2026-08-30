#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int col[N], fcol[N];
vector<int> G[N];
int dep[N], sz[N], dfn[N], cnt, heavy[N], fa[N];
int head[N];
int n, m;

struct Seg{
	int num, links, rechts;
	int sett; // not used for overalls
	void flip(){
		swap(links, rechts);
	}
}t[N<<2];

Seg meld(Seg X, Seg Y){
	Seg res = {X.num+Y.num, X.links, Y.rechts, 0};
	if (X.rechts == Y.links){
		res.num--;
	}
	return res;
}

void push(int x){
	if (t[x].sett){
		t[x<<1] = {1, t[x].sett, t[x].sett, t[x].sett};
		t[x<<1|1] = {1, t[x].sett, t[x].sett, t[x].sett};
		t[x].sett = 0;
	}
}

void pull(int x){
	t[x] = meld(t[x<<1], t[x<<1|1]);
}

void build(int x, int l, int r){
	if (l == r){
		t[x] = {1, fcol[l], fcol[l], 0};
		return;
	}
	int mid = (l+r)>>1;
	build(x<<1, l, mid);
	build(x<<1|1, mid+1, r);
	pull(x);
}

Seg qry(int x, int l, int r, int ql, int qr){
	if (ql <= l && r <= qr) return t[x];
	int mid = (l+r)>>1;
	push(x);
	if (ql <= mid && qr > mid) 
		return meld(qry(x<<1, l, mid, ql, qr), qry(x<<1|1, mid+1, r, ql, qr));
	else if (ql <= mid)
		return qry(x<<1, l, mid, ql, qr);
	else 
		return qry(x<<1|1, mid+1, r, ql, qr);
}

void update(int x, int l, int r, int ql, int qr, int v){
	if (ql <= l && r <= qr){
		t[x] = {1, v, v, v};
		return;
	}
	int mid = (l+r)>>1;
	push(x);
	if (ql <= mid) update(x<<1, l, mid, ql, qr, v);
	if (qr > mid) update(x<<1|1, mid+1, r, ql, qr, v);
	pull(x);
}

void dfs1(int x, int pa){
	sz[x] = 1;
	for (int v : G[x]){
		if (v == pa) continue;
		dep[v] = dep[x]+1;
		dfs1(v, x);
		fa[v] = x;
		if (!heavy[x] || sz[v] > sz[heavy[x]]){
			heavy[x] = v;
		}
		sz[x] += sz[v];
	}
}

void dfs2(int x, int pa, int hd){
	dfn[x] = ++cnt;
	head[x] = hd;
	if (heavy[x]){
		dfs2(heavy[x], x, hd);
	}
	for (int v : G[x]){
		if (v == pa || v == heavy[x]) continue;
		dfs2(v, x, v);
	}
}

int query(int x, int y){
	Seg X = Seg{0, -1, -1, 0};
	Seg Y = Seg{0, -1, -1, 0};
	Seg ans;
	while (head[x] != head[y]){
		if (dep[head[x]] > dep[head[y]]){
			// interval: [head[x], x];
			Seg Q = qry(1, 1, n, dfn[head[x]], dfn[x]); 
			Q.flip();
			X = meld(X, Q);
			x = fa[head[x]];
		} else {
			Seg Q = qry(1, 1, n, dfn[head[y]], dfn[y]);
			Y = meld(Q, Y);
			y = fa[head[y]];
		}
	}
	if (dep[x] <= dep[y]){
		Seg Q = qry(1, 1, n, dfn[x], dfn[y]);
		ans = meld(X, meld(Q, Y));
	} else if (dep[x] > dep[y]){
		Seg Q = qry(1, 1, n, dfn[y], dfn[x]); Q.flip();
		ans = meld(X, meld(Q, Y));
	} 
	return ans.num;
}

void modify(int x, int y, int to){
	while (head[x] != head[y]){
		if (dep[head[x]] < dep[head[y]]) swap(x, y);
		update(1, 1, n, dfn[head[x]], dfn[x], to);
		x = fa[head[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	update(1, 1, n, dfn[y], dfn[x], to);
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> col[i];
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs1(1, 1);
	dfs2(1, 1, 1);
	for (int i = 1; i <= n; i++){
		fcol[dfn[i]] = col[i];
	}
	build(1, 1, n);
	while (m--){
		char c; int a, b; cin >> c >> a >> b;
		if (c == 'Q'){
			cout << query(a, b) << '\n';
		} else {
			int d; cin >> d;
			modify(a, b, d);
		}
	}

	return 0;
}


