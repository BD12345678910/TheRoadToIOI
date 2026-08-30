#include <bits/stdc++.h>
using namespace std;
int Q;
char OP[100005]; 
int ND[100005];
vector<int> G[100005];
int activate[100005], cnt;

bool alive[100005];
int sz[100005];
int cent[100005];
int fa[100005][18];
int dep[100005];
int far1[100005], far2[100005];
void dfs1(int x, int pa){
	sz[x] = 1;
	for (int v : G[x]){
		if (v == pa || !alive[v]) continue;
		dfs1(v, x);
		sz[x] += sz[v];
	}
}
int find_centroid(int x, int pa, int tot){
	for (int v : G[x]){
		if (v == pa || !alive[v]) continue;
		if (sz[v]*2 >= tot){
			return find_centroid(v, x, tot);
		}
	}
	return x;
}
void assign(int x, int pa, int c){
	cent[x] = c;
	for (int v : G[x]){
		if (v == pa || !alive[v]) continue;
		assign(v, x, c); 
	}
}

void decomp(int x){
	dfs1(x, x);
	int c = find_centroid(x, x, sz[x]);
	for (int v : G[c]){
		if (!alive[v]) continue;
		assign(v, c, c);
	}
	alive[c] = 0;
	for (int v : G[c]){
		if (alive[v]) decomp(v);
	}
}

void preplca(int x, int pa){
	fa[x][0] = pa;
	for (int i = 1; i <= 17; i++){
		fa[x][i] = fa[fa[x][i-1]][i-1];
	}
	for (int v : G[x]){
		if (v == pa) continue;
		dep[v] = dep[x]+1;
		preplca(v, x);
	}
}

int lca(int x, int y){
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 17; i >= 0; i--){
		if (dep[x] - (1<<i) >= dep[y]){
			x = fa[x][i];
		}
	}
	if (x == y) return x;
	for (int i = 17; i >= 0; i--){
		if (fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int dist(int x, int y){
	if (x == -1 || y == -1) return -1;
	int m = lca(x, y);
	return dep[x]+dep[y]-2*dep[m];
}

void Activate(int x){
	int og = 0;
	while (x != 0){
		// update at its key points
		if (dist(x, og) > dist(x, far1[x])){
			far1[x] = og;
		} else if (dist(x, og) > dist(x, far2[x])){
			far2[x] = og;
		}
		x = cent(x);
	}
}

int query(int x){
	
}

int main(){
	cin >> Q;
	for (int i = 1; i <= Q; i++){
		cin >> OP[i] >> ND[i];
		if (OP[i]=='B') {
			activate[i] = ++cnt;
			if (ND[i] != -1){ 
				G[cnt].push_back(ND[i]);
				G[ND[i]].push_back(cnt);
			}
		}
	}
	for (int i = 1; i <= cnt; i++) {
		alive[i] = 1;
		far1[i] = far2[i] = -1;
	}
	for (int i = 1; i <= cnt; i++){
		if (alive[i]) {
			preplca(i, i);
			decomp(i, i);
		}
	}
	for (int i = 1; i <= Q; i++){
		// activate:
		if (OP[i]=='B'){
			Activate(activate[i]);
		} else {
			cout << query(ND[i]) << '\n';
		}
	}


	return 0;
}


