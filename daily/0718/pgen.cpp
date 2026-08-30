#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int n = 100;

int main(){
	freopen("prop.in", "w", stdout);
	cout << n << ' ' << 28 << '\n';
	for (int i = 1; i <= n; i++){
		cout << rng()%200000 << ' ';
	}
	cout << '\n';

	return 0;
}