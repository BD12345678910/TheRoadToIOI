#include <bits/stdc++.h>
using namespace std;

int n;
int a[200005];
int b[200005];
bool vis[200005];
bool alr[200005];
pair<int,int> comp[200005];
int cnt;
bool taken[200005], took[200005];
vector<int> G[200005];
int cur[200005];
bool flag;

int dfs(int x, int r){
	vis[x] = 1;
	if (!vis[a[x]]) return dfs(a[x], r)+1;
	else return 1;
}

bool dfs2(int x){
	vis[x] = 1;
	if (b[a[x]] != -1 && b[a[x]] != a[b[x]]) return 0;
	b[a[x]] = a[b[x]];
	taken[a[b[x]]] = 1;
	took[a[x]] = 1;
	if (!vis[a[x]]) return dfs2(a[x]);
	return 1;
}

void connect(int x, int y){
	b[x] = y;
	int xx = a[x], yy = a[y];
	while (xx != x){
		b[xx] = yy;
		xx = a[xx];
		yy = a[yy];
	}
}

void solve(){
	cin >> n; cnt = 0; flag = 0;
	for (int i = 1; i <= n; i++) {
		vis[i] = alr[i] = taken[i] = took[i] = 0;
		G[i].clear(); cur[i] = 0;
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];

	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			comp[++cnt].second = i;
			comp[cnt].first = dfs(i, i);
		}
	}
	for (int i = 1; i <= n; i++) vis[i] = 0;
	for (int i = 1; i <= n; i++){
		if (!vis[i] && b[i] != -1) {
			if (!dfs2(i)){
				cout << "NO\n";
				return;
			}
		}
	}
	
	for (int i = 1; i <= cnt; i++){
		if (!taken[comp[i].second]) {
			G[comp[i].first].push_back(i);
		}
	}

	for (int i = 1; i <= cnt; i++){
		if (!took[comp[i].second]){
			int x = comp[i].first;
			if (cur[x] == (int)G[x].size()){
				cout << "NO\n";
				return;
			}
			connect(comp[i].second, comp[G[x][cur[x]++]].second);
		}
	}

	for (int i = 1; i <= n; i++){
		if (b[i] == -1 || a[b[i]] != b[a[i]] || alr[b[i]]){
			cout << "NO\n";
			return;
		}
		alr[b[i]] = 1;
	}
	cout << "YES\n";
	for (int i = 1; i <= n; i++){
		cout << b[i] << ' ';
	}
	cout << '\n';
}

int main(){
	int T; cin >> T;
	while (T--) solve();

	return 0;
}