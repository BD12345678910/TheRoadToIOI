#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, root;
vector<int> G[200005];
int deg[200005];
int leaf[200005];
int ans = 0, best;

void dfs1(int x, int pa){
	if (G[x].size()==1) leaf[x] = 1; 
	for (int v : G[x]){
		if (v == pa) continue;
		dfs1(v, x);
		leaf[x] += leaf[v];
	}
	if (x != pa){
		if (leaf[x] % 2) ans++;
	}
}

void dfs2(int x, int pa, int bal){
	if (x != pa){
		if (leaf[x] % 2) bal--;
		else bal++;
	}
	for (int v : G[x]){
		if (v == pa) continue;
		dfs2(v, x, bal);
	}
	if (G[x].size()==1){
		best = min(best, bal);
	}
}

void solve(){
	cin >> n; ans = 0; best = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		G[i].clear(); deg[i] = 0; leaf[i] = 0;
	}
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
		deg[a]++; deg[b]++;
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] > 1) {root = i; break;}
	}
	dfs1(root, root);
	dfs2(root, root, 0);
	// odd leafs
	if (leaf[root]%2) ans += best;
	cout << ans << '\n';
}

int main(){
	int T; cin >> T;
	while (T--) solve();
	return 0;
}