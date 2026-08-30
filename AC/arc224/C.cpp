#include <bits/stdc++.h>
using namespace std;

int T, n, m;
int mx[300005], as[300005];
vector<int> G[300005];
bool vis[300005];

void dfs(int x){
	as[x] = mx[x]+1;
	vis[x] = 1;
	for (int v : G[x]){
		mx[v] = max(mx[v], as[x]);
	}
	for (int v : G[x]){
		if (!vis[v]) dfs(v);
	}
}

void solve(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	mx[1] = -1;
	dfs(1);

	for (int i = 1; i <= n; i++){
		cout << as[i] << " \n"[i==n];
	}

	for (int i = 1; i <= n; i++){
		mx[i] = vis[i] = 0; G[i].clear();
	}
	return;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	while (T--) solve();
	return 0;
}