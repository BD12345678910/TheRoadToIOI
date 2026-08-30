#include <bits/stdc++.h>
using namespace std;

int n, Q;
vector<int> G[100005];
vector<int> child[100005];
int col[100005];

bool vis[100005];
int sz[100005];
int cnt[100005];
int ans[100005];
int tmpans;

void dfs1(int x){
	vis[x] = 1;
	sz[x] = 1;
	for (int v : G[x]){
		if (vis[v]) continue;
		dfs1(v);
		sz[x] += sz[v];
		if (sz[v] > sz[G[x][0]]){
			child[x].push_back(child[x][0]);
			child[x][0] = v;
		} else {
			child[x].push_back(v);
		}
	}
}

void dele(int x){
	if (cnt[col[x]]==1) tmpans--;
	cnt[col[x]]--;
	for (int v : child[x]){
		dele(v);
	}
}

void dfs2(int x, bool mode){
	int l = child[x].size();
	if (!cnt[col[x]]) tmpans++;
	cnt[col[x]]++;
	for (int i = 1; i < l; i++){
		int v = child[x][i];
		dfs2(v, 0);
	}
	if (child[x].size()>0)
		dfs2(child[x][0], 1);
	ans[child[x][0]] = tmpans;
	for (int i = 1; i < l; i++){
		int v = child[x][i];
		dfs2(v, 1);
	}
	if (!mode) {
		ans[x] = tmpans;
		dele(x);
	}
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

	dfs1(1);
	dfs2(1, 1);
	ans[1] = tmpans;

	cin >> Q;
	while (Q--){
		int x; cin >> x;
		cout << ans[x] << '\n';
	}

	return 0;
}