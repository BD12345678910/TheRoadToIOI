#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000005], c[1000005];
// take 0 through 30
long double coeff[31];

bool check(){
	for (int i = 1; i <= n; i++){
		if (a[i] != i || c[i] != i) return 0;
	}
	return 1;
}

int main(){
	freopen("champion.in", "r", stdin);
	freopen("champion.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	cout << setprecision(10) << fixed;

	if (n <= 5000){
		// sub 1-3
		for (int i = 1; i <= n; i++){
			long double ans = 0;
			for (int j = 1; j <= n; j++){
				ans += 1.0L*c[i]/(c[i]+a[j]);
			}
			cout << ans << ' ';
		}
		cout << endl;
	} else if (check()){
		// sub 4
		// first: 1/2+1/3+1/4+1/5+1/6+...
		// second: 2/3+2/4...
		long double ans = 0;	
		for (int i = 2; i <= n+1; i++){
			ans += (1.0L/i);
		}
		cout << ans << ' ';
		for (int i = 2; i <= n; i++){
			ans -= (1.0L/i);
			ans += (1.0L/(i+n));
			cout << ans*i << ' ';
		}
		cout << endl;
	} else {
		// assume c <= 1e7, a >= 1e8 (sub 67)
		// query(c) = n - sum(1 - (c/a) + (c/a)^2 -...)
		// converges quite quickly, take 30 terms to be safe
		for (int i = 1; i <= n; i++){
			long double curr = 1.0L;
			for (int j = 0; j <= 30; j++){
				coeff[j] += curr;
				curr = -(curr / a[i]);
			}
		}
		for (int i = 1; i <= n; i++){
			long double ans = 0;
			long double curr = 1.0L;
			for (int j = 0; j <= 30; j++){
				ans += coeff[j] * curr;
				curr = curr*c[i];
			}
			cout << (long double)n - ans << ' ';
		}
		cout << endl;
	}

	return 0;
}


