#include <bits/stdc++.h>
using namespace std;

int n;

int qry(int l, int r, int k){
	cout << "? " << l << ' ' << r << ' ' << k << endl;
	int ret; cin >> ret; return ret;
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
		while (l < r){
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
		cout << "! " << l << endl;
	}


	return 0;
}