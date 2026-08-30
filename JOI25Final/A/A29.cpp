// K <= 10

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q;
ll a[500005], K;
// nxt[i][j][mod] gives mod', which is the position it leads to: (j+2, mod') 
int nxt[20][500005][10];
// dp[i][j][mod] gives the number of satisfactiuons collected on the way
ll dp[20][500005][10];
// total: 120MB

int main(){
	cin >> n >> q >> K;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	// consider the sweet parts:
	memset(nxt,-1,sizeof(nxt));
	for (int i = 1; i <= n; i += 2){
		for (int k = 0; k < min(K, a[i]); k++){
			nxt[0][i][k] = (a[i]-k+K)%K;
			dp[0][i][k] = (a[i]-k+K-1)/K;
		}
	}

	return 0;
}












