#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll qpow(ll x, ll n){
	ll res = 1;
	while (n){
		if (n & 1) res = res*x%MOD;
		x = x*x%MOD;
		n>>=1;
	}
	return res;
}

int n;
ll inv[2004];
int a[2004];

int main(){
	freopen("cross.in", "r", stdin);
	freopen("cross.out", "w", stdout);
	cin >> n;
	a[0] = -1;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}

	inv[0] = 1;
	for (int i = 1; i <= n; i++){
		inv[i] = inv[i-1]*qpow(i, MOD-2)%MOD;	
	}
	ll P = 1;
	for (int i = 1; i <= n; i++){
		P = P*inv[i]%MOD;
	}
	for (int i = 0; i < n; i++){
		for (int j = i+1; j <= n; j++){
			P = P*(a[j]-a[i]) % MOD;
		}
	}
	cout << P << endl;

	return 0;
}