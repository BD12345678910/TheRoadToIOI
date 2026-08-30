#include <bits/stdc++.h>
using namespace std;

string s; int m, n;
int a[20];
long long dp[270000][102];

int main(){
	cin >> s >> m;
	n = s.length();
	for (int i = 0; i < n; i++){
		a[i] = s[i]-'0';
	}
	int N = 1<<n;
	dp[0][0] = 1;
	for (int i = 0; i < N-1; i++){
		bool flag = 1;
		for (int j = 0; j < n; j++){
			if ((i>>j)&1 && a[j]!=0) flag = 0;
		}
		if (i == 0) flag = 0;
		if (flag) continue;

		for (int j = 0; j < m; j++){
			if (!dp[i][j]) continue;
			// cout << i << ' ' << j << ' ' << dp[i][j] << endl;
			set<int> S;
			for (int neu = 0; neu < n; neu++){
				if ((i>>neu)&1) continue;
				if (S.count(a[neu])) continue;
				int nj = (j*10+a[neu])%m;
				int ni = i|(1<<neu);
				dp[ni][nj] = (dp[ni][nj]+dp[i][j]);
				S.insert(a[neu]);
			}
		}
	}

	cout << dp[N-1][0] << '\n'; 

	return 0;
}