#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
// n <= 100, L <= 1000
int n, L;
int a[102];
long long dp[1002][52][4];
long long ndp[1002][52][4];

int main(){
	cin >> n >> L;
	if (n == 1){
		cout << 1 << '\n';
		return 0; 
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a+1, a+n+1);
	
	// insert the first by force:
	dp[0][1][1] = 2; dp[0][1][0] = 1;

	// consider differences:
	for (int t = 2; t <= n; t++){
		memset(ndp, 0, sizeof(ndp));
		for (int c = 0; c <= L; c++)
		for (int s = 1; s <= 50; s++)
		for (int e = 0; e <= 2; e++){
			if (!dp[c][s][e]) continue;
			int nc = c + (2*s-e)*(a[t]-a[t-1]);
			if (nc > L) continue;

			// merging two:
			if (s > 1) (ndp[nc][s-1][e] += dp[c][s][e]*(s-1)%MOD) %= MOD;

			// adding to someone
			(ndp[nc][s][e] += dp[c][s][e]*(2*s-e)%MOD) %= MOD;
			(ndp[nc][s][e+1] += dp[c][s][e]*(2-e)%MOD) %= MOD;

			// starting self
			(ndp[nc][s+1][e] += dp[c][s][e]*(s+1-e)%MOD) %= MOD;
			(ndp[nc][s+1][e+1] += dp[c][s][e]*(2-e)%MOD) %= MOD;

		}
		memcpy(dp, ndp, sizeof(dp));
	}

	long long ans = 0;
	for (int cost = 0; cost <= L; cost++){
		ans = (ans + dp[cost][1][2]) % MOD;
	}
	cout << ans << endl;
	return 0;
}




