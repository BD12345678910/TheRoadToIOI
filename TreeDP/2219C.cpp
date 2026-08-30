#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld INF = 1e13;
int n;
bool col[200005], vis[200005];
vector<int> G[200005];
// 0 means before parent, 1 means after parent
ld dp[200005][2];

void mn(ld &x, ld y){
	if (y < x) x = y;
}

void dfs(int x, int pa){
	vis[x] = 1;
	// the advantages of coloring before
	priority_queue<ld,vector<ld>,greater<ld>> P;
	ld curr = 0;
	for (int v : G[x]){
		if (v == pa) continue;
		if (col[v]){
			dp[v][0] = 0;
			dp[v][1] = INF; 
		} else {
			dfs(v, x);
		}
		curr += dp[v][1];
		P.push(dp[v][0]-dp[v][1]);
	}

	if (x == pa){
		int children = P.size();
		// total neighbors: children+1
		for (int i = 1; i <= children; i++){
			curr += P.top(); P.pop();
			mn(dp[x][0], curr + (ld)1.0*(children)/i);
		}
	} else {
		int children = P.size();
		mn(dp[x][1], curr + (ld)1.0*(children+1));
		// total neighbors: children+1
		for (int i = 1; i <= children; i++){
			curr += P.top(); P.pop();
			mn(dp[x][0], curr + (ld)1.0*(children+1)/i);
			mn(dp[x][1], curr + (ld)1.0*(children+1)/(i+1));
		}
	}
	
	// cout << x << ' ' << dp[x][0] << ' ' << dp[x][1] << endl;
}

void solve(){
	cin >> n; ld total = 0;
	for (int i = 1; i <= n; i++){
		G[i].clear(); vis[i] = 0;
		dp[i][0] = dp[i][1] = INF;
	}
	for (int i = 1; i <= n; i++) {
		char ch; cin >> ch;
		col[i] = (ch == '1');
	}
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for (int i = 1; i <= n; i++){
		if (!col[i] && !vis[i]){
			dfs(i, i);
			total += dp[i][0];
		}
	}
	cout << total << '\n';
}

int main(){
	int T; cin >> T;
	cout << setprecision(10) << fixed;
	while (T--) solve();
	return 0;
}