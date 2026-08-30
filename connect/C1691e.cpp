#include <bits/stdc++.h>
using namespace std;

int n, m;
int cur[100005];
vector<pair<int,int>> G[100005];
bool vis[200005];
int deg[100005];
vector<int> ans;

void dfs(int x, int e){
	vis[e] = 1;
	for (int &i = cur[x]; i < (int)G[x].size(); i++){
		int ee = G[x][i].second;
		if (vis[ee]) continue;
		dfs(G[x][i].first, ee);
	}
	if (e != -1) ans.push_back(e);
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back({b, i});
		G[b].push_back({a, i});
		deg[a]++; deg[b]++;
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] % 2) {
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}
	dfs(1, -1);
	reverse(ans.begin(), ans.end());
	for (int a : ans){
		cout << a << ' ';
	}
	cout << endl;

	return 0;
}