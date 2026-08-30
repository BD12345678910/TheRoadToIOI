#include <bits/stdc++.h>
using namespace std;

mt19937 rng(18439);
const int n = 100000;

int main(){
	freopen("01.in", "w", stdout);
	cout << n << endl;
	vector<pair<int,int>> P;
	for (int i = 1; i <= n/2; i++){
		P.push_back({2, 2*i});
	}
	for (int i = 1; i <= n/2; i++){
		P.push_back({4, 2*i});
	}
	shuffle(P.begin(), P.end(), rng);
	for (int i = 0; i < n; i++){
		cout << P[i].first << ' ' << P[i].second << '\n';
	}
}