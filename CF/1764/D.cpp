#include <bits/stdc++.h>
using namespace std;
int n, p;
long long fact[15005];
int main(){
	cin >> n >> p;
	fact[0] = 1;
	for (int i = 1; i <= n; i++){
		fact[i] = fact[i-1]*i%p;
	}
	long long ans = 0;
	if (n % 2 == 0){
		int b = n/2-1;
		for (int l = 0; l <= b; l++){
			long long cnt = 0;
			for (int k = 1; k <= l+1; k++){
				if (l != 0 && k == 1) continue;
				(cnt += fact[n-k-1]) %= p;
			}
			cnt = cnt * (l+1) % p;
			ans = (ans + cnt) % p;
		}
		ans = ans * n % p;
		cout << ans << '\n';
	} else {
		int b = n/2;
		for (int l = 1; l <= b; l++){
			long long cnt = 0;
			for (int k = 2; k <= l+1; k++){
				(cnt += fact[n-k-1]) %= p;
			}
			cnt = cnt * l % p;
			ans = (ans + cnt) % p;
		}
		ans = ans * n % p;
		cout << ans << '\n';
	}
	return 0;
}