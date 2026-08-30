#include <bits/stdc++.h>
using namespace std;

int n, a, b, c, d, e, ta, tb, tc, td, te;
int x[500005];

void solve(){
	cin >> n >> a >> b >> c >> d >> e;
	ta = a; tb = b; tc = c; td = d; te = e;
	for (int i = 1; i <= n; i++){
		cin >> x[i];
	}
	if (d == 0 && e == 0){
		for (int i = 1; i <= n; i++){
			int need = min(x[i]/4, c);
			c -= need;
			x[i] -= 4*need;
			need = min(x[i]/2, b);
			b -= need;
			x[i] -= 2*need;
			need = min(x[i], a);
			a -= need;
			x[i] -= need;
			if (x[i] > 0) {
				cout << "NO\n";
				return;
			}
		}
		cout << "YES\n";
		return;
	} else if (n == 3){
		// brute force assign 10s
		for (int i = 0; i <= min(d, x[1]/10); i++){
			x[1] -= 10*i;
			for (int j = 0; j <= min(d-i, x[2]/10); j++){
				x[2] -= 10*j;
 				for (int k = 0; k <= min(d-i-j, x[3]/10); k++){
 					x[3] -= 10*k;
 					bool work = 1;
 					a = ta, b = tb, c = tc, d = td, e = te;
 					for (int l = 1; l <= n; l++){
 						int y = x[l];
 						int need = min(y/20, e);
 						e -= need;
 						y -= 20*need;
 						need = min(y/4, c);
						c -= need;
						y -= 4*need;
						need = min(y/2, b);
						b -= need;
						y -= 2*need;
						need = min(y, a);
						a -= need;
						y -= need;
						if (y > 0) {
							work = 0;
							break;
						}
 					}
 					if (work){
 						cout << "YES\n";
 						return;
 					}
 					x[3] += 10*k;
				}
				x[2] += 10*j;
			}
			x[1] += 10*i;
		}
		cout << "NO\n";
		return;
	} else if (n == 2){
		// brute force assign 10s
		for (int i = 0; i <= min(d, x[1]/10); i++){
			x[1] -= 10*i;
			for (int j = 0; j <= min(d-i, x[2]/10); j++){
				x[2] -= 10*j;
				bool work = 1;
 				a = ta, b = tb, c = tc, d = td, e = te;
				for (int l = 1; l <= n; l++){
					int y = x[l];
					int need = min(y/20, e);
					e -= need;
					y -= 20*need;
					need = min(y/4, c);
					c -= need;
					y -= 4*need;
					need = min(y/2, b);
					b -= need;
					y -= 2*need;
					need = min(y, a);
					a -= need;
					y -= need;
					if (y > 0) {
						work = 0;
						break;
					}
				}
				if (work){
					cout << "YES\n";
					return;
				}
				x[2] += 10*j;
			}
			x[1] += 10*i;
		}
		cout << "NO\n";
		return;
	} else if (n == 1){
		// brute force assign 10s
		for (int k = 0; k <= min(d, x[1]/10); k++){
			x[1] -= 10*k;
			bool work = 1;
 			a = ta, b = tb, c = tc, d = td, e = te;
			for (int l = 1; l <= n; l++){
				int y = x[l];
				int need = min(y/20, e);
				e -= need;
				y -= 20*need;
				need = min(y/4, c);
				c -= need;
				y -= 4*need;
				need = min(y/2, b);
				b -= need;
				y -= 2*need;
				need = min(y, a);
				a -= need;
				y -= need;
				if (y > 0) {
					work = 0;
					break;
				}
			}
			if (work){
				cout << "YES\n";
				return;
			}
			x[1] += 10*k;
		}
		cout << "NO\n";
		return;
	} else {
		cout << "YES\n";
	}
}

int main(){
	freopen("trust.in", "r", stdin);
	freopen("trust.out", "w", stdout);
	int T; cin >> T;
	while (T--) solve();
}



