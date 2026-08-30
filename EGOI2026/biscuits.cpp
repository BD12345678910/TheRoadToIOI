// amazing problem:
// obviously dp[i] = 2ndmax(j>=i)(w[j]+dp[j+1])
// take t[i] = w[i]+dp[i+1]; force dp[n+1] = 0;
// A[i] = max(t[i], t[i+1]... t[n])
// B[i] = 2ndmax(t[i], t[i+1]...t[n])
// Notice that i from n...1 A+B is always the suffix sum
// w[i]+...+w[n], as B always gets added w[i], which makes a 
// B' > B, to become either the new A or a larger B
// then, A[i] + B[i] = easily maintained
// By similar reasoning D[i] := A[i] - B[i] = |D[i+1]-W[i]|
// for all 50 starting values, maintain a segment tree
// of transformations, solves in O(50 Q log N)

// P16541
#include <bits/stdc++.h>
using namespace std;

int n, w[100005], Q;
int S;
int t[400005][52];

void upd(int x, int l, int r, int q){
	if (l == r){
		for (int i = 0; i <= 50; i++){
			t[x][i] = abs(i-w[l]);
		}
		return;
	}
	int mid = (l+r)>>1;
	if (q <= mid) upd(x<<1, l, mid, q);
	else 		upd(x<<1|1, mid+1, r, q);
	for (int i = 0; i <= 50; i++){
		t[x][i] = t[x<<1][t[x<<1|1][i]];
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> Q; S = 0;
	for (int i = 1; i <= n; i++){
		cin >> w[i]; S += w[i];
		upd(1, 1, n, i);
	}
	cout << (S-t[1][0])/2 << '\n';
	while (Q--){
		int P, Z; cin >> P >> Z; P++;
		S -= w[P]; 
		w[P] = Z; 
		S += w[P];
		upd(1, 1, n, P);
		cout << (S-t[1][0])/2 << endl;
	}
	return 0;
}



