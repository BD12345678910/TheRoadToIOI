#include <bits/stdc++.h>
using namespace std;

const int N = 2003;
int inside[N][N];
int outside[N][N];
int n, k, dep[N];
int dfn[N], rev[N], out[N], cnt;
vector<int> G[N];
vector<pair<int,int>> prv;
long long ans, tmpans;

void search(int x, int pa, int d, int* arr){
	arr[d]++;
	for (int v : G[x]){
		if (v == pa) continue;
		search(v, x, d+1, arr);
	}
}

void dfs(int x, int pa){
	search(x, pa, 0, inside[x]);
	if (x!=pa) search(pa, x, 1, outside[x]);
	dfn[x] = ++cnt;
	rev[cnt] = x;
	for (int v : G[x]){
		if (v == pa) continue;
		dep[v] = dep[x]+1;
		dfs(v, x);
	}
	out[x] = cnt;
}

void dfscalc(int x, int pa){
	prv.clear();
	for (int v : G[x]){
		if (v == pa) continue;
		for (int i = dfn[v]; i <= out[v]; i++){
			int u = rev[i];
			for (auto [p, pp] : prv){
				int need = k-(dep[u]-dep[x])-(dep[p]-dep[x]);
				if (need <= 0) continue;
				ans += outside[x][need];
				tmpans += inside[x][need]-inside[pp][need-1]-inside[v][need-1];
			}
		}
		for (int i = dfn[v]; i <= out[v]; i++){
			prv.push_back({rev[i], v});
		}
	}

	for (int v: G[x]){
		if (v == pa) continue;
		dfscalc(v, x);
	}
}

void solve(){
	cin >> n >> k; k--; ans = cnt = tmpans = 0;
	for (int i = 1; i <= n; i++){
		G[i].clear();
		for (int j = 0; j <= n; j++){
			inside[i][j] = outside[i][j] = 0;
		}
	}
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1, 1);

	// linear case
	for (int i = 1; i <= n; i++){
		ans += inside[i][k] + outside[i][k];
	}
	ans /= 2;
	ans *= (k-1);

	// Y case
	dfscalc(1, 1);
	ans += tmpans / 3;
	cout << ans << '\n';

	return;
}

int main(){
	int T; cin >> T;
	while (T--) solve();

	return 0;
}