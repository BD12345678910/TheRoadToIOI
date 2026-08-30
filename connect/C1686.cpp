#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
int e[200005][2];
int cnt, dfn[100005], low[100005];
int comp[100005], cc;
stack<int> S; bool insta[100005];
vector<int> G[100005];
int w[100005];
ll suma[100005];
vector<int> GG[100005];
int deg[100005];
ll dp[100005];

void dfs(int x){
	dfn[x] = low[x] = ++cnt;
	S.push(x); insta[x] = 1;
	for (int v : G[x]){
		if (!dfn[v]){
			dfs(v);
			low[x] = min(low[x], low[v]);
		} else if (insta[v]){
			low[x] = min(low[x], dfn[v]);
		}
	}
	if (low[x] == dfn[x]){
		cc++; int u;
		do {
			u = S.top();
			insta[u] = 0;
			comp[u] = cc;
			S.pop();
		} while (u != x);
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> w[i];
	}
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		e[i][0] = a; e[i][1] = b;
	}
	for (int i = 1; i <= n; i++){
		if (!dfn[i]) dfs(i);
		suma[comp[i]] += w[i];
	}
	cout << endl;
	for (int i = 1; i <= m; i++){
		int a = e[i][0], b = e[i][1];
		if (comp[a]==comp[b]) continue;
		GG[comp[a]].push_back(comp[b]);
		deg[comp[b]]++;
	}
	queue<int> Q; ll global = 0;
	for (int i = 1; i <= cc; i++){
		if (deg[i]==0){
			Q.push(i);
			dp[i] = suma[i];
		}
	}
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		for (int v : GG[x]){
			dp[v] = max(dp[v], dp[x] + suma[v]);
			deg[v]--;
			if (deg[v]==0){
				Q.push(v);
			}
		}
	}
	for (int i = 1; i <= cc; i++){
		global = max(global, dp[i]);
	}
	cout << global << endl;

	return 0;
}




