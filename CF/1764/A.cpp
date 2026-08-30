#include <bits/stdc++.h>
using namespace std;

int n;
int a[100005];
void solve(){
	cin >> n;
	for (int i =1 ; i <= n; i++){
		cin >> a[i];
	}
	cout << 1 << ' ' << n << '\n';
}

int main(){
	int T; cin >> T;
	while (T--) solve();
	return 0;
}