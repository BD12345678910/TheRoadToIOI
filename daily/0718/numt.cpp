#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p; int q;

ll qpow(ll x, ll n){
	ll res = 1;
	while (n){
		if (n & 1) res = res * x % p;
		x = x * x % p;
		n >>= 1;
	}
	return res;
}

ll a, b, c, d;

int main(){	
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	cin >> p >> q;
	while (q--){
		cin >> a >> b >> c >> d;
		if ((a+b)%p != (c+d)%p){
			cout << -1 << '\n';
		} else {
			if (a == c && b == d){
				cout << 0 << '\n';
				continue;
			}
			ll Dopp = qpow((a+b)%p, p-2);
			for (int n = 1; n <= 1000; n++){
				ll k = (qpow(2, n) * a % p - c + p) % p * Dopp % p;
				if (n >= 40 || k < (1LL<<n)){
					cout << n << '\n';
					break;
				}
			}
		}
	}
}



