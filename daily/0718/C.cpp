#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> T[800005];
int dp[800005];
int sz[800005];

void dfs(int x){
	sz[x] = 1;
	int suma = 0, ch = 0;;
	bool flag = 0;
	for (int v : T[x]){
		dfs(v); ch++;
		sz[x] += sz[v];
		if (sz[v] > k) {
			dp[x] = max(dp[x], dp[v]+1);
		}
		suma += dp[v];
		if (sz[v] >= 2 && !dp[v]){
			flag = 1;
		}
	}
	dp[x] = max(dp[x], suma);
	if (flag && ch >= k) dp[x] = max(dp[x], suma+1);
}

int main(){
	int t; cin >> t;
	while (t--){
		cin >> n >> k;
		for (int i = 2; i <= n; i++){
			int x; cin >> x;
			T[x].push_back(i);
		}
		dfs(1);
		cout << dp[1] << endl;
		for (int i = 1; i <= n; i++){
			T[i].clear(); dp[i] = 0;
		}
	}

	return 0;
}

