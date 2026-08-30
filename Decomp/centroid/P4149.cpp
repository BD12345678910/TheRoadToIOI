// ioi2011 race
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, k;
vector<pair<int,int>> G[N];
int sz[N]; bool dead[N];
vector<pair<int,int>> tmp;
map<int,int> buck;
int ans;

void dfs_sz(int x, int p){
	sz[x] = 1;
	for (auto [v, _] : G[x]){
		if (v == p || dead[v]) continue;
		dfs_sz(v, x);
		sz[x] += sz[v];
	}
}

int cent(int x, int p, int tot){
	for (auto [v, _] : G[x]){
		if (v == p || dead[v]) continue;
		if (sz[v] > tot/2) return cent(v, x, tot);
	}
	return x;
}

void dfs(int x, int p, int d, int dep){
	if (k < d) return;
	if (buck.count(k-d)){
		ans = min(ans, buck[k-d]+dep);
	}
	tmp.push_back({d, dep});
	for (auto [v, w] : G[x]){
		if (v == p || dead[v]) continue;
		dfs(v, x, d+w, dep+1);
	}
}

void solve(int x){
	dfs_sz(x, x);
	int c = cent(x, x, sz[x]);
	buck.clear();
	buck[0] = 0;
	for (auto [v, w] : G[c]){
		if (dead[v]) continue;
		tmp.clear();
		dfs(v, c, w, 1);
		for (auto [t,tt] : tmp){
			if (!buck.count(t)) buck[t] = tt;
			else buck[t] = min(buck[t], tt);
		}
	}
	dead[c] = 1;
	for (auto [v, _] : G[c]){
		if (!dead[v]) solve(v);
	}
}

int main(){
	cin >> n >> k; ans = N;
	for (int i = 1; i < n; i++){
		int a, b, c; cin >> a >> b >> c;
		G[a].push_back({b,c});
		G[b].push_back({a,c});
	}
	solve(0);
	if (ans == N) ans = -1;
	cout << ans << endl;
	return 0;
}