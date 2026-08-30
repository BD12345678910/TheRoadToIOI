#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
ll inv2;
int n, k;
ll fact[200005], inv[200005];
ll a[200005];

ll qpow(ll x, ll nn){
	ll res = 1;
	while (nn){
		if (nn & 1) res = res * x % MOD; 
		x = x * x % MOD;
		nn >>= 1;
	}
	return res;
}

ll comb(ll x, ll y){
	if (y < 0 || y > x) return 0;
	return fact[x] * inv[x-y] % MOD * inv[y] % MOD;
}

void solve(){
	cin >> n >> k;
	ll M = 0;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if (i >= n-k+1) M |= a[i];
	}
	ll mnt = 0;
	for (int i = 0; i <= k; i++){
		mnt = (mnt + comb(n, i)) % MOD;
	}

	if (M == 0){
		cout << mnt << '\n';
		return;
	}

	ll require = M;
	ll ans = 0;
	int r = k;
	for (int i = n; i >= 1; i--){
		mnt = (mnt + comb(i-1, r)) % MOD * inv2 % MOD;
		ll x = a[i];
		if (require & (~x)){
			// we must take an OR, otherwise a bit will be missing
			mnt = (mnt - comb(i-1, r) + MOD) % MOD;
			r--;
			require &= (~x);
		} else {
			// i can take it and finish:
			ans = (ans + mnt - comb(i-1, r) + MOD) % MOD;
			// or i can and it: = do nothing
		}
	}
	cout << ans << '\n';
	return;
}

int main(){
	fact[0] = inv[0] = 1;
	inv2 = qpow(2LL, MOD-2);
	for (int i = 1; i <= 200000; i++){
		fact[i] = fact[i-1] * i % MOD;
		inv[i] = inv[i-1] * qpow(i, MOD-2) % MOD;
	}
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();

	return 0;
}