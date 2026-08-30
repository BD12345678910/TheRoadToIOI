#include <bits/stdc++.h>
using namespace std;

int n;
// 0 means with end rainy, 1 means sunny
bool S[200005];
long long dp[200005][2];
int x[200005], y[200005];

void solve(){
	cin >> n; 
	for (int i = 1; i <= n; i++){
		char c; cin >> c;
		if (c == 'S') S[i] = 1;
		else S[i] = 0;
	}
	for (int i = 1; i <= n; i++){
		cin >> x[i];
	}
	for (int i = 2; i <= n; i++){
		cin >> y[i];
	}
	dp[1][S[1]] = 0;
	dp[1][1-S[1]] = -x[1];
	for (int i = 2; i <= n; i++){
		if (S[i]){
			dp[i][1] = max(dp[i-1][0]+y[i], dp[i-1][1]);
			dp[i][0] = max(dp[i-1][0], dp[i-1][1])-x[i];
		} else {
			dp[i][1] = max(dp[i-1][0]+y[i], dp[i-1][1])-x[i];
			dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
		}
	}
	cout << max(dp[n][0], dp[n][1]) << '\n';
	return;
}

int main(){
	int T; cin >> T;
	while (T--) solve();
	return 0;
}