#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll qpow(ll a,ll b){
    ll r=1;
    for(;b;b>>=1,a=a*a%n) if(b&1) r=r*a%n;
    return r;
}
int a[200005];
int r[200005];

int t[200005];
int qry(int x){
	x++;
	int s = 0;
	for (int i = x; i; i -= i&(-i)){
		s += t[i];
	}
	return s;
}
void upd(int x){
	x++;
	for (int i = x; i <= n; i += i&(-i)){
		t[i]++;
	}
}

void solve(){
	cin >> n;
	for (int i = 0; i <= n; i++) r[i] = 0, t[i] = 0;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 2; i*i <= n; i++){
		if (n % i == 0) {
			cout << 0 << '\n';
			return;
		}
	}
	sort(a+1, a+n+1);
	for (int i = 1; i <= n; i++){
		if (r[a[i]%n]) {
			cout << 0 << '\n';
			return;
		}
		r[a[i]%n] = 1;
	}
	for (int i = 1; i <= n; i++){
		r[i] = a[i]%n;
	}
	// find the number of inversions.
	ll cnt = 0;
	for (int i = 1; i <= n; i++){
		cnt += (i-1-qry(r[i]));
		upd(r[i]);
	}
	ll ans = 1;
	for (int i = 1; i <= n; i++){
		ans = ans*qpow(i, n-i)%n;
	}
	if (cnt % 2){
		ans = (n-ans)%n;
	} 
	cout << ans << '\n';
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--){
		solve();
	}
	return 0;
}