#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
mt19937 rng(2772);

int main(){
	freopen("median.in", "w", stdout);
	cout << 10 << endl;
	for (int t = 1; t <= 10; t++){
		cout << N << endl;
		for (int i = 2; i < N; i++){
			cout << rng()%1000000001 << ' ';
		}
		cout << endl;
	}

	return 0;
}