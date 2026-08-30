#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[200005], b[200005];

void solve(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> b[i];

	if ((n-m)%2){
		cout << "No\n";
		return;
	}
	if (a[n]-a[1] != b[m]-b[1]){
		cout << "No\n";
		return;
	}
	int acnt = 0;
	for (int i = 1; i < n; i++){
		if (a[i+1]==a[i]) acnt++;
	}
	int bcnt = 0;
	for (int i = 1; i < m; i++){
		if (b[i+1]==b[i]) bcnt++;
	}
	if (acnt != bcnt){
		cout << "No\n";
		return;
	}
	cout << "Yes\n";
	return ;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}