#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> G[300005];
int res[300005];
bool vis[300005];
bool key[300005];
vector<int> added;
vector<int> wadd;
vector<int> waitlist[300005];

vector<int> find_reachable(vector<int> r, vector<int> U, vector<int> V, vector<int> C) {
	int n = r.size(); 
	int m = U.size();
	vector<int> ans;
	for (int i = 0; i < m; i++){
		int a = U[i], b = V[i], co = C[i];
		G[a].push_back({b, co});
		G[b].push_back({a, co});
	}
	int mn = 67676767;
	for (int i = 0; i < n; i++){
		added.clear();
		for (int j = 0; j < n; j++) vis[j] = 0;
		queue<int> Q; Q.push(i);
		while (!Q.empty()){
			int x = Q.front(); Q.pop();
			if (vis[x]) continue;
			vis[x] = 1;
			if (!key[r[x]]){
				key[r[x]] = 1;
				added.push_back(r[x]);
				for (int v : waitlist[r[x]]){
					Q.push(v);
				}
				waitlist[r[x]].clear();
			}
			for (auto[v,col]:G[x]){
				if (!vis[v]){
					if (key[col]){
						Q.push(v);
					} else {
						wadd.push_back(col);
						waitlist[col].push_back(v);
					}
				} 
			}
		}
		for (int j = 0; j < n; j++){
			if (vis[j]) res[i]++;
		}
		for (int v : added){
			key[v] = 0;
		}
		for (int v : wadd){
			waitlist[v].clear();
		}
		mn = min(mn, res[i]);
	}
	for (int i = 0; i < n; i++){
		ans.push_back(res[i]==mn);
	}

	return ans;
}
