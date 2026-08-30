#include <bits/stdc++.h>
using namespace std;

int n;
int a[55];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i+=2){
		a[i] = i+1;
		a[i+1] = i;
	}
	for (int i = 1; i <= n;i++){
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