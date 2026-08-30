#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1040;

int main(){
	freopen("02.in", "w", stdout);
	cout << N << endl;
	for (int i = 1; i <= N; i++){
		cout << rng()%2 << ' ';
	}
	cout << '\n';
	for (int i = 1; i <= N; i++){
		cout << rng()%2 << ' ';
	}
	cout << '\n';

	cout << N << endl;
	for (int i = 1; i <= N; i++){
		int t = rng() % N;
		int l = rng() % N;
		int r = rng() % N;
		if (l > r) swap(l, r);
		cout << t << ' ' << t << ' ' << l << ' ' << r << endl;
	}

	return 0;
}