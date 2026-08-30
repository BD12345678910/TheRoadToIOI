#include <bits/stdc++.h>
using namespace std;

int n, m, AA, BB, CC;
vector<pair<int,int>> color;
int A, B, C;
vector<int> G[100005];
vector<int> T[100005];
int dfn[100005], cnt, low[100005];
int fa[100005], sz[100005];
int ans[100005];
bool vis[100005];

void dfs(int x, int pa){
	sz[x] = 1; fa[x] = pa;
	dfn[x] = low[x] = ++cnt;
	for (int v : G[x]){
		if (v == pa) continue;
		if (dfn[v]) {
			low[x] = min(dfn[v], low[x]);
		} else {
			dfs(v, x);
			T[x].push_back(v);
			T[v].push_back(x);
			sz[x] += sz[v];
			low[x] = min(low[v], low[x]);
		}
	}
}

int centroid(int x, int pa){
	for (int v : T[x]){
		if (v == pa) continue;
		if (sz[v] > n/2) 
			return centroid(v, x);
	}
	return x;
}

void mark(int x, int pa){
	vis[x] = 1;
	for (int v: T[x]){
		if (v == pa) continue;
		mark(v, x);
	}
}

int tmp;

void dfs1(int x, int pa){
	tmp--; ans[x] = color[0].second;
	if (!tmp) return;
	for (int v : T[x]){
		if (v == pa) continue;
		dfs1(v, x);
		if (!tmp) return;
	}
}

void dfs2(int x, int pa){
	tmp--; ans[x] = color[1].second;
	if (!tmp) return;
	for (int v : T[x]){
		if (v == pa) continue;
		dfs2(v, x);
		if (!tmp) return;
	}
}

vector<int> handle(int x, int root){
	tmp = A; dfs1(x, root);
	tmp = B; dfs2(root, x);
	for (int i = 0; i < n; i++){
		if (!ans[i]) 
			ans[i] = color[2].second;
	}
	return vector<int>(ans, ans+n);
}

void dfs1e(int x, int pa){
	tmp--; ans[x] = color[0].second;
	if (!tmp) return;
	for (int v : G[x]){
		if (v == pa || !vis[v] || ans[v]) continue;
		dfs1e(v, x);
		if (!tmp) return;
	}
}

void dfs2e(int x, int pa){
	tmp--; ans[x] = color[1].second;
	if (!tmp) return;
	for (int v : T[x]){
		if (v == pa || vis[v]) continue;
		dfs2e(v, x);
		if (!tmp) return;
	}
}

vector<int> handlee(int x, int root){
	tmp = A; dfs1e(x, root);
	tmp = B; dfs2e(root, x);
	for (int i = 0; i < n; i++){
		if (!ans[i]) 
			ans[i] = color[2].second;
	}
	return vector<int>(ans, ans+n);
}

vector<int> solve(){
	cin >> n >> m;
	cin >> AA >> BB >> CC;
	color.push_back({AA, 1});
	color.push_back({BB, 2});
	color.push_back({CC, 3});
	sort(color.begin(), color.end());
	A = color[0].first; B = color[1].first;
	C = color[2].first;

	for (int i = 1; i <= m; i++){
		int x, y; cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(0, 0);
	int root = centroid(0, 0);

	// find the size of what's before: above
	int above = n-1;
	for (int x : T[root]){
		if (dfn[x] < dfn[root]) continue;
		if (sz[x] >= A){
			return handle(x, root);
		}
		above -= sz[x];
	}

	if (above >= A) return handle(fa[root], root);
	if (root != 0) mark(fa[root], root);

	for (int x : T[root]){
		if (x == fa[root]) continue;
		if (low[x] < dfn[root]){
			mark(x, root);
			if (above+sz[x] >= A){
				return handlee(x, root);
			} else {
				above += sz[x];
			}
		}
	}

	return vector<int>(n,0);
}

int main(){
	vector<int> V = solve();
	for (int v : V) cout << v << ' ';
	cout << endl;
	return 0;
}
