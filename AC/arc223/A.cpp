#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; ll W;
ll w[65], v[65], s[65];

ll go(int x, ll rem){
	if (x == 1){
		if (w[x] <= rem) return v[x];
		else return 0;
	}
	if (w[x] > rem) return go(x-1, rem);
	return max(go(x-1, rem-w[x])+v[x], s[x-1]);
}

void solve(){
	cin >> n >> W;
	for (int i = 1; i <= n; i++){
		cin >> w[i] >> v[i];
		s[i] = s[i-1]+v[i];
	}
	ll ans = go(n, W);
	cout << ans << '\n';
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();

	return 0;
}