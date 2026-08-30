#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int INF = 1e9;

int n,m,e;
vector<int> G[N];
int ml[N], mr[N], dis[N];

bool bfs(){
	queue<int> q;
	for (int x = 1; x <= n; x++){
		if (!ml[x]){
			dis[x] = 0;
			q.push(x);
		} else {
			dis[x] = INF;
		}
	}	
	dis[0] = INF;
	while (!q.empty()){
		int x = q.front();
		q.pop();
		if (dis[x] >= dis[0]) continue;
		for (int y : G[x]){
			int z = mr[y];
			if (dis[z] == INF){
				dis[z] = dis[x]+1;
				q.push(z);
			}
		}
	}
	return dis[0]!=INF;
}

bool dfs(int x){
	if (!x) return 1;
	for (int y : G[x]){
		int z = mr[y];
		if (dis[z] == dis[x]+1 && dfs(z)){
			ml[x] = y;
			mr[y] = x;
			return 1;
		}
	}
	dis[x] = INF;
	return 0;
}

int main(){
	cin >> n >> m >> e;
	for (int i = 1; i <= e; i++){
		int x, y; cin >> x >> y;
		G[x].push_back(y);
	}
	int ans = 0;
	while (bfs()){
		for (int x = 1; x <= n; x++){
			if (!ml[x] && dfs(x)) ans++;
		}
	}
	cout << ans << endl;
}





