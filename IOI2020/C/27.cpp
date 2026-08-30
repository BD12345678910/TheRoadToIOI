#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

// at position i, we took j l's
long long dp[1505][1505];
int last[1505][1505];

long long find_maximum(int k, vector<vector<int>> x) {
	int n = x.size();
	int m = x[0].size();
	vector<vector<int>> answer(n, vector<int>(m, -1));

	memset(dp, 0xc0, sizeof(dp));
	dp[0][0] = x[0][m-1]; last[0][0] = 1;
	dp[0][1] = -x[0][0]; last[0][1] = 0;
	for (int i = 1; i < n; i++){
		// consider taking i: l
		for (int j = 1; j <= n/2; j++){
			long long cand = dp[i-1][j-1]-x[i][0];
			if (cand > dp[i][j]){
				dp[i][j] = cand;
				last[i][j] = 0; // took smaller
			}
		}
		// consider taking i: r
		for (int j = 0; j <= n/2; j++){
			long long cand = dp[i-1][j]+x[i][m-1];
			if (cand > dp[i][j]){
				dp[i][j] = cand;
				last[i][j] = 1; // took larger
			}
		}
	}

	long long ans = dp[n-1][n/2];

	int curr = n/2;
	for (int i = n-1; i >= 0; i--){
		if (last[i][curr]){
			answer[i][m-1] = 0;
		} else {
			answer[i][0] = 0;
			curr--;
		}
	}
	allocate_tickets(answer);
	return ans;
}
