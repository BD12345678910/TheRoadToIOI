#include <bits/stdc++.h>
using namespace std;

long long n;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--){
		cin >> n;
		long long k = sqrtl(n);
		long long rem = n - k * k;
		long long ans = 2LL*k*(k-1);

		if (rem && rem > k){
			ans += rem;
			ans += (rem-2);
		} else if (rem) {
			ans += rem;
			ans += (rem-1);
		}
		cout << ans << '\n';
	}


	return 0;
}