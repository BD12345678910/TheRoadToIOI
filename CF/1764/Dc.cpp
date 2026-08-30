#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, p;
ll fact[5005], inv[5005];
ll f[5005];

ll poww(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r=r*a%p;
        a = a*a%p;
        e >>= 1;
    }
    return r;
}

ll comb(int n, int k){
	return fact[n]*inv[k]%p*inv[n-k]%p;
}

int main(){
	cin >> n >> p;
	fact[0] = 1;
	for (int i = 1; i <= n; i++){
		fact[i] = fact[i-1]*i%p;
	}
	inv[0] = 1;
	for (int i = 1; i <= n; i++){
		inv[i] = inv[i-1]*poww(i, p-2)%p;
	}
	int b = n/2;
	f[b-1] = 0;
	for (int i = b; i < n; i++){
		f[i] = n*fact[i]%p;
		f[i] = f[i]*comb(n-1-b, i-b)%p;
	}
	f[n] = fact[n];
	ll ans = 0;
	for (int k = b; k <= n-1; k++){
		ans = (ans + f[k] - f[k-1]*(n-(k-1))%p + p) % p;
	}
	cout << ans << '\n';

	return 0;
}

