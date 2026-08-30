#include <bits/stdc++.h>
using namespace std;

int n, k;
long long capacity[1000006];

void solve(){
	cin >> n >> k;
	if (n <= 20 && (1<<n)<k) {
		cout << -1 << '\n';
		return ;
	}
	long long su = 0; int en = n;
	long long c = 1; capacity[0] = 1;
	for (int i = 1; i <= n; i++){
		c = c * (n-i+1) / i;
		if (su + c > k) {
			capacity[i] = k-su;
			en = i; break;
		} else {
			capacity[i] = c;
		}
		su += c;
	}
	int curr = k;
	long long ans = 0;
	for (int i = 0; i <= en; i++){
		for (int x = 1; x <= capacity[i]; x++){ 
			int len = 0, cl = curr;
			while (cl){
				cl = cl / 10; 
				len++;
			}
			// cout << curr << ' ' << len << ' ' << i << endl;
			ans += 1LL * len * i; 
			curr--;
			if (curr == 0) break;
		}
		if (curr == 0) break;
	}
	cout << ans << '\n';
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}