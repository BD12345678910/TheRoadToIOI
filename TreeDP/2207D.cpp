#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, k, v;
vector<int> G[500005];
int dp[500005];

void dfs(int x, int pa){
	if (x != pa && G[x].size()==1){
		dp[x] = 0;
		return;
	}
	int small = INF;
	bool mark = 0;
	for (int v : G[x]){
		if (v == pa) continue;
		dfs(v, x);
		if (small + dp[v] <= k-1){
			mark = 1;
		}
		small = min(small, dp[v]);
	}
	if (mark) dp[x] = 0;
	else dp[x] = small+1;
}

void solve(){
	cin >> n >> k >> v;
	for (int i = 1; i <= n; i++){
		G[i].clear(); dp[i] = 0;
	}
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(v, v);
	if (dp[v]==0) cout << "YES\n";
	else cout << "NO\n";
	return;
}

int main(){
	int T; cin >> T;
	while (T--) solve();
	return 0;
}