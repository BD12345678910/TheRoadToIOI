#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
struct Edge{
	int to, rev; ll cap;
};
int s, t, n, m;
vector<Edge> G[2003];
int cur[2003], dep[2003];

void add_Edge(int u, int v, ll w){
	G[u].push_back({v, (int)G[v].size(), w});
	G[v].push_back({u, (int)G[u].size()-1, 0});
}

bool bfs(){
	for (int i = 1; i <= n; i++) dep[i] = -1;
	queue<int> Q; Q.push(s); dep[s] = 0;
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		for (Edge E: G[x]){
			if (E.cap && dep[E.to] == -1){
				dep[E.to] = dep[x] + 1;
				Q.push(E.to);
			}
		}
	}
	return dep[t] != -1;
}

ll dfs(int x, ll flow){
	if (x == t) return flow;
	for (int &i = cur[x]; i < (int)G[x].size(); i++){
		Edge &E = G[x][i];
		if (!E.cap || dep[E.to] != dep[x]+1) continue;
		ll pushed = dfs(E.to, min(flow, E.cap));
		if (pushed) {
			E.cap -= pushed;
			G[E.to][E.rev].cap += pushed;
			return pushed;
		}
	}
	return 0;
}

int main(){
	cin >> n >> m; s=1;t=n;
	for (int i = 1; i <= m; i++){
		int a, b; ll c; cin >> a >> b >> c;
		add_Edge(a,b,c);
	}
	ll ans = 0;
	while (bfs()){
		for (int i = 1; i <= n; i++) cur[i] = 0;
		ll pushed = dfs(s, INF);
		while (pushed){
			ans += pushed;
			pushed = dfs(s, INF);
		}
	}
	cout << ans << endl;
	return 0;
}



