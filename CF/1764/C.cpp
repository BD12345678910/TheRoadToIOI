#include <bits/stdc++.h>
using namespace std;

int n;
int a[200005];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	bool flag = 0;
	for (int i = 1; i <= n; i++){
		if (a[i]!=a[1]){
			flag = 1;
			break;
		}
	}
	if (!flag){
		cout << n/2 << '\n';
		return;
	} 
	sort(a+1, a+n+1);
	a[n+1] = 0;
	long long best = 0;
	for (int i = 1; i <= n; i++){
		if (a[i]==a[i+1]) continue;
		best = max(1LL*i*(n-i), best);
	}
	cout << best << '\n';
}

int main(){
	int T; cin >> T;
	while (T--) solve();
}