// stardew valley

#include <bits/stdc++.h>
using namespace std;

int n, m;
int cur[500005];
vector<pair<int,int>> G[500005];
vector<pair<int,int>> B[500005];
bool par[500005];
bool vis[500005];
bool vise[500005];	

vector<int> ans;

void dfs(int x){
	vis[x] = 1;
	for (auto [v, e] : B[x]){
		if (vis[v]) continue;
		dfs(v);
		if (par[v]){
			par[v] ^= 1;
			par[x] ^= 1;
			vise[e] = 1;
		}
	}
}

void hier(int x){
	for (int &i = cur[x]; i < G[x].size(); ){
		int v = G[x][i].first, e = G[x][i].second;
		i++;
		if (vise[e]) continue;
		vise[e] = 1;
		hier(v);
	}
	ans.push_back(x);
}

void solve(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		vis[i] = par[i] = cur[i] = 0;
		G[i].clear(); B[i].clear();
	}
	for (int i = 1; i <= m; i++){
		vise[i] = 0;
		int a, b, c; cin >> a >> b >> c;
		G[a].push_back({b, i});
		G[b].push_back({a, i});
		par[a] ^= 1; par[b] ^= 1;
		if (c == 0){
			B[a].push_back({b, i});
			B[b].push_back({a, i});
		}
	}
	for (int i = 1; i <= n; i++){
		if (!vis[i]) {
			dfs(i);
			if (par[i]) {
				cout << "NO\n";
				return;
			}
		}
	}
	ans.clear();
	hier(1);
	cout << "YES\n";
	cout << ans.size()-1 << '\n';
	for (int x : ans){
		cout << x << ' ';
	}
	cout << '\n';
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}