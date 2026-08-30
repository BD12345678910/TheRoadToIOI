#include <bits/stdc++.h>
using namespace std;

int n, m;
bool valid[100005];
int cur[100005];
vector<pair<int,int>> G[100005];
bool vis[200005];
int deg[100005];
vector<int> ans;

void dfs(int x){
	for (int &i = cur[x]; i < (int)G[x].size(); ){
		if (vis[G[x][i].second]) continue;
		vis[G[x][i].second] = 1;
		i++;
		dfs(G[x][i-1].first);
	}
	ans.push_back(x);
}

bool viss[100005];
void dfss(int x){
	valid[x] = 0; 
	viss[x] = 1;
	for (auto v : G[x]){
		if (!viss[v.first]){
			dfss(v.first);
		}
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back({b, i});
		G[b].push_back({a, i});
		deg[a]++; deg[b]++;
		valid[a] = 1; valid[b] = 1;
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] % 2) {
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}
	dfss(1);
	for (int i = 1; i <= n; i++) if (valid[i]) {
		cout << "IMPOSSIBLE\n";
		return 0;
	}
	dfs(1);
	reverse(ans.begin(), ans.end());
	for (int a : ans){
		cout << a << ' ';
	}
	cout << endl;

	return 0;
}