#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
vector<int> G[200005];
int n;
long long dp[200005];
int mx[200005];
bool ok[200005];
int start;
set<int> S;

void dfs(int x, int pa){
	for (int v : G[x]){
		if (v == pa) continue;
		dfs(v, x);
		mx[x] = max({mx[v], v, mx[x]});
	}
	if (G[x].size()==1) start = max(start,x);
}

void dfs2(int x, int pa, bool er){
	if (er) S.erase(x);
	else S.insert(x);
	for (int v : G[x]){
		if (v == pa) continue;
		dfs2(v, x, er);
	}
}

void dfs3(int x, int pa){
	if (x > *(--S.end())) ok[x]=1;
	for (int v : G[x]){
		if (v == pa) continue;
		dfs3(v, x);
	}
}

void solve(){
	cin >> n;
	start = 0; S.clear();
	for (int i = 0; i <= n; i++){
		G[i].clear();
		mx[i] = dp[i] = ok[i] = 0;
	}
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	if (G[n].size() == 1){
		cout << 1 << '\n';
		return;
	}
	dfs(n, n);
	dp[start] = 1;
	for (int i = start+1; i < n; i++){
		if (mx[i] > i-1) dp[i] = dp[i-1];
		else dp[i] = (dp[i-1]-dp[mx[i]]+dp[i-1]+MOD)%MOD;
	}

	for (int i = 1; i < n; i++) S.insert(i);
	for (int x : G[n]){
		dfs2(x, n, 1);
		// cout << x << ' ' << *(--S.end()) << '\n';
		dfs3(x, n);
		dfs2(x, n, 0);
	}
	for (int i = start; i < n; i++){
		// cout << i << ' ' << dp[i] << '\n';
		if (ok[i]) (dp[n] += (dp[i]-dp[i-1]+MOD))%=MOD;
	}
	cout << dp[n] << '\n';

	return;
}

int main(){
	int T; cin >> T; 
	while (T--) solve();
	return 0;
}