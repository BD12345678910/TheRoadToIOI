#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, m, r;
vector<int> G[502];
int d[502];
int lm[502], rm[502];
bool vis[502];

bool bfs(){
	queue<int> Q; 
	for (int i = 1; i <= n; i++){
		if (!lm[i]){
			d[i] = 0;
			Q.push(i);
		} else {
			d[i] = INF;
		}
	}
	d[0] = INF;
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		if (d[x] >= d[0]) continue;
		for (int v : G[x]){
			if (d[rm[v]] == INF){
				d[rm[v]] = d[x]+1;
				Q.push(rm[v]);
			}
		}
	}
	return d[0] != INF;
}

bool dfs(int x){
	for (int v : G[x]){
		if (!rm[v] || (d[rm[v]] == d[x]+1 && dfs(rm[v]))){
			lm[x] = v;
			rm[v] = x;
			return 1;
		}
	}
	d[x] = INF;
	return 0;
}

int main(){
	cin >> n >> m >> r;
	for (int i = 1; i <= r; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
	}
	int ans = 0;
	while (bfs()){
		for (int i = 1; i <= n; i++){
			if (!lm[i] && dfs(i)){
				ans++;
			}
		}
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++){
		if (lm[i]){
			cout << i << ' ' << lm[i] << endl;
		}
	}

	return 0;
}