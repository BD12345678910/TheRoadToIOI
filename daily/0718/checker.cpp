#include <bits/stdc++.h>
using namespace std;

int n;
int a[105];

int main(){
	freopen("prop.out", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	int x; cin >> x;
	int s = 0;
	for (int i = 1; i <= x; i++){
		int t; cin >> t;
		s += a[t];
	}
	cin >> x;
	for (int i = 1; i <= x; i++){
		int t; cin >> t;
		s-= a[t];
	}
	cout << s << endl;
	return 0;
}