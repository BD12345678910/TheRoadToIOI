#include <bits/stdc++.h>
using namespace std;

int n, a[200005];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	sort(a+1, a+n+1);
	vector<int> diff;
	a[0] = 0;
	for (int i = 1; i <= n; i++){
		if (a[i] != a[i-1]) diff.push_back(a[i]-a[i-1]);
	}
	reverse(diff.begin(), diff.end());
	bool state = 0;
	for (int x: diff){
		if (state == 0) state = 1;
		else {
			if (x == 1) state = 0;
			else state = 1;
		}
	}
	if (state) cout << "Alice\n";
	else cout << "Bob\n";
	return;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}