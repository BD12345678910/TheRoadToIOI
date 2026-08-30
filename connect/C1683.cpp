#include <bits/stdc++.h>
using namespace std;

int dfn[100005], low[100005], cnt;
bool insta[100005];
stack<int> S;
int cc;
vector<int> G[100005];
int n, m;
int comp[100005];

void dfs(int x){
	// cout << x << endl;
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
	if (low[x]==dfn[x]){
		cc++;
		while (S.top() != x){
			comp[S.top()] = cc;
			insta[S.top()] = 0;
			S.pop();
		}
		comp[x] = cc;
		insta[x] = 0;
		S.pop();
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
	}
	for (int i = 1; i <= n; i++){
		if (!dfn[i]) dfs(i);
	}
	cout << cc << endl;
	for (int i = 1; i <= n; i++){
		cout << comp[i] << ' ';
	}
	cout << endl;

	return 0;
}