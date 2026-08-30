// https://www.luogu.com.cn/problem/P10614

// Given S, m, for each i, 
// count the number of strings T of length m such that LCS(S, T) = i

// m <= 1000, |S| <= 15

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int m; string S;
char CH[4] = {'A', 'T', 'C', 'G'};
int dp[33000];
int ndp[33000];
int tmp[18];
int neu[18];
int ans[18];

void solve(){
	memset(dp, 0, sizeof(dp));
	memset(ans, 0, sizeof(ans));
	cin >> S; 
	cin >> m;
	int n = S.length(); S = "#"+S;
	dp[0] = 1; tmp[0] = neu[0] = 0;
	int cap = (1<<n)-1;
	for (int j = 1; j <= m; j++){
		memset(ndp, 0, sizeof(ndp));
		for (int W = 0; W <= cap; W++){
			for (int id = 0; id < 4; id++){
				char c = CH[id];
				for (int i = 1; i <= n; i++){
					tmp[i] = tmp[i-1] + (W>>(i-1)&1);
					neu[i] = 0;
				}
				for (int i = 1; i <= n; i++){
					neu[i] = max(max(neu[i-1], tmp[i]), neu[i]);
					if (S[i] == c) neu[i] = max(neu[i], tmp[i-1]+1);
				}
				int nW = 0;
				for (int i = 1; i <= n; i++){
					if (neu[i] > neu[i-1]) nW |= (1<<(i-1));
				}
				(ndp[nW] += dp[W]) %= MOD;
			}
		}
		memcpy(dp, ndp, sizeof(ndp));
	}
	for (int W = 0; W <= cap; W++){
		int cnt = __builtin_popcount(W);
		(ans[cnt] += dp[W]) %= MOD;
	}

	for (int i = 0; i <= n; i++){
		cout << ans[i] << '\n';
	}


	return;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}