// solve the subtask of h, w <= 1000, q <= 5000

#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int h,w,Q;

struct rect{
	int xn, xx, yn, yx;
	rect operator+(const rect &other) const{
		return {
			min(xn, other.xn),
			max(xx, other.xx),
			min(yn, other.yn),
			max(yx, other.yx)
		};
	}
	int sz(){
		return (xx-xn+1)*(yx-yn+1);
	}
};

struct Seg{
	rect t[4000005];
	void upd(int x, int l, int r, int q, int vr, int vc){
		if (l == r) {
			t[x] = {vr, vr, vc, vc};
			return;
		}
		int mid = (l+r)>>1;
		if (q <= mid) upd(x<<1, l, mid, q, vr, vc);
		else upd(x<<1|1, mid+1, r, q, vr, vc);
		t[x] = t[x<<1] + t[x<<1|1];
	}
	rect qry(int x, int l, int r, int ql, int qr){
		if (ql > r || qr < l) return {INF,0,INF,0};
		if (ql <= l && r <= qr) return t[x];
		int mid = (l+r)>>1;
		return qry(x<<1, l, mid, ql, qr)+qry(x<<1|1, mid+1, r, ql, qr);
	}
} T;

int r[1000005], c[1000005];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> h >> w >> Q;
	int TT = h*w;
	for (int i = 1; i <= TT; i++){
		cin >> r[i] >> c[i]; r[i]++; c[i]++;
		T.upd(1,1,TT,i,r[i],c[i]);
	}
	while (Q--){
		int x, y; cin >> x >> y; x++; y++;
		swap(r[x], r[y]); 
		swap(c[x], c[y]);
		T.upd(1,1,TT,x,r[x],c[x]);
		T.upd(1,1,TT,y,r[y],c[y]);

		// every two runs, the candidate's box strictly increases.
		// hence O(Q(H+W)log(T))
		int k = 1, cnt = 0;
		while (k <= TT){
			int area = (T.qry(1, 1, TT, 1, k)).sz();
			if (k == area){
				cnt++; k++;
			} else {
				k = area;
			}
		}
		cout << cnt << '\n';
	}	

	return 0;
}




