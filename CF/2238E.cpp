// firstly, given a string, how to find the smallest mistakes?
// xoxoooxoxxoxoxooo
// A        B      C
// mistakes = lies in A + lies in C + truths in B
// mistakes = Ftotal - Fin + Tin
// Let Ftotal = M
// mistakes = M - (Fin-Tin)

// define bi := (si == 'lie')
// mistakes = M - sigma bi

// Chell's maximized mistakes = M - Smax

// dp(i, f, s): at i, total f fakes, s is maximum ending, dp = smallest Smax
// ans = max(f - Smax)

#include <bits/stdc++.h>
using namespace std;

int n, a[505], dp[505][505][505];

void mn(int &x, int y){
	if (y < x) x = y;
}

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		char c; cin >> c; 
		if (c == 'T') a[i] = -1;
		if (c == 'F') a[i] = 1;
		if (c == 'N') a[i] = 0;
	}
	for (int i = 0; i <= n; i++){
		for (int f = 0; f <= n; f++){
			for (int s = 0; s <= n; s++){
				dp[i][f][s] = 0x3f3f3f3f;
			}
		}
	}
	dp[0][0][0] = 0;
	for (int i = 0; i < n; i++){
		for (int f = 0; f <= i; f++){
			for (int s = 0; s <= i; s++){
				if (a[i+1] >= 0){
					mn(dp[i+1][f+1][s+1], max(dp[i][f][s], s+1));
				} 
				if (a[i+1] <= 0){
					int sp = max(s-1, 0);
					mn(dp[i+1][f][sp], dp[i][f][s]);
				}
			}
		}
	}
	int ans = 0;
	for (int f = 0; f <= n; f++){
		for (int s = 0; s <= n; s++){
			ans = max(ans,f-dp[n][f][s]);
		}
	}
	cout << ans << '\n';
	return;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}


