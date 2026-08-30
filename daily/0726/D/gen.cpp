#include <bits/stdc++.h>
using namespace std;
const int Bd = 100000000;
const int B = 900000000;
mt19937 rng(132893);
int n;


int main(){
	freopen("02.in", "w", stdout);
	n = 5000;
	cout << n << endl;
	for (int i = 1; i <= n; i++){
		cout << rng()%B+Bd << ' ';
	}
	cout << endl;
	for (int i = 1; i <= n; i++){
		cout << rng()%10000000+1 << ' ';
	}
	cout << endl;

	return 0;
}