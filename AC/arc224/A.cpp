#include <bits/stdc++.h>
using namespace std;

int k;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--){
		cin >> k;
		for (int i = 1; i <= 100; i++){
			long long N = 1LL*k*i;
			int cnt = 0;
			bool found = 0;
			while (N > 0){
				if (N % 10 == 0) cnt++;
				else cnt = 0;
				if (cnt >= 2) found = 1;
				N = N / 10;
			}
			if (found) {
				cout << 1LL*k*i << '\n';
				break;
			}
		}
	}
	
	return 0;
}