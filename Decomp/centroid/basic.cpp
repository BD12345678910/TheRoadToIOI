#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> G[200005];
int sz[200005];
void dfs(int x, int pa){
	sz[x] = 1;
	for (int v : G[x]){
		if (v == pa) continue;
		dfs(v, x);
		sz[x] += sz[v];
	}
}

int centroid(int x, int pa){
	for (int v : G[x]){
		if (v == pa) continue;
		if (sz[v] > n/2) return centroid(v, x); 
	}
	return x;
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1, 1);
	cout << centroid(1,1) << endl;

	return 0;
}