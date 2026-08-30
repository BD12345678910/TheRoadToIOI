#include <bits/stdc++.h>
using namespace std;

int n, Q;
vector<int> G[100005];
int col[100005], sz[100005], heavy[100005];
int cnt[100005], ans[100005], cur;

void dfs_sz(int x, int p){
	sz[x] = 1;
	heavy[x] = 0;
	for (int v : G[x]){
		if (v == p) continue;
		dfs_sz(v, x);
		sz[x] += sz[v];
		if (!heavy[x] || sz[v]>sz[heavy[x]]){
			heavy[x] = v;
		}
	}
}

void add(int x, int p, int val){
	if (val == 1){
		if (cnt[col[x]]==0)cur++;
		cnt[col[x]]++;
	} else {
		cnt[col[x]]--;
		if (cnt[col[x]]==0)cur--;
	}
	for (int v : G[x]){
		if (v == p) continue;
		add(v, x, val);
	}
}

void dfs(int x, int p, bool keep){
	for (int v : G[x]){
		if (v == p || v == heavy[x]) continue;
		dfs(v, x, 0);
	}
	if (heavy[x]) dfs(heavy[x], x, 1);
	for (int v : G[x]){
		if (v == p || v == heavy[x]) continue;
		add(v, x, 1);
	}
	if (cnt[col[x]]==0) cur++;
	cnt[col[x]]++;
	ans[x] = cur;
	if (!keep) add(x, p, -1);
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for (int i = 1; i <= n; i++){
		cin >> col[i];
	}

	dfs_sz(1, 1);
	dfs(1, 1, 1);

	cin >> Q;
	while (Q--){
		int x; cin >> x;
		cout << ans[x] << '\n';
	}

	return 0;
}

