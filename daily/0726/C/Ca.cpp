#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(ll k, ll a, ll b, ll c, ll d){
	if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
	k -= d; k -= (c/2); c %= 2;
	if (c){
		if (b >= 2 && a >= 1){
			b -= 2;
			a -= 1;
			c -= 1;
			k--;
		} else if (b >= 1 && a >= 3){
			b -= 1;
			a -= 3;
			c -= 1;
			k--;
		} else if (a >= 5){
			a -= 5;
			c -= 1;
			k--;
		}
	}
	k -= (b/5);
	b %= 5;
	if (a + b*2 >= 10){
		a -= (10-2*b);
		b = 0;
		k--;
	}
	k -= (a/10);
	return k <= 0;
}

ll n, a, b, c, d, e;
ll x[500005];

bool solve(){
	cin >> n >> e >> a >> b >> c >> d;
	for (int i = 1; i <= n; i++){
		cin >> x[i];
	}
	for (int i = 1; i <= n; i++){
		if (x[i] % 2){
			e--;
			if (e < 0) return 0;
		}
		x[i] >>= 1;
	}
	a += (e/2);

	// the problem has been transformed:
	// a b c d, to sum to x
	// 1 2 5 10

	ll k = 0;
	int one = 0, elone = 0, six = 0;
	for (int i = 1; i <= n; i++){
		if (x[i] % 10 == 3 && b) {
			x[i] -= 2; b--;
		} 
		if (x[i] % 10 == 3 && a >= 2){
			x[i] -= 2; a-=2;
		}
		if (x[i] % 10 == 8 && b) {
			x[i] -= 2; b--;
		}
		if (x[i] % 10 == 8 && a >= 2){
			x[i] -= 2; a-=2;
		}
		if (x[i] % 10 == 1){
			one++;
			if (x[i] >= 10) elone++;
		} else if (x[i] % 10 == 6){
			six++;
		} else {
			if (c && x[i] % 10 >= 5){
				c--; x[i] -= 5;
			}
			for (int j = 0; j < 4; j++)
			if (b && x[i] % 10 >= 2){
				b--; x[i] -= 2;
			}
			for (int j = 0; j < 10; j++)
			if (a && x[i] % 10 >= 1){
				a--; x[i] -= 1;
			}
			if (x[i] % 10) return 0;
		}
		k += x[i]/10;
	}

	for (int eleven = 0; eleven <= elone; eleven++){
		if (check(k-eleven, a-(one-eleven), 
			b-3*eleven-3*six, c-eleven, d)) return 1;
	}
	for (int onefive = 0; onefive <= six; onefive++){
		if (check(k, a-onefive-one, 
			b-3*(six-onefive), c-onefive, d)) return 1;
	}

	return 0;
}

int main(){
	int T; cin >> T;
	while (T--) {
		if (solve()){
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
	return 0;
}
