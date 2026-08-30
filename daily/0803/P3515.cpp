#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int a[500005];
// p >= hj - hi + sqrt(i-j)
// dp[i] = max(hj + sqrt(i-j)) for j < i
// We have anti-monge for candidate values in a max transfer D&C
double dp[2][500005];
double sq[500005];

void work(int l, int r, int ql, int qr, int idx){
	if (l > r) return;
	int mid = (l+r)>>1, opt = -1;
	// brute force x:
	for (int x = ql; x <= min(qr,mid); x++){
		double cand = a[x] + sq[mid-x];
		if (cand > dp[idx][mid]){
			opt = x;
			dp[idx][mid] = cand;
		}
	}
	assert(opt != -1);
	work(l, mid-1, ql, opt, idx);
	work(mid+1, r, opt, qr, idx);
}

int main(){
	cin >> n; sq[0] = 0;
	for (int i = 1; i <= n; i++){
		dp[0][i] = dp[1][i] = -1; // force successful transition
		sq[i] = sqrt(i);
		cin >> a[i];
	}
	work(1, n, 1, n, 0);
	reverse(a+1, a+n+1);
	work(1, n, 1, n, 1);
	for (int i = 1; i <= n; i++){
		cout << (int)ceil(max(dp[0][i], dp[1][n+1-i])) - a[n+1-i] << '\n';
	}
	return 0;
}

