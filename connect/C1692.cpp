#include <bits/stdc++.h>
using namespace std;

int cur[20000];
vector<int> G[20000];
vector<int> res;

void dfs(int x){
	for (int &i = cur[x]; i < (int)G[x].size(); ){
		dfs(G[x][i++]);
	}
	res.push_back(x);
}

int main(){
	int n; cin >> n;
	int mask = (1<<(n-1))-1;
	for (int i = 0; i < (1<<(n-1)); i++){
		int nxt1 = mask & (i << 1);
		int nxt2 = (mask & (i << 1)) | 1;
		G[i].push_back(nxt1);
		G[i].push_back(nxt2);
	}
	dfs(0);
	reverse(res.begin(), res.end());
	string ans = "";
	for (int i = n-2; i >= 0; i--){
		ans += ('0'+((res[0]>>i)&1));
	}
	for (int i = 1; i < (int) res.size(); i++){
		ans += ('0'+(res[i]&1));
	}
	cout << ans << endl;
	return 0;
}




