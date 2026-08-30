#include <bits/stdc++.h>
using namespace std;

int n;
long long a[1000006];

void solve(){
	cin >> n;
	long long x = 0;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		x = x^a[i];
	}
	if (n == 1) {cout << 0 << '\n'; return;}
	int ans = 0;
	for (int i = 1; i <= n; i++){
		x = x^a[i];
		if (x == a[i]){
			cout << 1 << '\n';
			return;
		}
		if (x < a[i]) ans++;
		x = x^a[i];
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