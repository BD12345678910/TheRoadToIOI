#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int X = 300000;
int Q;
ll ans, gans[300005];
map<pii, int> start;

struct DSU{
	int fa[600005], szx[600005], szy[600005];
	stack<int> S;
	int find(int x){
		if (fa[x]==x) return x;
		return find(fa[x]);
	}
	int snap(){ return S.size(); }
	void join(int a, int b){
		a = find(a); b = find(b);
		if (a==b) {
			S.push(-1);
			return;
		}
		if (szx[a]+szy[a] < szx[b]+szy[b]) swap(a, b);
		ans -= 1LL*szx[a]*szy[a];
		ans -= 1LL*szx[b]*szy[b];
		S.push(b);
		szx[a] += szx[b];
		szy[a] += szy[b];
		fa[b] = a;
		ans += 1LL*szx[a]*szy[a];
		return;
	}
	void rollback(int s){
		while ((int)S.size() > s){
			int x = S.top(); S.pop();
			if (x == -1) continue;
			int y = fa[x];
			ans -= 1LL*szx[y]*szy[y];
			szx[y] -= szx[x];
			szy[y] -= szy[x];
			fa[x] = x;
			ans += 1LL*szx[y]*szy[y];
			ans += 1LL*szx[x]*szy[x];
		}
	}
} D;

vector<pair<int,int>> G[1200005];
void update(int x, int l, int r, int ql, int qr, pii P){
	if (ql <= l && r <= qr) {
		G[x].push_back(P);
		return;
	}
	int mid = (l+r)>>1;
	if (ql <= mid) update(x<<1, l, mid, ql, qr, P);
	if (qr > mid) update(x<<1|1, mid+1, r, ql, qr, P);
}

void dfs(int x, int l, int r){
	int mid = (l+r)>>1;
	int s = D.snap();
	for (auto [a, b]: G[x]){
		D.join(a, b+X);
	}
	if (l == r){
		gans[l] = ans;
	} else {
		dfs(x<<1, l, mid);
		dfs(x<<1|1, mid+1, r);
	}
	D.rollback(s);
}

int main(){
	cin >> Q;
	for (int i = 1; i <= Q; i++){
		int a, b; cin >> a >> b;
		if (start.count({a, b})){
			int s = start[{a,b}];
			update(1, 1, Q, s, i-1, {a, b});
			start.erase({a, b});
		} else {
			start[{a,b}] = i;
		}
	}
	for (auto [u, v]: start){
		update(1, 1, Q, v, Q, u);
	}

	for (int i = 1; i <= 2*X; i++){
		D.fa[i] = i;
		if (i <= X) D.szx[i] = 1;
		else D.szy[i] = 1;
	}

	dfs(1, 1, Q);
	for (int i = 1; i <= Q; i++){
		cout << gans[i] << ' ';
	}
	cout << endl;

	return 0;
}



