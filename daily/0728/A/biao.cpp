#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, K;
const ll MOD = 998244353;
ll comb[30][30];
ll dp[30][30];

int main(){
	cin >> n >> K;
	if (n <= 10){
		comb[0][0] = 1;
		for (int i = 1; i <= n; i++){
			comb[i][0] = comb[i-1][0];
			comb[i][i] = comb[i-1][i-1];
			for (int j = 1; j < i; j++){
				comb[i][j] = comb[i-1][j-1]+comb[i-1][j];
			}
		}
		dp[0][0] = 1;
		dp[1][1] = 1; dp[1][0] = 1;
		for (int i = 2; i <= n; i++){
			for (int k = 0; k <= i; k++){
				for (int a = 0; a <= k; a++)
				for (int l = 1; l <= n; l++){
					for (int r = l; r <= n; r++){
						dp[i][k] += dp[l-1][a]*dp[n-r][k-a]*comb[k][a];
					}
				}
			}
		}
		for (int i = 1; i <= n; i++){
			for (int k = 0; k <= i; k++){
				cout << dp[i][k] << ' ';
			}
			cout << endl;
		}
	} else if (n == K) {
		ll ans = 1;
		for (int i = 1; i <= 2*n-1; i+=2){
			ans = ans * i % MOD;
		}
		cout << ans << '\n';
	}
	return 0;
}





