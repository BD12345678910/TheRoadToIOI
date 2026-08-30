// UNFINIShED

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000006;
int n, q, root, ans;
int ch[N][2], fa[N], pa[N];
ll w[N], su[N], vir[N], sub[N], M;
vector<int> G[N];

bool isroot(int x){
	// return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	return x == root;
}

void pull(int x){
	su[x] = su[ch[x][0]]+su[ch[x][1]]+w[x]+vir[x];
}

// !!
void rotate(int x){
	int y = fa[x], z = fa[y];
	int k = (ch[y][1] == x);
	if (!isroot(y)){
		ch[z][ch[z][1]==y] = x;
	}
	fa[x] = z;
	ch[y][k] = ch[x][k^1];
	fa[ch[x][k^1]] = y;
	ch[x][k^1] = y;
	fa[y] = x;
	pull(y); pull(x);
}

void splay(int x){
	while (!isroot(x)){
		int y = fa[x], z = fa[y];
		if (!isroot(y)){
			if ((ch[y][1]==x)==(ch[z][1]==y)){
				rotate(y);
			} else {
				rotate(x);
			}
		}
		rotate(x);
	}
}

void access(int x){
	int z = x;
	for (int y = 0; x; x = fa[y=x]){
		splay(x);
		vir[x] += (su[ch[x][1]]-su[y]);
		ch[x][1] = y;
		pull(x);
	}
	splay(z);
}

ll query(int x){
	access(x);
	return w[x] + vir[x];
}

int lowest(int v){
	access(v);
	int x = v;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> pa[i] >> w[i];
		M += w[i];
		fa[i] = p[i];
		if (pa[i]){
			G[pa[i]].push_back(i);
		} else {
			root = i;
		}
	}
	dfs(root);
	ans = root;
	for (int i = 1; i <= n; i++){
		if (2 * sub[i] >= M && sub[i] < sub[ans]){
			ans = i;
		}
	}
	cout << ans << '\n';
	while (q--){
		int a, b; cin >> a >> b;
		int x = (ans + a) % n + 1;
		int z = (ans + b) % n + 1;
		int y = pa[x];
		int old = ans;

		cut(x); 
		link(x, z);
		pa[x] = z;
		int u = lowest(y);
		int v = lowest(z);
		ll U = query(u);
		ll V = query(v);
		ll O = query(old);
		ans = (U<V?u:v);
		// if old answer prevails
		if (2*O >= M && O < min(U, V)){
			ans = old;
		}
		cout << ans << '\n';
	}
	return 0;
}


