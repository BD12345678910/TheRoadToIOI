// DP on DP example

#include <bits/stdc++.h>
using namespace std;

/*

states:
0 - Empty
1 - 0 LOSE
2 - 00
3 - 1 WIN
4 - 10
5 - 100 LOSE
6 - 11 (guaranteed) WIN
(7 - 110 x 8 - 1100 x)

*/

const int P = 1e9+7;
int nxt[7][2];
int dp[7];
int ndp[7];

int main(){
	nxt[0][0] = 1; nxt[0][1] = 3;
	nxt[1][0] = 2; nxt[1][1] = 0;
	nxt[2][0] = 1; nxt[2][1] = 1;
	nxt[3][0] = 4; nxt[3][1] = 6;
	nxt[4][0] = 5; nxt[4][1] = 3;
	nxt[5][0] = 4; nxt[5][1] = 4;
	nxt[6][0] = 6; nxt[6][1] = 6;
	string s; cin >> s; int n = s.length(); s = "#"+s;
	
	dp[0] = 1;
	for (int i = 1; i <= n; i++){
		memset(ndp, 0, sizeof(ndp));
		for (int x = 0; x < 7; x++){
			if (s[i]=='0' || s[i]=='?'){
				(ndp[nxt[x][0]] += dp[x]) %= P;
			}
			if (s[i]=='1' || s[i]=='?'){
				(ndp[nxt[x][1]] += dp[x]) %= P;
			}
		}
		memcpy(dp, ndp, sizeof(dp));
	}
	cout << (dp[3] + dp[6])%P << '\n';

	return 0;
}




