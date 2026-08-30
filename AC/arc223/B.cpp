#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
const int N = 200000;
int n, k;
int a[200005];
int cnt[2];

ll fac[200005], ifac[200005];

ll qpow(ll a,ll b){
    ll r=1;
    for(;b;b>>=1,a=a*a%MOD) if(b&1) r=r*a%MOD;
    return r;
}

void init(){
    fac[0]=1;
    for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i%MOD;
    ifac[N]=qpow(fac[N],MOD-2);
    for(int i=N;i;i--) ifac[i-1]=ifac[i]*i%MOD;
}

ll C(int n,int k){
    if(k<0||k>n) return 0;
    return fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}

void solve(){
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	cnt[0] = cnt[1] = 0;
	int curr = 0x3f3f3f3f;
	map<int,int> M;
	ll ans = 1; int t = 0;
	for (int i = 1; i <= n; i++){
		int g = a[i]%k;
		if (g == curr && ((g*2 == k) || (g == 0))){
			M[a[i]]++;
			t++;
			continue;
		}
		if (g == curr){
			cnt[0]++;
			continue;
		}
		if (g == k-curr){
			cnt[1]++;
			continue;
		} 

		if (curr*2 == k || (curr == 0)){
			for (auto [u, v]: M){
				ans = ans * C(t, v) % MOD;
				t -= v;
			}
		} else {
			ans = ans * C(cnt[0]+cnt[1], cnt[1]) % MOD;
		}

		curr = g;
		cnt[0] = 0;
		cnt[1] = 0;
		t = 0;
		M.clear(); 
		if (g*2 == k || g == 0){
			M[a[i]]++;
			t++;
		} else {
			cnt[0]++;
		}
	}

	if (curr*2 == k || curr == 0){
		for (auto [u, v]: M){
			ans = ans * C(t, v) % MOD;
			t -= v;
		}
	} else {
		ans = ans * C(cnt[0]+cnt[1], cnt[1]) % MOD;
	}

	cout << ans << '\n';
	return;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	init();
	while (T--) solve();

	return 0;
}