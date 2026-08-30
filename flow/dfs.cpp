#include <bits/stdc++.h>
using namespace std;

// n on the left, m on the right
int n, m, e, ans;
vector<int> G[1003];
int belong[1003];
bool vis[1003];

bool dfs(int x){
	if (vis[x]) return 0;
	vis[x] = 1;
	for (int v : G[x]){
		if (belong[v]==x) continue;
		if (!belong[v] || dfs(belong[v])){
			belong[v] = x;
			return 1;
		}
	}
	return 0;
}

int main(){
	cin >> n >> m >> e;
	for (int i = 1; i <= e; i++){
		int x, y; cin >> x >> y;
		G[x].push_back(y);
	}
	for (int i = 1; i <= n; i++){
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	cout << ans << endl;
	return 0;
}