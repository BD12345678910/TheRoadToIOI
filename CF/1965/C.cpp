#include <bits/stdc++.h>
using namespace std;
const int D = 200000;
int n, k;
bool a[200005];
bool nl[400005];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		char c; cin >> c;
		a[i] = (c=='1');
	}
	nl[D] = a[1];
	int curr = 0, mn = 0, mx = 0;
	for (int i = 2; i <= n; i++){
		// cout << curr << endl;
		if (mn-1 < curr && curr < mx){
			if (a[i]==nl[curr+D]){
				curr--;
			} else {
				curr++;
			}
		} else if (curr == mn-1){
			if (a[i]==nl[curr+1+D]){
				curr++;
			} else {
				curr--; mn--;
				nl[mn+D] = a[i];
			}
		} else if (curr == mx){
			if (a[i]==nl[curr+D]){
				curr--;
			} else {
				curr++; mx++;
				nl[mx+D] = a[i];
			}
		}
	}
	cout << mx-mn+1 << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}