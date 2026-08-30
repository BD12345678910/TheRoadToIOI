#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k, tot;
vector<int> G[200005];
bool dead[200005];
int sz[200005];
vector<int> pushd, tmp;
int fr[200005];
int dep[200005];
ll ans = 0;

void dfs(int x, int pa){
	sz[x] = 1;
	for (int v : G[x]){
		if (v == pa || dead[v]) continue;
		dfs(v, x);
		sz[x] += sz[v];
	}
}

int centroid(int x, int pa){
	for (int v : G[x]){
		if (v == pa || dead[v]) continue;
		if (sz[v] > tot/2) return centroid(v, x); 
	}
	return x;
}

void calc(int x, int pa){
	if (k-dep[x] >= 0) ans += fr[k-dep[x]];
	tmp.push_back(dep[x]);
	for (int v : G[x]){
		if (v == pa || dead[v]) continue;
		dep[v] = dep[x]+1;
		calc(v, x);
	}
}

void solve(int x){
	pushd.clear();
	dfs(x, x); tot = sz[x];
	int c = centroid(x, x);
	// self
	fr[0] = 1; pushd.push_back(0);
	for (int v : G[c]){
		if (dead[v]) continue;
		dep[v] = 1; tmp.clear();
		calc(v, c);
		for (int t : tmp){
			pushd.push_back(t);
			fr[t]++;
		}
	}
	dead[c] = 1;

	for (int v : pushd) fr[v]--;
	for (int v : G[c]){
		if (!dead[v]) solve(v);
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	solve(1);
	cout << ans << endl;
	return 0;
}