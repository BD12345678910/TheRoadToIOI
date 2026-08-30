#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int n;
vector<int> G[200005];
int mx[200005], dp[200005];
int leaf;

void dfs(int x, int pa){
	for (int v : G[x]){
		if (v == pa) continue;
		dfs(v, x);
		mx[x] = max({mx[x], mx[v], v});
	}
	if (G[x].size()==1){
		leaf = max(leaf, x);
	}
}

int main(){
	int T; cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1; i <= n; i++) {
			dp[i] = mx[i] = 0;
			G[i].clear();
		}
		leaf = 0;
		for (int i = 1; i < n; i++){
			int a, b; cin >> a >> b;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		dfs(n, n);

		dp[leaf] = 1;
		for (int i = leaf+1; i < n; i++){
			int what = dp[i-1]-dp[mx[i]]+MOD;
			if (i-1<mx[i]) what = 0; 
			dp[i] = (what % MOD + dp[i-1])%MOD;
			// cout << dp[i]-dp[i-1] << ' ';
		}
		cout << dp[n-1]-dp[n-2] << endl;
	}
	return 0;
}

