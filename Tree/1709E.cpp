// creds: https://codeforces.com/blog/entry/105164

#include <bits/stdc++.h>
using namespace std;

int n, ans;
int a[200005];
int b[200005];
vector<int> G[200005];
set<int> vals[200005];

void setup(int x, int p){
	b[x] = a[x];
	if (p != x) b[x] ^= b[p];
	for (int v : G[x]){
		if (v == p) continue;
		setup(v, x);
	}
}

void dfs(int x, int p){
	bool bad = 0;
	vals[x].insert(b[x]);
	for (int v: G[x]){
		if (v == p) continue;
		dfs(v, x);
		if (vals[v].size() > vals[x].size())
			swap(vals[v], vals[x]);
		for (int t : vals[v]) 
			bad |= vals[x].count(t^a[x]);
		for (int t : vals[v])
			vals[x].insert(t);
		vals[v].clear();
	}
	if (bad){
		ans++;
		vals[x].clear();
	}
}

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i < n; i++){
		int x,y;  cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	setup(1, 1);
	dfs(1, 1);
	cout << ans << '\n';

	return 0;
}