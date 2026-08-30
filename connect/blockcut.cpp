#include <bits/stdc++.h>
using namespace std;

vector<int> G[100005];
vector<int> T[100005];
int n, m;
int dfn[100005], low[100005], cnt, bcc;
int sta[100005], tp;

void dfs(int x, int fa){
	dfn[x] = low[x] = ++cnt;
	sta[++tp] = x;
	int cnt = 0;
	for (int v : G[x]){
		if (v == fa) continue;
		if (dfn[v]){
			low[x] = min(low[x], dfn[v]);
		} else {
			dfs(v); cnt++;
			low[x] = min(low[x], low[v]);
			if (x != fa && low[v] >= dfn[x]){
				++bcc;
				while (sta[tp] != v){
					T[bcc].push_back(sta[tp]);
					T[sta[tp]].push_back(bcc);
					tp--;
				}
				T[bcc].push_back(v);
				T[v].push_back(bcc);
				T[bcc].push_back(x);
				T[x].push_back(bcc);
				ap[x] = 1;
				tp--;
			}
		}
	}
	if (x == fa && cnt > 1) ap[x] = 1;
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bcc = n;
	dfs(1);
	// nodes > n are blocks.
	cout << bcc << endl;
	return 0;
}