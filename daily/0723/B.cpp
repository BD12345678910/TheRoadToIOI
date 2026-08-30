#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int n;
int b[100005];
int c[100005][11];
int s[100005];
bool dp[100005][11][11];
int last[100005][11][11];
int a[100005];

void add(int x, int y){
	if (y > 1 && y < n){
		c[x][s[x]++] = b[y];
		if (b[y] > 0) c[x][s[x]++] = b[y]-1;
		if (b[y] < INF) c[x][s[x]++] = b[y]+1;
	}
}

int med(int x, int y, int z){
	if (z > y) swap(y, z);
	if (y > x) swap(x, y);
	return max(y, z);
}

void solve(){
	cin >> n;
	for (int i = 2; i < n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++){
		s[i] = 0;
		add(i, i-1); add(i, i); add(i, i+1);
		c[i][s[i]++] = 0;
		c[i][s[i]++] = INF;
	}

	memset(dp[2], 0, sizeof(dp[2]));
	for (int i = 0; i < s[1]; i++){
		for (int j = 0; j < s[2]; j++){
			dp[2][i][j] = 1;
		}
	}
	for (int i = 3; i <= n; i++){
		memset(dp[i], 0, sizeof(dp[i]));
		for (int j = 0; j < s[i-2]; j++){
			int two = c[i-2][j];
			for (int k = 0; k < s[i-1]; k++){
				if (!dp[i-1][j][k]) continue;
				int one = c[i-1][k];
				for (int e = 0; e < s[i]; e++){
					if (dp[i][k][e]) continue;
					int me = c[i][e];
					if (b[i-1] == med(two, one, me)){
						dp[i][k][e] = 1;
						last[i][k][e] = j;
					}
				}
			}
		}
	}

	int aj = -1, ak = -1;
	for (int j = 0; j < s[n-1]; j++){
		for (int k = 0; k < s[n]; k++){
			if (dp[n][j][k]){
				aj = j;
				ak = k;
			}
		}
	}

	if (aj == -1 && ak == -1){
		cout << -1 << '\n';
		return;
	}

	for (int i = n; i >= 3; i--){
		int ai = last[i][aj][ak];
		a[i] = c[i][ak];
		ak = aj;
		aj = ai;
	}
	a[1] = c[1][aj];
	a[2] = c[2][ak];
	for (int i = 1; i <= n; i++){
		cout << a[i] << ' ';
	}
	cout << '\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("median.in", "r", stdin);
	freopen("median.out", "w", stdout);
	// auto start = chrono::steady_clock::now();
	int T; cin >> T;
	while (T--) solve();
	// auto finish = chrono::steady_clock::now();
	// cerr << "Time: " << chrono::duration<double, milli>(finish - start).count() << " ms\n";
	return 0;
}



