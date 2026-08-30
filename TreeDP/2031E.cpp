#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> G[1000005];
int dep[1000005];

void dfs(int x){
	if ((int)G[x].size()==0) {
		dep[x] = 0;
		return;
	}
	priority_queue<int,vector<int>,greater<int>> P;
	for (int v : G[x]){
		dfs(v);
		P.push(dep[v]);
	}
	if (P.size()==1) {
		dep[x] = P.top()+1; 
		return;
	}
	while (P.size()>1){
		int c = P.top(); P.pop();
		int y = P.top(); P.pop();
		int z = max(c, y)+1;
		P.push(z);
	}
	dep[x] = P.top(); P.pop();
}

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		G[i].clear(); dep[i] = 0;
	}
	for (int i = 2; i <= n; i++){
		int x; cin >> x;
		G[x].push_back(i);
	}
	dfs(1);
	cout << dep[1] << '\n';
}

int main(){
	int T; cin >> T;
	while (T--) solve();
	return 0;
}