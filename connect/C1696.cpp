#include <bits/stdc++.h>
using namespace std;

int n, m, r;
vector<int> G[505];
int belong[505];
bool vis[505];

bool dfs(int x){
	vis[x] = 1;
	for (int v : G[x]){
		if (vis[belong[v]]) continue;
		if (!belong[v] || dfs(belong[v])){
			belong[v] = x;
			return 1;
		}
	}
	return 0;
}

int main(){
	cin >> n >> m >> r;
	for (int i = 1; i <= r; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++){
		memset(vis,0,sizeof(vis));
		if (dfs(i)) ans++;
	}
	cout << ans << endl;
	for (int i = 1; i <= m; i++){
		if (belong[i]){
			cout << belong[i] << ' ' << i << '\n';
		}
	}
	return 0;
}