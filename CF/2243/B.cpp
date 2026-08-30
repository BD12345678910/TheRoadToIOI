#include <bits/stdc++.h>
using namespace std;

int n;
long long a[55];

void solve(){
	cin >> n;

	if (n == 2){
		cout << -1 << '\n';
		return ;
	}

	long long s = 3; 
	a[1] = 1; a[2] = 2;
	for (int i = 3; i <= n; i++){
		a[i] = s;
		s = s * 2;
	}
	for (int i = 1; i <= n; i++){
		cout << a[i] << ' ';
	}
	cout << '\n';
	return ;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}