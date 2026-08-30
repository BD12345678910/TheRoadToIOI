#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 2e9;
const int MAXN = 200005;
const int MAN = 400005;
int H, W, N; ll X;
int RU[MAXN], RD[MAXN], RL[MAXN], RR[MAXN], C[MAXN];
// end result: UDLR <= 2n, or 400000
int U[MAXN], D[MAXN], L[MAXN], R[MAXN];
int xmax, ymax;
int ans[4][MAXN];
vector<int> st[MAN];
vector<int> en[MAN];

ll t[MAN<<2], lz[MAN<<2];
// clear the whole tree
void build(int x, int l, int r){
	if (l == r) {
		t[x] = 0; 
		lz[x] = 0;
		return ;
	}
	int mid = (l+r)>>1;
	build(x<<1, l, mid);
	build(x<<1|1, mid+1, r);
	lz[x] = 0; t[x] = 0;
}

int push_down(int x, int l, int r){
	int mid = (l+r)>>1;
	if (lz[x]){
		lz[x<<1|1] += lz[x];
		lz[x<<1] += lz[x];
		t[x<<1|1] += lz[x];
		t[x<<1] += lz[x];
		lz[x] = 0;
	}
	return mid;
}

void update(int x, int l, int r, int ql, int qr, ll v){
	if (ql <= l && r <= qr){
		t[x] += v;
		lz[x] += v;
		return;
	}
	int mid = push_down(x, l, r);
	if (ql <= mid) update(x<<1, l, mid, ql, qr, v);
	if (qr > mid) update(x<<1|1, mid+1, r, ql, qr, v);
	t[x] = max(t[x<<1], t[x<<1|1]);
}

void solve(int u[], int d[], int l[], int r[], int h, int w, int idx){
	for (int i = 1; i <= h; i++){
		st[i].clear(); en[i].clear();
	}
	for (int i = 1; i <= N; i++){
		st[u[i]].push_back(i);
		en[d[i]].push_back(i);
	}
	set<int> seg;
	build(1, 1, w);
	int tim = N;
	for (int i = 1; i <= h; i++){
		for (int v : st[i]){
			if (v > tim) continue;
			seg.insert(v);
			update(1, 1, w, l[v], r[v], C[v]);
		}
		int og = tim;
		while (t[1] >= X){
			// remove tim if possible
			if (*(--seg.end()) == tim){
				seg.erase(--seg.end());
				update(1, 1, w, l[tim], r[tim], -C[tim]);
			}
			tim--;
		}
		for (int j = tim+1; j <= og; j++){
			ans[idx][j] = i;
		}
		for (int v : en[i]){
			if (v > tim) continue;
			seg.erase(seg.find(v));
			update(1, 1, w, l[v], r[v], -C[v]);
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> H >> W >> N >> X;
	vector<int> XX, YY; 
	XX.push_back(0); YY.push_back(0);
	XX.push_back(INF); YY.push_back(INF);
	for (int i = 1; i <= N; i++){
		cin >> RU[i] >> RD[i] >> RL[i] >> RR[i] >> C[i];
		U[i] = RU[i]; 
		D[i] = RD[i]+1;
		XX.push_back(U[i]);
		XX.push_back(D[i]);
		L[i] = RL[i];
		R[i] = RR[i]+1;
		YY.push_back(L[i]);
		YY.push_back(R[i]);
	}
	sort(XX.begin(), XX.end());
	xmax = unique(XX.begin(), XX.end())-XX.begin();
	sort(YY.begin(), YY.end());
	ymax = unique(YY.begin(), YY.end())-YY.begin();
	for (int i = 1; i <= N; i++){
		U[i] = lower_bound(XX.begin(), XX.begin()+xmax, U[i])-XX.begin();
		D[i] = lower_bound(XX.begin(), XX.begin()+xmax, D[i])-XX.begin()-1;
		L[i] = lower_bound(YY.begin(), YY.begin()+ymax, L[i])-YY.begin();
		R[i] = lower_bound(YY.begin(), YY.begin()+ymax, R[i])-YY.begin()-1;
	}

	solve(U, D, L, R, xmax, ymax, 0);
	
	for (int i = 1; i <= N; i++){
		U[i] = xmax-1-U[i];
		D[i] = xmax-1-D[i];
	}
	solve(D, U, L, R, xmax, ymax, 1);
	for (int i = 1; i <= N; i++){
		U[i] = xmax-1-U[i];
		D[i] = xmax-1-D[i];
	}

	solve(L, R, U, D, ymax, xmax, 2);
	
	for (int i = 1; i <= N; i++){
		L[i] = ymax-1-L[i];
		R[i] = ymax-1-R[i];
	}
	solve(R, L, U, D, ymax, xmax, 3);
	for (int i = 1; i <= N; i++){
		L[i] = ymax-1-L[i];
		R[i] = ymax-1-R[i];
	}

	for (int i = 1; i <= N; i++){
		if (!ans[0][i]){
			cout << 0 << '\n';
			continue;
		}
		ans[1][i] = xmax-1-ans[1][i];
		ans[3][i] = ymax-1-ans[3][i];
		ll ret = 1LL*(XX[ans[1][i]+1]-XX[ans[0][i]]);
		ret *= (YY[ans[3][i]+1]-YY[ans[2][i]]);
		cout << ret << '\n';
	}

	return 0;
}






