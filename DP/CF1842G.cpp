#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7;
int n, m, v;
int a[5005];
int f[5005][5005];
int inv[5005];

int pow(int x, int nn){
	int r = 1;
	while (nn){
		if (nn & 1) r = 1LL*r*x%M;
		x = 1LL*x*x%M; 
		nn >>= 1;
	}
	return r;
}

int main(){
	cin >> n >> m >> v;
	inv[0] = 1; int invv = pow(n, M-2);
	for (int i = 1; i <= n; i++){
		inv[i] = 1LL*inv[i-1]*invv%M;
	}
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	f[0][0] = 1;
	for (int i = 0; i < n; i++){
		for (int j = 0; j <= min(i, m); j++){
			(f[i+1][j] += 1LL*f[i][j]*a[i+1]%M) %= M;
			(f[i+1][j] += 1LL*f[i][j]*v%M*j%M) %= M;
			(f[i+1][j+1] += 1LL*f[i][j]*(i+1)%M*(m-j)%M*v%M) %= M;
		}
	}
	int ans = 0;
	for (int i = 0; i <= min(n, m); i++){
		ans = (ans + 1LL*f[n][i]*inv[i]%M) % M;
	}
	cout << ans << endl;

	return 0;
}