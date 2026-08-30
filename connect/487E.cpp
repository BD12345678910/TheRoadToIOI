// UNFINISHED: 
// an optimization is needed:
// store each ap into its fa bcc, so that queries take lca + parent
// and somehow include that ap also: because if e.g. X to X, 
// then an attached ap (in that bcc) can be visited still.

#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
vector<int> G[100005];
vector<int> T[200005];
int n, m, Q;
int dfn[100005], low[100005], cnt, bcc;
int sta[100005], tp, pa[100005];
bool ap[100005];
multiset<int> P[100005];
int w[100005];
int sz[200005], heavy[200005], head[200005];
int dffn[200005], cc;
int fa[200005][18], dep[200005];

// stores in terms of dfn
int t[800005];
void update(int x, int l, int r, int q, int v){
	if (l == r){
		t[x] = v;
		return ;
	}
	int mid = (l+r)>>1;
	if (q <= mid) update(x<<1, l, mid, q, v);
	else update(x<<1|1, mid+1, r, q, v);
	t[x] = min(t[x<<1], t[x<<1|1]);
}
int qry(int x, int l, int r, int ql, int qr){
	if (ql > r || qr < l) return INF;
	if (ql <= l && r <= qr) return t[x];
	int mid = (l+r)>>1;
	return 
	min(qry(x<<1,l,mid,ql,qr), qry(x<<1|1,mid+1,r,ql,qr));
}

void dfs(int x, int p){
	dfn[x] = low[x] = ++cnt;
	sta[++tp] = x;
	int child = 0;
	for (int v : G[x]){
		if (v == p) continue;
		if (dfn[v]){
			low[x] = min(low[x], dfn[v]);
		} else {
			dfs(v, x); child++;
 			low[x] = min(low[x], low[v]);
			if (low[v] >= dfn[x]){
				if (x != p) ap[x] = 1;
				++bcc;
				while (sta[tp] != v){
					int u = sta[tp];
					T[bcc].push_back(u);
					T[u].push_back(bcc);
					pa[u] = bcc;
					tp--;
				}
				T[bcc].push_back(v);
				T[v].push_back(bcc);
				pa[v] = bcc;
				T[bcc].push_back(x);
				T[x].push_back(bcc);
				tp--;
			}
		}
	}
	if (x == p && child > 1) ap[x] = 1;
}

void dfs2(int x, int p){
	sz[x] = 1;
	fa[x][0] = p;
	for (int i = 1; i <= 17; i++){
		fa[x][i] = fa[fa[x][i-1]][i-1];
	}
	for (int v : T[x]){
		if (v == p) continue;
		dep[v] = dep[x]+1;
		dfs2(v, x);
		sz[x] += sz[v];
		if (!heavy[x] || sz[v] > sz[heavy[x]]){
			heavy[x] = v;
		}
	}
}

void update(int x){
	if (x <= n) update(1, 1, bcc, dffn[x], w[x]);
	else update(1, 1, bcc, dffn[x], *P[x-n].begin());
}

void dfs3(int x, int p, int hd){
	head[x] = hd;
	dffn[x] = ++cc; 
	if (heavy[x]) dfs3(heavy[x], x, hd);
	for (int v : T[x]){
		if (v==p || v==heavy[x]) continue;
		dfs3(v, x, v);
	}
}

int rng(int a, int b){
	int ans = INF;
	while (head[a] != head[b]){
		if (dep[head[a]] < dep[head[b]]) swap(a, b);
		ans = min(ans, qry(1, 1, bcc, dffn[head[a]], dffn[a]));
		a = fa[head[a]][0];
	}
	if (dffn[a] > dffn[b]) swap(a, b);
	ans = min(ans, qry(1, 1, bcc, dffn[a], dffn[b]));
	return ans;
}

int main(){
	cin >> n >> m >> Q;
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bcc = n;
	dfs(1, 1);
	dfs2(1, 1);
	dfs3(1, 1, 1);

	for (int B = n+1; B <= bcc; B++){
	    for (int v : T[B]){
	        P[B-n].insert(w[v]);
	    }
	}
	for (int i = 1; i <= bcc; i++){
		update(i);
	}

	while (Q--){
		int a, b; char op; 
		cin >> op >> a >> b;
		if (op == 'C'){
			if (!ap[a]){
				int p = pa[a];
				P[p-n].erase(P[p-n].find(w[a]));
				w[a] = b;
				update(a);
				P[p-n].insert(w[a]);
				update(p);
			} else {
				w[a] = b;
				update(a);
			}
			
		} else {
			cout << rng(a, b) << '\n';
		}
	}

	return 0;
}




