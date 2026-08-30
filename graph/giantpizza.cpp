// proof. why can we always choose the earlier scc

// we need to show that true never leads to false
// suppose u is true and v is false and u somehow leads to it

// we know id[u] > id[~u] and id[~v] > id[v], if u leads to it we also have
// id[u] <= id[v], then id[~u] < id[u] <= id[v] < id[~v], 
// however, since u leads to v, ~v must lead to ~u, or 
// id[~u] >= id[~v], contradiction, hence true never leads to false

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> G[200005], R[200005];
int ord[200005],cnt;
bool vis1[200005], vis2[200005];
int cc[200005];

void dfs1(int x){
	vis1[x] = 1;
	for (int v : G[x]){
		if (!vis1[v]) dfs1(v);
	}
	ord[++cnt] = x;
}

void dfs2(int x){
	cc[x] = cnt;
	vis2[x] = 1;
	for (int v : R[x]){
		if (!vis2[v]) dfs2(v);
	}
}

int main(){
	cin >> n >> m;
	for (int i = 0; i < n; i++){
		int a, b; char op1, op2;
		cin >> op1 >> a >> op2 >> b;
		a = ((a-1)<<1)+(op1=='+');
		b = ((b-1)<<1)+(op2=='+');
		int ao = (a>>1<<1<<1)+1-a;
		int bo = (b>>1<<1<<1)+1-b;
		G[ao].push_back(b);
		G[bo].push_back(a);
		R[b].push_back(ao);
		R[a].push_back(bo);
	}
	cnt = 0;
	for (int i = 0; i < 2*m; i++){
		if (!vis1[i]) dfs1(i);
	}
	cnt = 0;
	for (int i = 2*m-1; i >= 0; i--){
		if (!vis2[ord[i]]) {
			cnt++;
			dfs2(ord[i]);
		}
	}
	string ans = "";
	for (int i = 0; i < 2*m; i+=2){
		// consider i and i+1
		if (cc[i] == cc[i+1]){
			cout << "IMPOSSIBLE" << endl;
			return 0;
		} else if (cc[i] < cc[i+1]){
			ans.push_back('+');
			ans.push_back(' ');
		} else {
			ans.push_back('-');
			ans.push_back(' ');
		}
	}
	ans.pop_back();
	cout << ans << endl;

	return 0;
}



