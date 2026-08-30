#include <bits/stdc++.h>
using namespace std;

int n, q;

// 0-5e5
int root[500002];
pair<int,int> node[19800000];
// an OR over interval
int cnt;

int newNode(int l, int r){
	node[++cnt] = {l, r};
	return cnt;
}

// always A subset of B
int update(int A, int B, int l, int r, int ql, int qr){
	if (!B || A == B) return A;
	if (ql <= l && r <= qr) return B;
	int mid = (l+r)>>1;
	int nl = node[A].first;
	int nr = node[A].second;
	if (ql <= mid){
		nl = update(node[A].first, node[B].first, l, mid, ql, qr);
	} 
	if (qr > mid){
		nr = update(node[A].second, node[B].second, mid+1, r, ql, qr);
	}
	if (nl == node[A].first && nr == node[A].second) return A;
	if (nl == node[B].first && nr == node[B].second) return B;
	return newNode(nl, nr);
}

bool someone(int A, int l, int r, int ql, int qr){
	if (!A) return 0;
	if (ql <= l && r <= qr) return 1;
	int mid = (l+r)>>1;
	if (ql <= mid && someone(node[A].first, l, mid, ql, qr)) return 1;
	if (qr > mid && someone(node[A].second, mid+1, r, ql, qr)) return 1;
	return 0;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	node[0] = {0, 0};
	node[1] = {1, 1}; 
	cnt = 1;
	cin >> n >> q;

	root[0] = 1;
	for (int i = 1; i <= q; i++){
		int op, l, r, x;
		cin >> op >> l >> r;
		if (op == 1){
			cin >> x;
			root[x+1] = update(root[x+1], root[x], 1, n, l, r);
		} else {
			int ans = 0, lo = 1, hi = i;
			while (lo <= hi){
				int mid = (lo+hi)>>1;
				if (someone(root[mid], 1, n, l, r)){
					lo = mid+1, ans = mid;
				} else {
					hi = mid-1;
				}
			}
			cout << ans << '\n';
		}
	}
}



