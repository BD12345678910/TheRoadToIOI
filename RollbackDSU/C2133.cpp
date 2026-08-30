// DSU rollback

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, m, k;
int ans[N<<2];

struct DSU{
	int fa[N], sz[N];
	int comp;
	stack<pair<int,int>> S;
	int find(int x){
		if (fa[x] == x) return x;
		return find(fa[x]);
	}
	int snap(){
		return S.size();
	}
	void join(int a, int b){
		a = find(a); b = find(b);
		if (a == b){
			S.push({-1, 0});
			return;
		}
		if (sz[a] < sz[b]) swap(a, b);
		S.push({b, sz[a]});
		sz[a] += sz[b];
		fa[b] = a;
		comp--;
	}
	void rollback(int s){
		while ((int)S.size()>s){
			auto [b, ori] = S.top();
			S.pop();
			if (b == -1) continue;
			int a = fa[b];
			sz[a] = ori;
			fa[b] = b;
			comp++;
		} 
	}
} D;

vector<pair<int,int>> t[4000006];

void update(int x, int l, int r, int ql, int qr, pair<int,int> iden){
	if (ql <= l && r <= qr){
		t[x].push_back(iden);
		return;
	}
	int mid = (l+r)>>1;
	if (ql <= mid) update(x<<1, l, mid, ql, qr, iden);
	if (qr > mid) update(x<<1|1, mid+1, r, ql, qr, iden);
}

void dfs(int x, int l, int r){
	// add my changes:
	int s = D.snap();
	for (auto [a, b]: t[x]){
		D.join(a, b);
	}
	if (l == r){
		ans[l] = D.comp;
	} else {
		int mid = (l+r)>>1;
		dfs(x<<1, l, mid);
		dfs(x<<1|1, mid+1, r);
	}
	D.rollback(s);
}

map<pair<int,int>, int> start;

int main(){
	cin >> n >> m >> k;
	D.comp = n;
	for (int i = 1; i <= n; i++){
		D.fa[i] = i; D.sz[i] = 1;
	}
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		start[{min(a, b), max(a, b)}] = 1;
	}
	for (int i = 2; i <= k+1; i++){
		int op, a, b; cin >> op >> a >> b;
		pair<int,int> iden = {min(a, b), max(a, b)};
		if (op == 1){
			start[iden] = i;
		} else {
			int s = start[iden]; start.erase(iden);
			update(1, 1, k+1, s, i-1, iden);
			// cout << s << ' ' << i << ' ' << a << ' ' << b << endl;
		}
	}
	for (auto [pp, ss] : start){
		update(1, 1, k+1, ss, k+1, pp);
	}
	dfs(1, 1, k+1);
	for (int i = 1; i <= k+1; i++){
		cout << ans[i] << ' ';
	}
	return 0;
}






