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
	int prev = -1, cnt = 0, d = 0;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if (a[i]==-1) pref++;
		else {
			if (a[i] != prev){
				if (a[i]-prev == 1) d++;
				V.push_back(cnt);
				who.push_back(prev);
				prev = a[i];
				cnt = 1;
			} else {
				cnt++;
			}
		}
	}
	V.push_back(cnt);
	who.push_back(prev);

	int l = V.size()-1;
	ll ans = 0;
	ll P = 1;
	for (int i = 1; i <= l; i++){
		two[i] = qpow(2LL, V[i]-1);
		P = P*two[i]%MOD;
	}

	if (pref > 0){
		ans = qpow(2LL, pref-1) * P % MOD;
		ans = ans*(1+d)%MOD;
	} else {
		ans = P;
	}
	cout << ans << endl;

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