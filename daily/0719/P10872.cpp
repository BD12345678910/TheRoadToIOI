#include <bits/stdc++.h>
using namespace std;

int n, k, l;

int main(){
	cin >> n >> k >> l;
	cout << (1LL * l * k + n - 1) / n << endl;
	for (int i = 1; i <= k; i++){
		cout << 1;
	}
	for (int i = k+1; i <= n; i++){
		cout << 0;
	}
	cout << endl;
	for (int i = 1; i <= n; i++){
		cout << (1LL*i*l/n)-(1LL*(i-1)*l/n);
	}
	cout << endl;

	return 0;
}