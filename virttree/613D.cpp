#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, cnt;
const int N = 100005;
vector<int> G[N];
set<ll> E;
bool important[N];
int dfn[N], out[N];
int rev[N], depth[N], fa[N][18];
vector<int> T[N];
bool dp[N]; int ans; bool ns;

int lca(int x, int y){
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = 17; i >= 0; i--){
		if (depth[fa[x][i]] >= depth[y]){
			x = fa[x][i];
		}
	}
	if (x == y) return x;
	for (int i = 17; i >= 0; i--){
		if (fa[x][i]!=fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

bool is_ancestor(int x, int y){
	return (dfn[x] <= dfn[y] && out[y] <= out[x]);
}

void dfs(int x, int pa){
	dfn[x] = ++cnt;
	rev[cnt] = x;
	fa[x][0] = pa;
	for (int i = 1; i <= 17; i++){
		fa[x][i] = fa[fa[x][i-1]][i-1];
	}
	for (int v: G[x]){
		if (v == pa) continue;
		depth[v] = depth[x]+1;
		dfs(v, x);
	}
	out[x] = cnt;
}

bool dfs_solve(int x){
	int t = 0;
	for (int v : T[x]){
		if (dfs_solve(v)) t++;
	}
	if (important[x]){
		ans += t; 
		return 1;
	} else {
		if (t >= 2) ans++;
		return (t==1);
	}
}

void clean(int x){
	for (int v : T[x]) clean(v);
	important[x] = 0;
	T[x].clear();
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
		E.insert(1LL*min(a,b)*N+max(a,b));
	}
	dfs(1, 1);
	cin >> m;
	while (m--){
		int k; cin >> k; ns = 0;
		vector<int> nodes;
		for (int i = 1; i <= k; i++){
			int x; cin >> x;
			nodes.push_back(dfn[x]);
			important[x] = 1;
		}
		sort(nodes.begin(), nodes.end());
		for (int i = 0; i < k-1; i++){
			nodes.push_back(dfn[lca(rev[nodes[i]], rev[nodes[i+1]])]);
		}
		sort(nodes.begin(), nodes.end());
		int sz = unique(nodes.begin(), nodes.end())-nodes.begin();
		int root;
		stack<int> S; S.push(root = rev[nodes[0]]);
		for (int i = 1; i < sz; i++){
			int x = rev[nodes[i]];
			while (S.size() && !is_ancestor(S.top(), x)){
				S.pop();
			}
			T[S.top()].push_back(x);
			if (E.count(1LL*min(S.top(), x)*N+max(S.top(),x))) {
				if (important[S.top()] && important[x])
				ns = 1;
			}
			S.push(x);
		}
		if (ns) {
			cout << -1 << '\n';
		} else {
			ans = 0;
			dfs_solve(root);
			cout << ans << '\n';
		}
		clean(root);
	}

	return 0;
}