#include <bits/stdc++.h>
using namespace std;
const int INF = 0xc0c0c0c0;
int n, m;
int dp[500005];
int drei[500005], zwei[500005], eins[1000005];
int a[500005];

void solve(){
	cin >> n >> m;
	for (int i = 0; i <= n; i++){
		zwei[i] = drei[i] = eins[i] = INF;
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	int curr = INF;
	drei[1] = zwei[m] = eins[m] = dp[1] = (a[1] == 1);
	for (int i = 2; i <= n; i++){
		dp[i] = 0;
		if (i-a[i] >= 0 && i-a[i] <= n-m) {
			dp[i] = max(drei[i-a[i]]+1, dp[i]);
			dp[i] = max(eins[i-a[i]+m]+1, dp[i]);
			dp[i] = max(curr+1, dp[i]);
		}
		drei[i] = max(drei[i-1], dp[i]);
		zwei[i+m-a[i]] = max(dp[i], zwei[i+m-a[i]]);
		eins[i+m-a[i]] = max(eins[i+m-a[i]], dp[i]);
		curr = max(curr, zwei[i]);
	}
	cout << n-drei[n] << '\n';
	return;
}

int main(){
	int T; cin >> T;
	while (T--) solve();
	return 0;
}