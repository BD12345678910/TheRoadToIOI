#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<int> G[202];
int d[202][202];

const int MOD = 1000000007;

ll qpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r=r*a%MOD;
        a = a*a%MOD;
        e >>= 1;
    }
    return r;
}

ll inv(ll x) { return qpow(x, MOD - 2);}

void dfs(int x, int pa, int di, int me){
	d[me][x] = d[x][me] = di;
	for (int v : G[x]){
		if (v == pa) continue;
		dfs(v, x, di+1, me);
	}
}

ll p[202][202];

int main(){
	ll inv2 = inv(2);
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b); 
		G[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) dfs(i, i, 0, i);

	for (int i = 1; i <= n; i++) {
		p[0][i] = 1; 
		p[i][0] = 0;
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			p[i][j] = (p[i][j-1]+p[i-1][j])*inv2%MOD;
		}
	}

	ll ans = 0;
	for (int i = 1; i < n; i++){
		for (int j = i+1; j <= n; j++){
			for (int k = 1; k <= n; k++){
				// i < j
				// we want P(i later than j)
				// dist[jk] , dist[ik]
				int A = d[i][j];
				int B = d[i][k];
				int C = d[j][k];
				int di = (B+A-C)/2;
				int dj = (C+A-B)/2;
				(ans += p[dj][di]) %= MOD;
			}
		}
	}
	ans = ans * inv(n) % MOD;
	cout << ans << endl;
	return 0;
}



