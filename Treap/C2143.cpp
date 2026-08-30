// yes, this problem has nothing to do with treaps
// reachability for n <= 5e4, m, q <= 1e5

// after shrinking scc's how to efficiently check if a can reach b in DAG??
// use bitset...


#include <bits/stdc++.h>
using namespace std;

int n, m, q;
int e[100005][2];
vector<int> G[50005];
vector<int> R[50005];
bool vis[50005];
int ord[50005], cnt, cc;
int scc[50005];
vector<int> GG[50005];
bitset<50005> reach[50005];

void dfs1(int x){
	vis[x] = 1;
	for (int v : G[x]){
		if (!vis[v]) dfs1(v);
	}
	ord[++cnt] = x;
}

void dfs2(int x){
	vis[x] = 0;
	scc[x] = cc;
	for (int v : R[x]){
		if (vis[v]) dfs2(v);
	}
}

int main(){
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		R[b].push_back(a);
		e[i][0] = a;
		e[i][1] = b;
	}
	for (int i = 1; i <= n; i++){
		if (!vis[i]) dfs1(i);
	}
	for (int i = n; i >= 1; i--){
		if (vis[ord[i]]) {
			cc++;
			dfs2(ord[i]);
		}
	}
	for (int i = 1; i <= m; i++){
		if (scc[e[i][0]] != scc[e[i][1]]){
			GG[scc[e[i][1]]].push_back(scc[e[i][0]]);
		}
	}
	for (int i = cc; i >= 1; i--){
		reach[i][i] = 1;
		for (int x : GG[i]){
			reach[x] |= reach[i];
		}
	}
	for (int i = 1; i <= q; i++){
		int a, b; cin >> a >> b;
		if (scc[a] == scc[b] || reach[scc[a]][scc[b]]){
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}


