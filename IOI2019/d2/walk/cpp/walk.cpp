#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INFF = 1e18;
const ll INF = 1000000001LL;
pair<int,int> tmp[100005];
pair<int,int> tmpbr[100005];
set<int> SS;

int cnt, start, finish;
map<ll,int> Node;
int yy[1000006];
vector<int> col[100005];
vector<pair<int, int>> G[1000006];
int vis[1000006];
ll dist[1000006];
ll code(int x, int y){return INF*x+y;}

ll min_distance(vector<int> X, vector<int> H, vector<int> L, vector<int> R, vector<int> Y, int S, int GG) {
	int m = L.size(), n = X.size();
	for (int i = 0; i < m; i++) tmpbr[i] = {Y[i], i};
	sort(tmpbr, tmpbr+m);
	for (int i = 0; i < n; i++) tmp[i] = {H[i], i};
	sort(tmp, tmp+n);
	int curr = n-1;
	for (int i = m-1; i >= 0; i--){
		while (curr >= 0 && tmp[curr].first >= tmpbr[i].first){
			SS.insert(tmp[curr].second);
			curr--;
		}
		int skyidx = tmpbr[i].second;
		auto no = SS.upper_bound(R[skyidx]);
		int prv = -1, prvx = -1;
		for (auto it = SS.lower_bound(L[skyidx]); it != no; it++){
			int x; ll me = code(*it, tmpbr[i].first);
			// cout << *it << ' ' << tmpbr[i].first << '\n';
			if (!Node.count(me)){
				x = ++cnt;
				yy[x] = tmpbr[i].first;
				col[*it].push_back(x);
				Node[me] = cnt;
			} else {
				x = Node[me];
			}
			if (prv != -1){
				G[prv].push_back({x, X[*it]-prvx});
				G[x].push_back({prv, X[*it]-prvx});
			}
			prv = x;
			prvx = X[*it];
		}
	}
	col[S].push_back(++cnt); yy[cnt] = 0; start = cnt;
	col[GG].push_back(++cnt); yy[cnt] = 0; finish = cnt;

	// cout << cnt << endl;

	for (int i = 0; i < n; i++){
		int l = col[i].size();
		for (int j = 0; j < l-1; j++){
			// col[i][j]  col[i][j+1];
			int x = col[i][j];
			int y = col[i][j+1];
			int d = yy[x]-yy[y];
			G[x].push_back({y,d});
			G[y].push_back({x,d});
		}
	}

	for (int i = 1; i <= cnt; i++) dist[i] = INFF;
	
	priority_queue<pair<long long, int>> P;
	P.push({0, start}); dist[start] = 0;
	while (!P.empty()){
		int x = P.top().second; P.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		if (x == finish){
			break;
		}
		for (auto [v, w]: G[x]){
			if (dist[v] > dist[x]+w){
				dist[v] = dist[x]+w;
				P.push({-dist[v], v});
			}
		}
	}
	if (dist[finish] == INFF) dist[finish] = -1;
	return dist[finish];
}

int main() {
	int n, m;
	assert(2 == scanf("%d%d", &n, &m));
	vector<int> x(n), h(n);
	for (int i = 0; i < n; i++)
		assert(2 == scanf("%d%d", &x[i], &h[i]));
	vector<int> l(m), r(m), y(m);
	for (int i = 0; i < m; i++)
		assert(3 == scanf("%d%d%d", &l[i], &r[i], &y[i]));
	int s, g;
	assert(2 == scanf("%d%d", &s, &g));
	fclose(stdin);

	long long result = min_distance(x, h, l, r, y, s, g);

	printf("%lld\n", result);
	fclose(stdout);
	return 0;
}


/*
7 7
0 8 3 7 5 9 7 7 10 6 12 6 14 9                       
0 1 1   
0 2 6
0 6 8
2 3 1
2 6 7
3 4 2
4 6 5
1 5
*/



