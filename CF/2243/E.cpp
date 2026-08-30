#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int o, r;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--){
		cout << 1 << endl;
		cin >> o;
		if (o > 1){
			cout << 0 << ' ' << 2 << endl;
			cin >> r;
			cout << ((r|1)==o?0:1) << endl;
		} else if (o == 0){
			cout << 0 << ' ' << 1 << endl;
			cin >> r;
			cout << (r & 1) << endl;
		} else {
			int d = ((rng()%((1<<29)-1)+1)<<1)|1;
			cout << 0 << ' ' << d << endl;
			cin >> r;
			if (r <= 1) cout << 0 << endl;
			else if ((r^d) <= 1) cout << 1 << endl;
			else cout << !(r & 1) << endl;
		}
	}
	return 0;
}