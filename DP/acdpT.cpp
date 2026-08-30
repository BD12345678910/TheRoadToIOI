#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1000000007;
int n;
bool bigger[3005];
// at position i, position i was rank j
int dp[3005][3005];

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		char c; cin >> c;
		bigger[i] = (c=='>');
	}
	dp[1][1] = 1;
	for (int i = 2; i <= n; i++){
		// the rank must be smaller 
		if (bigger[i-1]){
			ll su = 0;
			for (int j = 1; j < i; j++){
				su = (su + dp[i-1][j]) % MOD;
				dp[i][j+1] = su;
			}
		} else {
			ll su = 0;
			for (int j = i; j >= 1; j--){
				su = (su + dp[i-1][j]) % MOD;
				dp[i][j] = su;
			}
		}
	}
	ll gans = 0;
	for (int j = 1; j <= n; j++) gans += dp[n][j];
	cout << gans % MOD << endl;

	return 0;
}