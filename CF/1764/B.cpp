#include <bits/stdc++.h>
using namespace std;

int n, a[100005];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	int g = a[1];
	for (int i = 2; i <= n; i++){
		g = gcd(g, a[i]);
	}
	cout << a[n]/g << '\n';
}

int main(){
	int T; cin >> T;
	while (T--) solve();
}