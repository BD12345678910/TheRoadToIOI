#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9+7;
// ll fact[200005], inv[200005];
ll a[200005];
ll two[200005], pre[200005], suf[200005];
vector<int> V;
vector<int> who;

ll qpow(ll x, ll nn){
	ll res = 1;
	while (nn){
		if (nn & 1) res = res * x % MOD; 
		x = x * x % MOD;
		nn >>= 1;
	}
	return res;
}

int n;

void solve(){
	cin >> n; V.clear(); who.clear();
	int pref = 0;
	int prev = -1, cnt = 0;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if (a[i]==-1) pref++;
		else {
			if (a[i] != prev){
				V.push_back(cnt);
				who.push_back(prev);
				prev = a[i];
				cnt = 0;
			}
		}
	}

	int l = V.size()-1;

	for (int i = 1; i <= l; i++){
		two[i] = qpow(2LL, V[i]-1);
	}	
	pre[0] = suf[l+1] = 1;
	for (int i = 1; i <= l; i++){
		pre[i] = pre[i-1] * two[i] % MOD;
	}
	for (int i = l; i >= 1; i--){
		suf[i] = suf[i+1] * two[i] % MOD;
	}

	ll odds = 0;
	for (int i = 1; i < l; i++){
		// consider [i, i+1]
		if (who[i] == who[i+1]-1){
			ll fact = (pre[i-1]*suf[i+2] % MOD);
			if (V[i] % 2) fact = (fact * (two[i]-1) % MOD);
			else fact = (fact * two[i] % MOD);
			if (V[i+1] % 2) fact = (fact * (two[i+1]-1) % MOD);
			else fact = (fact * two[i+1] % MOD);
			odds = (odds + fact) % MOD;
		}
	}

	ll ans = odds % MOD + pre[l];
	ans = (ans * qpow(2LL, pref));

	return;
}

int main(){
	// fact[0] = inv[0] = 1;
	// for (int i = 1; i <= 200000; i++){
	// 	fact[i] = fact[i-1] * i % MOD;
	// 	inv[i] = inv[i-1] * qpow(i, MOD-2) % MOD;
	// }
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}