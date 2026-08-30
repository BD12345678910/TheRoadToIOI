// "Light can pass if water can pass"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e8;
int s, t, N;

struct Edge{
	int cap, to, rev;
};
vector<Edge> G[610];

int d[610], cur[610];

void addEdge(int u, int v, int w){
	Edge U = {w, v, (int)G[v].size()};
	Edge V = {0, u, (int)G[u].size()};
	G[u].push_back(U);
	G[v].push_back(V);
}

bool bfs(){
	for (int i = 1; i <= N; i++){
		d[i] = -1;
	}
	queue<int> Q; Q.push(s); d[s] = 0;
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		for (Edge E: G[x]){
			if (E.cap && d[E.to] == -1){
				d[E.to] = d[x]+1;
				Q.push(E.to);
			}
		}
	}
	return d[t] != -1;
}

int dfs(int x, int flow){
	if (x == t) return flow;
	for (int &i = cur[x]; i < (int)G[x].size(); i++){
		Edge &E = G[x][i];
		if (!E.cap || d[E.to] != d[x]+1) continue;
		int pushed = dfs(E.to, min(E.cap, flow));
		if (pushed){
			E.cap -= pushed;
			G[E.to][E.rev].cap += pushed;
			return pushed;
		}
	}
	return 0;
}

ll n, X, Y;
int typ[304];
// xhi is radius for circles
ll xlo[304], ylo[304], xhi[304], yhi[304];

ll dist(ll xa, ll ya, ll xb, ll yb){
	return (xa-xb)*(xa-xb)+(ya-yb)*(ya-yb);
}

ll clamp(ll l, ll r, ll x){
	if (x > r) return r;
	if (x < l) return l;
	return x;
}

int in(int x){
	return x;
}
int out(int x){
	if (x == s || x == t) return x;
	return n+x;
}
void add(int x, int y, int w){
	addEdge(out(x), in(y), w);
	addEdge(out(y), in(x), w);
}

int main(){
	cin >> X >> Y;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> typ[i] >> xlo[i] >> ylo[i] >> xhi[i];
		if (typ[i] == 2) cin >> yhi[i];
	}
	for (int i = 1; i <= n; i++){
		for (int j = i+1; j <= n; j++){
			// consider if i and j are connected
			// two circles
			if (typ[i] == 1 && typ[j] == 1){
				if (dist(xlo[i], ylo[i], xlo[j], ylo[j]) <= (xhi[i]+xhi[j])*(xhi[i]+xhi[j])){
					add(i, j, INF);
				}
			} else if (typ[i] != typ[j]){
				bool sw = 0;
				if (typ[i] == 2) {
					swap(i, j);
					sw = 1;
				}
				// i is a circle:
				int jx = clamp(xlo[j], xhi[j], xlo[i]);
				int jy = clamp(ylo[j], yhi[j], ylo[i]);
				if (dist(jx, jy, xlo[i], ylo[i]) <= (xhi[i]*xhi[i])){
					add(i, j, INF);
				}
				if (sw){
					swap(i, j);
				}
			} else {
				int xl = max(xlo[i], xlo[j]);
				int xr = min(xhi[i], xhi[j]);
				int yl = max(ylo[i], ylo[j]);
				int yr = min(yhi[i], yhi[j]);
				if (xl <= xr && yl <= yr){
					add(i, j, INF);
				}
			}
		}
	}
	s = 2*n+1; t = 2*n+2; N = 2*n+2;
	for (int i = 1; i <= n; i++){
		if (typ[i] == 1){
			if (ylo[i]-xhi[i] <= 0 && ylo[i]+xhi[i] >= 0){
				add(i, s, INF);
			}
			if (ylo[i]-xhi[i] <= Y && ylo[i]+xhi[i] >= Y){
				add(i, t, INF);
			}
		} else {
			if (ylo[i] <= 0 && yhi[i] >= 0){
				add(i, s, INF);
			}
			if (ylo[i] <= Y && yhi[i] >= Y){
				add(i, t, INF);
			}
		}
	}
	for (int i = 1; i <= n; i++){
		addEdge(in(i), out(i), 1);
	}

	int ans = 0;
	while (bfs()){
		for (int i = 1; i <= N; i++){
			cur[i] = 0;
		}
		int pushed = dfs(s, INF);
		while (pushed){
			ans += pushed;
			pushed = dfs(s, INF);
		}
	}
	cout << ans << '\n';

	return 0;
}


