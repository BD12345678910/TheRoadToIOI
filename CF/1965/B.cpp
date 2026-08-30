#include <bits/stdc++.h>
using namespace std;

int n, k;
int ans[26];

void solve(){
	cin >> n >> k;
	int og = k; k--;
	int i;
	for (i = 1; i <= 21; i++){
		if (k >= (1<<(i-1))) {
			ans[i] = (1<<(i-1));
			k -= (1<<(i-1));
		} else {
			break;
		}
	}
	i--;
	if (k) ans[++i] = k;
	ans[++i] = og+1;
	ans[++i] = 3*og;
	while (og*2 <= n){
		og <<= 1;
		ans[++i] = og;
	}
	cout << i << '\n';
	for (int j = 1; j <= i; j++){
		cout << ans[j] << ' ';
	}
	cout << '\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}