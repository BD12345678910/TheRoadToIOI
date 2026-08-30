#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k1, k2, tot;
vector<int> G[200005];
bool dead[200005];
int sz[200005];
vector<int> thi;
int rec, trec;
vector<int> fr;
int dep[200005];
ll ans = 0;

int rang(int x, int y){
	if (x > y) return 0;
	if (y+1 > rec) return fr[x];
	return fr[x]-fr[y+1];
}

void dfs(int x, int pa){
	sz[x] = 1;
	for (int v : G[x]){
		if (v == pa || dead[v]) continue;
		dfs(v, x);
		sz[x] += sz[v];
	}
}

int centroid(int x, int pa){
	for (int v : G[x]){
		if (v == pa || dead[v]) continue;
		if (sz[v] > tot/2) return centroid(v, x); 
	}
	return x;
}

void calc(int x, int pa){
	// dep[x]+y in [k1, k2]
	// y in [k1-dep[x], k2-dep[x]]
	if (k2-dep[x] < 0) return;
	ans += rang(max(k1-dep[x],0), min(k2-dep[x], rec));
	thi.push_back(dep[x]);
	for (int v : G[x]){
		if (v == pa || dead[v]) continue;
		dep[v] = dep[x]+1;
		calc(v, x);
	}
}

void solve(int x){
	dfs(x, x); tot = sz[x];
	int c = centroid(x, x);
	rec = 0; fr.push_back(1);
	for (int v : G[c]){
		if (dead[v]) continue;
		dep[v] = 1; 
		thi.clear(); 
		calc(v, c);
		vector<int> tmp;
		trec = 0; tmp.push_back(0);
		for (int t : thi){
			if (t > trec) {
				tmp.push_back(0);
				trec = t;
			}
			tmp[t]++;
		}
		// combine tmp:
		for (int t = trec-1; t >= 0; t--){
			tmp[t] += tmp[t+1];
		}
		if (trec > rec) {
			swap(fr, tmp); 
			swap(trec, rec);
		}
		for (int i = 0; i <= trec; i++){
			fr[i] += tmp[i];
		}
	}
	dead[c] = 1;

	fr.clear();
	for (int v : G[c]){
		if (!dead[v]) solve(v);
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k1 >> k2;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	solve(1);
	cout << ans << endl;
	return 0;
}

