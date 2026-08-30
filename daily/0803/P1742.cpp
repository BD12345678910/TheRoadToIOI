// UNFINISHED

#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int n;
pair<ld,ld> A[200005];
ld x[200005], y[200005];

ld dist(ld xa, ld ya, ld xb, ld yb){
	return (xa-xb)*(xa-xb) + (ya-yb)*(ya-yb);
}

struct circ{
	ld xc, yc, r; bool inval;
	bool contain(ld xx, ld yy){
		if (inval) return 0;
		return dist(xx, yy, xc, yc) <= r*r;
	}
} C;

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> A[i].first >> A[i].second;
	}
	random_shuffle(A+1, A+n+1);
	for (int i = 1; i <= n; i++){
		x[i] = A[i].first;
		y[i] = B[i].first;
	}

	C.inval = 1;
	for (int i = 1; i <= n; i++){
		if (C.contain(x[i], y[i])) continue;
		// if it does not contain i, reset the circle:
		C.inval = 0;
		C.r = 0; C.xc = x[i]; C.yc = y[i];
		for (int j = 1; j < i; j++){
			if (C.contain(x[j], y[j])) continue;
			C.r = sqrt(dist(C.xc, C.yc, x[j], y[j]))/2;
			C.xc = (C.xc+x[j])/2;
			C.yc = (C.yc+y[j])/2;
			for (int k = 1; k < j; k++){
				if (C.contain(x[k], y[k])) continue;
				// finish building the third circle, and continue
				// ... we'll do this later....
			}
		}
	}

	return 0;
}


