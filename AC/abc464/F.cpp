#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353; 
int n;
ll a[43], x, tot;
ll C[45][45];
ll inv[45];

ll pw(ll a, ll b){
    ll r = 1;
    while(b){
        if (b&1) r=r*a%MOD;
        a = a*a%MOD;
        b >>= 1;
    }
    return r;
}

int main(){
	cin >> n >> x;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		tot += a[i];
	}
	int n1 = n/2, n2 = n-n1;

	vector<vector<ll>> R(n2+1), pref(n2+1);
	for (int m = 0; m < (1<<n2); m++){
		ll s = 0; int c = 0;
		for (int i = 0; i < n2; i++){
			if (m >> i & 1){
				s += a[n1+1+i], c++;
			}
		}
		R[c].push_back(s);
	}
	for (int i = 0; i <= n2; i++){
		sort(R[i].begin(), R[i].end());
		pref[i].assign(R[i].size()+1, 0);
		for (int j = 0; j < (int)R[i].size(); j++){
			pref[i][j+1] = (pref[i][j]+R[i][j])%MOD;
		}
	}

	for (int i = 0; i < n; i++){
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++){
			C[i][j] = (C[i-1][j-1]+C[i-1][j])%MOD;
		}
	}

	for (int k = 0; k < n; k++){
		inv[k] = pw(n*C[n-1][k]%MOD, MOD-2);
	}

	ll ans = 0;
	for (int m = 0; m < (1<<n1); m++){
		ll s = 0; int c = 0;
		for (int i = 0; i < n1; i++){
			if (m >> i & 1){
				s += a[i+1], c++;
			}
		}
		for (int rc = 0; rc <= n2; rc++){
			int k = c+rc;
			if (k == n) continue;
			// number of other half subsets with sum < X
			int t = lower_bound(R[rc].begin(), R[rc].end(), x-s)-R[rc].begin();
			ll tmp = (tot-s)%MOD*t%MOD;
			tmp = (tmp-pref[rc][t]+MOD)%MOD;
			ans = (ans + tmp*inv[k]%MOD)%MOD;
		}
	}
	cout << ans << endl;

	return 0;
}








