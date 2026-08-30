#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// N, Q <= 5e5, K <= 1e14, a <= 1e9
int n, Q; ll K;
ll a[500005];
ll P[500005];
int go[500005][20];
ll take[500005][20];
set<pair<ll,int>> S;

ll residue(ll x){
	return ( x % K + K) % K;
}

void discard(ll l, ll r, int i){
	set<pair<ll,int>>::iterator it = S.lower_bound({l, -1});
	while (it != S.end() && it->first <= r){
		// remove it:
		int start = it->second;
		go[start][0] = i+1;
		take[start][0] = (P[i-1]-P[start-1])/K;
		it = S.erase(it);
	}
}

int main(){
	cin >> n >> Q >> K;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		if (i % 2 == 0) a[i] = -a[i];
		go[i][0] = n+2;
	}
	go[n+1][0] = go[n+2][0] = n+2;

	P[0] = 0;
	for (int i = 1; i <= n; i++){
		P[i] = (P[i-1]+a[i]);
	}
	// i+1 for n!!
	for (int i = 1; i <= n; i++){
		if (i % 2){
			S.insert({residue(P[i-1]), i});
		} else {
			go[i][0] = i+1;
			take[i][0] = 0;
			ll t = residue(P[i-1]);
			ll d = -a[i];
			if (d >= K-1){
				discard(0, K-1, i);
			} else {
				ll start = residue(t-d);
				// [start, t]
				if (start <= t){
					discard(start, t, i);
				} else {
					discard(start, K-1, i);
					discard(0, t, i);
				}
			}
		}
	}
	for (int i = 1; i <= 19; i++){
		for (int j = 1; j <= n+2; j++){
			go[j][i] = go[go[j][i-1]][i-1];
			take[j][i] = take[j][i-1] + take[go[j][i-1]][i-1];
		}
	}
	while (Q--){
		int l, r; cin >> l >> r;
		ll ans = 0;
		for (int i = 19; i >= 0; i--){
			if (go[l][i] <= r+1){
				ans += take[l][i];
				l = go[l][i];
			}
		}
		if (l <= r) ans += (P[r]-P[l-1])/K;
		cout << ans << '\n';
	}

	return 0;
}




