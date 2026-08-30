#include <bits/stdc++.h>
using namespace std;

int n;
struct past{
	int l, r, k;
	int res;
} t[35]; int cnt = 0;

int qry(int l, int r, int k){
	cout << "? " << l << ' ' << r << ' ' << k << endl;
	int ret; cin >> ret; 
	t[++cnt].l = l; t[cnt].r = r; t[cnt].k = k;
	t[cnt].res = ret; return ret;
}

void answer(int l){
	cout << "! " << l << endl;
}

int main(){
	cin >> n;
	if (n % 2 == 1){
		// binary search to find smallest 
		// l such that [1, l] contains 1
		int l = 1, r = n;	
		while (l < r){
			int mid = (l+r)>>1;
			int x = qry(1, mid, 2);
			int y = qry(mid+1, n, 2);
			x = 2*x-mid;
			y = 2*y-(n-mid);
			if (x > y) r = mid;
			else l = mid+1;
		}
		cout << "! " << l << endl;
	} else {
		int l = 1, r = n;
		int diff = 0;	
		while (l < r+1){
			int mid = (l+r)>>1;
			int x = qry(1, mid, 2);
			int y = qry(mid+1, n, 2);
			x = 2*x-mid;
			y = 2*y-(n-mid);
			if (!diff && x == y){
				if (mid > 1){
					int z = qry(1, mid, n);
					if (z == 2) {
						l = mid+1;
						diff = -1;
					} else {
						r = mid;
						diff = 1;
					}
				} else {
					int z = qry(mid+1, n, n);
					if (z == 2) {
						r = mid;
						diff = 1;
					} else {
						l = mid+1;
						diff = -1;
					}
				}
			}
			else if (x > y-diff) r = mid;
			else l = mid+1;
		}
		if (r == l+1){
			// do the final layer:
			if (diff == 0){
				// this means one is n one is 1
				if (l > 1){
					int z = qry(1, l, n);
					if (z == 2) {answer(l+1); return 0;}
					else {answer(l); return 0;}
				} else {
					int z = qry(l+1, n, n);
					if (z == 2) {answer(l); return 0;}
					else {answer(l+1); return 0;}
				}
			} else {
				int x = search(1, l-1, 2);
				if (x == -1) {
					x = search(r+1, n, 2);
					int y = qry(r, n, 2);
				} else {

				}
			}
		} else if (l == r) {
			answer(l);
		}
	}

	return 0;
}