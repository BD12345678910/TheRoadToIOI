#include <bits/stdc++.h>
using namespace std;

int q;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> q;
	while (q--){
		long long op, c, T;
		cin >> op >> c >> T;
		if (op == 1){
			long long t = c, p = c;
			while (t < T){
				++t;
				if (p == 0){
					p = t/2;
				} else if (p <= t/2){
					p--;
					if (p >= T-t){
						p -= (T-t);
						break;
					} else {
						t += p;
						p = 0;
					}
				} else {
					t = 2*p-1;
				}
			}
			cout << p << '\n';
		} else {
			long long t = T, p = c;
			while (t > 0){
				if (p > t/2) break;
				else if (p == t/2) {
					p = 0;
					t--;
				} else {
					long long k = max(1LL, (t-2*p)/3);
					p += k;
					t -= k;
				}
			}
			cout << p << '\n';
		}
	}
	return 0;
}