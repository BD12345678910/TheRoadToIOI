// Brilliant way to optimize from O(n^2) to O(n log n):
// Solve(l, r) -> find i such that (r-i+1)(i-l+1) = a[i], 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9+7;
ll a[500005], n;
ll fact[500005];
ll inv[500005];
ll ans;

ll qpow(ll x, ll n){
	ll res = 1;
	while (n){
		if (n & 1) res = res * x % MOD;
		x = x * x % MOD;
		n >>= 1;
	}
	return res;
}

ll comb(int A, int B){
	return fact[A]*inv[B]%MOD*inv[A-B]%MOD;
}

void solvee(int L, int R){
	if (L == R) {
		if (a[L] != 1) ans = 0;
		return;
	}
	if (L > R) return;
	int m = (R-L)>>1;
	bool flag = 1;
	for (int i = 0; i <= m; i++){
		int x = L+i;
		if (1LL*(R-x+1)*(x-L+1) == a[x]){
			ans = (ans * comb(R-L, R-x) % MOD);
			solvee(L, x-1);
			solvee(x+1, R);
			flag = 0;
			break;
		}
		x = R-i;
		if (1LL*(R-x+1)*(x-L+1) == a[x]){
			ans = (ans * comb(R-L, R-x) % MOD);
			solvee(L, x-1);
			solvee(x+1, R);
			flag = 0;
			break;
		}
	}
	if (flag){
		ans = 0;
		return;
	}
}

void solve(){
	cin >> n; ans = 1;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	solvee(1, n);
	cout << ans << '\n';
}

int main(){
	fact[0] = 1; inv[0] = 1;
	for (int i = 1; i <= 500000; i++){
		fact[i] = fact[i-1]*i%MOD;
		inv[i] = inv[i-1]*qpow(i, MOD-2)%MOD; 
	}
	int T; cin >> T;
	while (T--) solve();
	return 0;
}

