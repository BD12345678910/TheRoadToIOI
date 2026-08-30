#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now.time_since_epoch().count());
const int n = 50;
const int q = 20;

int main(){
	freopen("02.in", "w", stdout);
	cout << n << ' ' << q << endl;
	for (int i = 0; i < n; i++){
		cout << rng()%20+1 << ' ';
	}
	cout << endl;
	for (int i = 0; i < n; i++){
		cout << rng()%10+1 << ' ';
	}
	cout << endl;
	for (int i = 0; i < n; i++){
		
		cout << rng()%(n-1)
	}


	return 0;
}