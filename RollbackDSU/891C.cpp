#include <bits/stdc++.h>
using namespace std;

int n, m, q;
int e[500005][3];
int ord[500005];
bool ans[500005];

vector<int> who[500005];
vector<vector<int>> edges[500005];

bool cmp(int x, int y){
	return e[x][2] < e[y][2];
}

struct Rollback{
	int fa[500005], sz[500005];
	stack<pair<int,int>> S;
	int find(int x){
		if (fa[x]==x) return x;
		return find(fa[x]);
	}
	int snap(){return S.size();}
	void join(int a, int b){
		a = find(a); b = find(b);
		if (a == b){
			S.push({-1, 0});
			return;
		}
		if (sz[a] < sz[b]) swap(a, b);
		S.push({b, sz[a]});
		fa[b] = a;
		sz[a] += sz[b];
	}
	void rollback(int s){
		while ((int)S.size() > s){
			auto x = S.top(); S.pop();
			if (x.first == -1) continue;
			int b = x.first;
			int a = fa[b];
			sz[a] = x.second;
			fa[b] = b;
		}
	}
} D;

int main(){
	ios::sync_with_stdio(0); 
	cin.tie(0);
	cin >> n >> m;
	int maxv = 0;
	for (int i = 1; i <= m; i++){
		int a, b, c; cin >> a >> b >> c;
		e[i][0] = a; 
		e[i][1] = b;
		e[i][2] = c;
		maxv = max(maxv, c);
		ord[i] = i;
	}

	for (int i = 1; i <= n; i++){
		D.fa[i] = i;
		D.sz[i] = 1;
	}

	sort(ord+1, ord+m+1, cmp);
	cin >> q;
	for (int i = 1; i <= q; i++){
		ans[i] = 1;
		int k; cin >> k;
		map<int, vector<int>> tmp;
		for (int j = 1; j <= k; j++){
			int x; cin >> x;
			if (tmp.count(e[x][2])){
				tmp[e[x][2]].push_back(x);
			} else {
				tmp[e[x][2]] = vector<int>{x};
			}
		}
		for (auto [u, v]: tmp){
			who[u].push_back(i);
			edges[u].push_back(v);
			// cout << u << ": " << i << ": ";
			// for (int x : v){
			// 	cout << x << ' ';
			// }
			// cout << endl;
		}
	}
	int curr = 1;
	for (int i = 1; i <= maxv; i++){
		if (who[i].empty()) continue;
		// permanent add:
		while (curr <= m && e[ord[curr]][2] < i){
			int a = e[ord[curr]][0];
			int b = e[ord[curr]][1];
			// cout << i << ' ' << a << ' ' << b << endl;
			D.join(a, b);
			curr++;
		}
		for (int j = 0; j < (int)who[i].size(); j++){
			int qq = who[i][j];
			if (ans[qq]==0) continue;
			vector<int> edg = edges[i][j];
			int s = D.snap();
			for (int v : edg){	
				int a = e[v][0], b = e[v][1];
				if (D.find(a)==D.find(b)){
					ans[qq] = 0;
					break;
				}
				D.join(a, b);
			}
			D.rollback(s);
		}
	}
	for (int i = 1; i <= q; i++){
		if (ans[i]) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}






