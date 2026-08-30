#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, cnt;
const int N = 250005;
const ll INF = 1e18;
vector<pair<int,ll>> G[N];
bool important[N];
int dfn[N], out[N];
int rev[N], depth[N], fa[N][19];
vector<int> T[N];
ll dp[N], mn[N];

int lca(int x, int y){
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = 18; i >= 0; i--){
		if (depth[fa[x][i]] >= depth[y]){
			x = fa[x][i];
		}
	}
	if (x == y) return x;
	for (int i = 18; i >= 0; i--){
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
	for (int i = 1; i <= 18; i++){
		fa[x][i] = fa[fa[x][i-1]][i-1];
	}
	for (auto [v, w]: G[x]){
		if (v == pa) continue;
		depth[v] = depth[x]+1;
		mn[v] = min(mn[x], w);
		dfs(v, x);
	}
	out[x] = cnt;
}

void dfs_solve(int x){
	if (important[x]){
		dp[x] = mn[x];
		return;
	}
	dp[x] = 0;
	for (int v : T[x]){
		dfs_solve(v);
		dp[x] += dp[v];
	}
	dp[x] = min(dp[x], mn[x]);
}

void clean(int x){
	for (int v : T[x]){
		clean(v);
	}
	important[x] = 0;
	T[x].clear();
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b; ll c; cin >> a >> b >> c;
		G[a].push_back({b,c});
		G[b].push_back({a,c});
	}
	mn[1] = INF; dfs(1, 1);
	cin >> m;
	while (m--){
		int k; cin >> k;
		vector<int> nodes;
		for (int i = 1; i <= k; i++){
			int x; cin >> x;
			nodes.push_back(dfn[x]);
			important[x] = 1;
		}
		sort(nodes.begin(), nodes.end());
		// consider nodes[i]
		for (int i = 0; i < k-1; i++){
			nodes.push_back(dfn[lca(rev[nodes[i]], rev[nodes[i+1]])]);
		}
		nodes.push_back(dfn[1]);
		sort(nodes.begin(), nodes.end());
		int sz = unique(nodes.begin(), nodes.end())-nodes.begin();
		stack<int> S; S.push(1);
		for (int i = 1; i < sz; i++){
			int x = rev[nodes[i]];
			while (S.size() && !is_ancestor(S.top(), x)){
				S.pop();
			}
			T[S.top()].push_back(x);
			S.push(x);
		}
		dfs_solve(1);
		cout << dp[1] << '\n';
		clean(1);
	}

	return 0;
}