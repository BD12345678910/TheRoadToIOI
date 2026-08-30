#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
int n, k;
ll fact[2000005], inv[2000005];

ll qpow(ll x, ll nn){
	ll res = 1;
	while (nn){
		if (nn & 1) res = res * x % MOD;
		x = x * x % MOD;
		nn >>= 1;
	}
	return res;
}

ll comb(int a, int b){
	return fact[a] * inv[b] % MOD * inv[a-b] % MOD;
}

int main(){
	freopen("flip.in", "r", stdin);
	freopen("flip.out", "w", stdout);
	cin >> n >> k;
	fact[0] = inv[0] = 1;
	for (int i = 1; i <= n+k; i++){
		fact[i] = fact[i-1] * i % MOD;
		inv[i] = inv[i-1] * qpow(i, MOD-2) % MOD;
	}
	ll ans = comb(n+k, 2*k);
	for (int i = 2*k-1; i >= 1; i -= 2){
		ans = ans * i % MOD;
	}
	cout << ans << endl;
	return 0;
}


