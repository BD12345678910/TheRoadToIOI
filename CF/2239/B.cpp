#include <bits/stdc++.h>
using namespace std;

int n, d;
long long a[400005];

void solve(){
	cin >> n >> d;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		a[i+n] = a[i];
	}

	long long s = 0;
	for (int i = 1; i <= d; i++) s+=a[i];
	for (int i = d+2; i <= d+d+1; i++) s+=a[i];
	long long ans = 0;
	for (int i = d+1; i <= d+n; i++){
		long long ci = 2LL*d*a[i]-s;
		if (ci > 0) ans += ci;
		s += a[i]; s -= a[i+1];
		s -= a[i-d];
		s += a[i+d+1];
	}
	cout << ans << '\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	while (T--) solve();

	return 0;
}