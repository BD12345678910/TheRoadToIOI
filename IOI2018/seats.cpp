#include <bits/stdc++.h>
using namespace std;

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

int H, W, Q, TT;
pair<int,int> where[1000005];
vector<vector<int>> t;

int sign; set<pair<int,int>> pos;

void eval(){
	for (auto [x, y]: pos){
		int tself = t[x][y];
		int tl = t[x][y-1], tu = t[x-1][y];
		int tr = t[x][y+1], td = t[x+1][y];
		vector<int> V = {tl, tr, tu, td}; 
		sort(V.begin(), V.end());
		int second = V[1];
		if (tself < min(tl, tu)){
			upd(1, 1, TT, tself, min(tl, tu)-1, sign);
		}
		if (second < tself){
			upd(1, 1, TT, second, tself-1, sign);
		}
	}
}

void change(int i){
	int x = where[i].first, y = where[i].second;
	pos.insert({x,y});
	if (y < W) pos.insert({x,y+1});
	if (x < H) pos.insert({x+1,y});
	if (y > 1) pos.insert({x,y-1});
	if (x > 1) pos.insert({x-1,y});
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> H >> W >> Q; TT = H*W;
	build(1, 1, TT);
	t.assign(H + 2, vector<int>(W + 2, 0));
	for (int i = 1; i <= TT; i++){
		int x, y; cin >> x >> y; x++, y++;
		t[x][y] = i;
		where[i] = {x, y};
	}
	for (int i = 0; i <= W; i++) t[0][i] = t[H+1][i] = TT+1;
	for (int i = 0; i <= H; i++) t[i][0] = t[i][W+1] = TT+1;
	sign = 1;
	for (int i = 1; i <= TT; i++){
		pos.clear();
		pos.insert({where[i].first, where[i].second});
		eval();
	}
	while (Q--){
		int x, y; cin >> x >> y; x++, y++;
		sign = -1; pos.clear();
		change(x); change(y);
		eval();
		swap(t[where[x].first][where[x].second], t[where[y].first][where[y].second]);
		sign = 1; pos.clear();
		change(x); change(y);
		eval();
		swap(where[x], where[y]);
		cout << cnt[1] << '\n';
	}
	return 0; 
}




