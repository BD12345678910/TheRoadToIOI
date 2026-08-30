#include <bits/stdc++.h>
using namespace std;

// consider the function F(X) 
// = number of changing edges
// e.g. BWBWWB = 6

// can we maintain this?
// for each x, consider x-1 & x
// x & x+1, the interval [t(x-1), tx-1] is when contribution is made
int h, w, q, total;
int trash, t[1000006], where[1000006];

int mn[4000006], cnt[4000006], lz[4000006];
void build(int x, int l, int r){
	if (l == r) {cnt[x] = 1; return;}
	int mid = (l+r)>>1;
	build(x<<1, l, mid);
	build(x<<1|1, mid+1, r);
	cnt[x] = cnt[x<<1] + cnt[x<<1|1];
}
int push_down(int x, int l, int r){
	int mid = (l+r)>>1;
	if (!lz[x]) return mid;
	mn[x<<1] += lz[x];
	mn[x<<1|1] += lz[x];
	lz[x<<1] += lz[x];
	lz[x<<1|1] += lz[x];
	lz[x] = 0;
	return mid;
}
void push_up(int x){
	if (mn[x<<1] == mn[x<<1|1]){
		cnt[x] = cnt[x<<1] + cnt[x<<1|1];
		mn[x] = mn[x<<1];
	} else if (mn[x<<1] < mn[x<<1|1]){
		cnt[x] = cnt[x<<1];
		mn[x] = mn[x<<1];
	} else {
		cnt[x] = cnt[x<<1|1];
		mn[x] = mn[x<<1|1];
	}
}
void upd(int x, int l, int r, int ql, int qr, int delta){
	if (ql <= l && r <= qr){
		mn[x] += delta;
		lz[x] += delta;
		return;
	}
	int mid = push_down(x, l, r);
	if (ql <= mid) upd(x<<1, l, mid, ql, qr, delta);
	if (qr > mid) upd(x<<1|1, mid+1, r, ql, qr, delta);
	push_up(x);
}

int main(){
	cin >> h >> w >> q;
	// h = 1;
	for (int i = 1; i <= w; i++){
		cin >> trash >> where[i];
		where[i]++; t[where[i]] = i;
	}
	t[0] = t[w+1] = w+1;
	build(1, 1, w);
	for (int i = 1; i <= w+1; i++){
		upd(1, 1, w, min(t[i], t[i-1]), max(t[i], t[i-1])-1, 1);
	}

	while (q--){
		int x, y; cin >> x >> y; x++; y++;
		// their positions:
		swap(where[x], where[y]);
		x = where[x]; y = where[y];
		upd(1, 1, w, min(t[x], t[x-1]), max(t[x], t[x-1])-1, -1);
		upd(1, 1, w, min(t[x], t[x+1]), max(t[x], t[x+1])-1, -1);
		upd(1, 1, w, min(t[y], t[y-1]), max(t[y], t[y-1])-1, -1);
		upd(1, 1, w, min(t[y], t[y+1]), max(t[y], t[y+1])-1, -1);
		swap(t[x], t[y]);
		upd(1, 1, w, min(t[x], t[x-1]), max(t[x], t[x-1])-1, 1);
		upd(1, 1, w, min(t[x], t[x+1]), max(t[x], t[x+1])-1, 1);
		upd(1, 1, w, min(t[y], t[y-1]), max(t[y], t[y-1])-1, 1);
		upd(1, 1, w, min(t[y], t[y+1]), max(t[y], t[y+1])-1, 1);
		cout << cnt[1] << '\n';
	}

	return 0;
}







