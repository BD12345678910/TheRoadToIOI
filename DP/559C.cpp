#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200000;
const int MOD = 1000000007;
ll fact[200005], inv[200005];
int H, W, n;
pair<int,int> P[2005];
ll dp[2005];

ll qpow(ll x, ll nn){
	ll res = 1;
	while (nn){
		if (nn & 1) res = res * x % MOD;
		x = x * x % MOD;
		nn >>= 1;
	}
	return res;
}
ll comb(int x, int y){
	return fact[x]*inv[y]%MOD*inv[x-y]%MOD;
}

int main(){
	fact[0] = inv[0] = 1;
	for (int i = 1; i <= N; i++){
		fact[i] = fact[i-1]*i%MOD;
		inv[i] = inv[i-1]*qpow(i,MOD-2)%MOD;
	}
	cin >> H >> W >> n;
	for (int i = 1; i <= n; i++){
		cin >> P[i].first >> P[i].second;
	}
	P[n+1] = {H, W};
	sort(P+1, P+n+2);
	for (int i = 1; i <= n+1; i++){
		int x = P[i].first, y = P[i].second;
		dp[i] = comb(x+y-2, x-1);
		for (int j = 1; j < i; j++){
			int xx = P[j].first, yy = P[j].second;
			if (yy > y) continue;
			dp[i] = (dp[i]-dp[j]*comb(y-yy+x-xx,x-xx)%MOD+MOD)%MOD;
		}
	}
	cout << dp[n+1] << '\n';
	return 0;
}





