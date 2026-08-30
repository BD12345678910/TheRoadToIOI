#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
int n;
int a[100005];
int xx[100005];
ll gans;
int odd[100005], even[100005];

int f(int x){
	return (31-__builtin_clz(x)) + __builtin_popcount(x);
}

void solve(){
	cin >> n; gans = INF;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int c = 1; c <= 17; c++){
		int common = 1<<c;
		bool flag = 0;
		for (int i = 1; i <= n; i++){
			xx[i] = (a[i]+common-1)/common;
			if (xx[i]&1) flag = 1;
		}
		ll ans = c; int penalty = INF;
		for (int i = 1; i <= n; i++){
			ans += common * xx[i] - a[i] + f(xx[i]);
			penalty = min(penalty, common+f(xx[i]+1)-f(xx[i]));
		}
		if (flag) gans = min(gans, ans);
		else gans = min(gans, ans + penalty);
	}

	bool flag = 0;
	int penalty = INF; ll ans = 0;
	for (int i = 1; i <= n; i++){
		ans += min(odd[a[i]], even[a[i]]);
		if (odd[a[i]] <= even[a[i]]) flag = 1;
		penalty = min(penalty, odd[a[i]]-even[a[i]]);
	}
	if (flag) gans = min(gans, ans);
	else gans = min(gans, ans + penalty);
	cout << gans << '\n';

	return ;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int mnodd = INF, mneven = INF;
	for (int i = 200000; i >= 1; i--){
		int val = i + f(i);
		if (i & 1) mnodd = min(mnodd, val);
		else mneven = min(mneven, val);
		if (i <= 100000){
			odd[i] = mnodd-i;
			even[i] = mneven-i;
		}
	}
	int T; cin >> T;
	while (T--) solve();
	return 0;
}