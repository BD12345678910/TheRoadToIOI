#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> G[300005];
int mask[300005];
queue<int> Q;
bool inq[300005];

void enq(int x){
	if (!inq[x]){
		inq[x] = 1;
		Q.push(x);
	}
}

vector<int> T[300005];
int dfn[300005], low[300005], cnt;
bool insta[300005];
int sta[300005], tp, cc;
int comp[300005];
vector<int> ofCC[300005];
int deg[300005];

void dfs(int x){
	dfn[x] = low[x] = ++cnt;
	insta[x] = 1;
	sta[++tp] = x;
	for (int v : T[x]){
		if (!dfn[v]){
			dfs(v);
			low[x] = min(low[x], low[v]);
		} else if (insta[v]){
			low[x] = min(low[x], dfn[v]);
		}
	}
	if (low[x]==dfn[x]){
		cc++;
		while (tp > 0){
			int y = sta[tp--];
			insta[y] = 0;
			comp[y] = cc;
			ofCC[cc].push_back(y);
			if (y == x) break;
		}
	}
}

vector<int> find_reachable(vector<int> R, vector<int> U, vector<int> V, vector<int> C) {
	int n = R.size(); 
	int m = U.size();
	vector<int> ans(n, 0);
	for (int i = 0; i < m; i++){
		int a = U[i], b = V[i], c = C[i];
		G[a].push_back({b,c});
		G[b].push_back({a,c});
	}
	
	for (int i = 0; i < n; i++){
		mask[i] = 1<<(R[i]);
		enq(i);
	}
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		// update x by checking its edges
		for (auto [v, c] : G[x]){
			int nm = (mask[x]|mask[v]);
			if (mask[x]>>c&1){
				if (nm!=mask[x]) {
					mask[x] = mask[x]|mask[v];
					enq(x);
				}	
			}
			if (mask[v]>>c&1){
				if (nm!=mask[v]) {
					mask[v] = mask[x]|mask[v];
					enq(v);
				}
			}
		}
	}

	for (int i = 0; i < n; i++){
		for (auto [v, w]: G[i]){
			if (mask[i]>>w & 1){
				T[i].push_back(v);
				// cout << i << "->" << v << endl;
			}
		}
	}	

	// find SCC on T
	for (int i = 0; i < n; i++){
		if (!dfn[i]) dfs(i);
	}

	for (int i = 0; i < n; i++){
		for (int v : T[i]){
			if (comp[i] != comp[v]){
				deg[comp[i]]++;
			}
		}
	}

	int mn = 400000;
	for (int i = 1; i <= cc; i++){
		if (deg[i] == 0){
			mn = min(mn, (int)ofCC[i].size());
		}
	}
	for (int i = 1; i <= cc; i++){
		if (deg[i] == 0 && (int)ofCC[i].size()==mn){
			for (int x : ofCC[i]){
				ans[x] = 1;
			}
		}
	}
	return ans;
}
