// TRASHED

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, cnt;
const int N = 250005;
const ll INF = 1e18;
vector<pair<int,ll>> G[N];
bool important[N];
int dfn[N], out[N];
int rev[N], d[N], st[N][19];
vector<int> T[N];
ll dp[N], mn[N];
int ln[N];

bool is_ancestor(int x, int y){
	return (dfn[x] <= dfn[y] && out[y] <= out[x]);
}

int lca(int x, int y){
	int p = ln[y-x+1];
	int xx = y-(1<<p)+1;
	if (d[st[x][p]] < d[st[xx][p]]){
		return st[x][p];
	} else {
		return st[xx][p];
	}
}

void dfs(int x, int pa){
	dfn[x] = ++cnt;
	rev[cnt] = x;
	for (auto [v, w]: G[x]){
		if (v == pa) continue;
		d[dfn[v]] = d[dfn[x]]+1;
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
	cin >> n; ln[1] = 0;
	for (int i = 2; i <= n; i++){
		ln[i] = ln[i>>1]+1;
	}
	for (int i = 1; i < n; i++){
		int a, b; ll c; cin >> a >> b >> c;
		G[a].push_back({b,c});
		G[b].push_back({a,c});
	}
	mn[1] = INF; dfs(1, 1);
	for (int i = 1; i <= n; i++) {
		st[i][0] = i;
	}
	for (int i = 1; i <= 18; i++){
		for (int j = 1; j+(1<<i) <= n; j++){
			int p = j+(1<<i);
			if (d[st[j][i-1]] < d[st[p][i-1]]){
				st[j][i] = st[j][i-1];
			} else {
				st[j][i] = st[p][i-1];
			}
		}
	}
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
			nodes.push_back(lca(nodes[i], nodes[i+1]));
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