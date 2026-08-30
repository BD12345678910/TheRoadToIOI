#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
const int MAXN = 105;

ll qpow(ll a, ll e){
	ll r = 1;
	while (e){
		if (e & 1) r = r * a % MOD;
		a = a * a % MOD; 
		e >>= 1;
	}
	return r;
}

// new stuff: Gaussian elimination to upper
// triangular to obtain determinant
// two main operations, row add and row swap
// swap multiplies determinant by -1

// complexity: N^3!
ll DET(vector<vector<ll>> a){
	int n = (int) a.size();
	ll ans = 1;
	// for each column we wish to make
	// a[col][col] nonzero and all below it 
	// zero
	for (int col = 0; col < n; col++){
		int pivot = col;
		while (pivot < n && a[pivot][col] == 0) {
			pivot++;
		}
		if (pivot == n) return 0;
		if (pivot != col){
			swap(a[pivot], a[col]);
			ans = (MOD-ans) % MOD;
		}
		ans = ans * a[col][col] % MOD;
		ll inv = qpow(a[col][col], MOD-2);
		// keep eliminating below
		for (int row = col+1; row < n; row++){
			ll coef = a[row][col] * inv % MOD;
			for (int j = col; j < n; j++){
				a[row][j] = (a[row][j] - coef * a[col][j]) % MOD;
				if (a[row][j] < 0) a[row][j] += MOD;
			}
		}
	}
	return ans;
}

ll fact[MAXN];
int n, k; string type;
char adj[MAXN][MAXN];
ll lap[MAXN][MAXN];
int outdeg[MAXN];

void solve(){
	cin >> n >> k;
	cin >> type;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> adj[i][j];
		}
	}

	int A = n, B = n+1, V = n+2;

	for (int i = 0; i <= B; i++){
		outdeg[i] = 0;
		for (int j = 0; j <= B; j++){
			lap[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (adj[i][j] == '1'){
				lap[i][i]=(lap[i][i]+1)%MOD;
				lap[i][j]=(lap[i][j]-1+MOD)%MOD;
			}
		}
	}
	// matrix tree preparation
	int S = 0;
	for (int i = 0; i < n; i++){
		if (type[i] == 'S'){
			lap[A][A]=(lap[A][A]+1)%MOD;
			lap[A][i]=(lap[A][i]-1+MOD)%MOD;
			S++;
		}
		if (type[i] == 'R'){
			lap[i][i]=(lap[i][i]+1)%MOD;
			lap[i][B]=(lap[i][B]-1+MOD)%MOD;
		}
	}
	lap[B][B]=(lap[B][B]+S)%MOD;
	lap[B][A]=(lap[B][A]-S+MOD)%MOD;
	
	// prepare to remove row A
	vector<vector<ll>> minor;
	for (int i = 0; i < V; i++){
		if (i == A || lap[i][i]==0) continue;
		vector<ll> row;
		for (int j = 0; j < V; j++){
			if (j == A || lap[j][j]==0) continue;
			row.push_back(lap[i][j]);
		}
		minor.push_back(row);
	}

	// number of spanning trees going into node A
	// by matrix tree theorem
	ll ans = DET(minor);
	for (int i = 0; i < n; i++){
		if (lap[i][i] > 0)
		ans = ans * fact[lap[i][i]-1] % MOD;
	}
	ans = ans * qpow(S, MOD-2) % MOD;
	cout << ans << '\n';

	// ans = #eulerian circuits * S (the starting direction on A)
	// divided by S! (permutations of the S originally intended paths)
	// divided by S! (permutations of the S routes from B to A)
	// = T * product of outdeg missing A and B / S

}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++){
		fact[i] = fact[i-1] * i % MOD;
	}
	int T; cin >> T;
	while (T--) solve();
}



