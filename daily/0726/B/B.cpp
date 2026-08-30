#include <bits/stdc++.h>
using namespace std;

int n, q;
char a[500005];
char ans[500005];
bool flip[500005];

int main(){
	freopen("excel.in", "r", stdin);
	freopen("excel.out", "w", stdout);
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= q; i++){
		int x; cin >> x;
		flip[x] = 1;
	}
	int suma = 0, sign = 1;
	for (int i = n; i >= 1; i--){
		if (flip[i]){
			suma += sign*(i+1);
			sign = -sign;
		}
		ans[suma+i*sign] = a[i];
	}
	for (int i = 1; i <= n; i++){
		cout << ans[i];
	}
	cout << endl;
	return 0;
}



