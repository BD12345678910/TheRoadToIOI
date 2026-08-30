#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; i++)

long long ask(const vector<int> &w);
void answer(int s, int t);

// U, V from 0 to n-2
vector<pair<int,int>> G[130005];
bool vis[130005];
int ord[130005], cc;
int rev[130005], cnt, M, A, B;
long long od;

bool check(int mid) {
    vector<int> w(M, 0);
    for (int i = 0; i <= mid; ++i) w[i] = 1;
    return ask(w) > od;
}

int get_first_edge(){
	int l = 0, r = M-1;
	while (l < r){
		int mid = (l+r)>>1;
		if (check(mid)) r = mid;
		else l = mid+1;
	}
}

void find_pair(int N, vector<int> U, vector<int> V, int a, int b){
	A = a, B = b;
	M = U.size();
	for (int i = 0; i < M; i++){
		G[U[i]].push_back({V[i], i});
		G[V[i]].push_back({U[i], i});
	}
	od = ask(vector<int>(M, 0));
	int e = get_first_edge();
	int v[2] = { U[e], V[e] };
	vector<int> dist[2];
	int ans[2];

	REP(j, 2) {
		queue<int> q; q.push(v[j]);
		// notice this is great practice::
		vector<int> d(N, -1); d[v[j]] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (auto& e : G[x]) {
				if (d[e.first] == -1) {
					d[e.first] = d[x] + 1;
					q.push(i.first);
				}
			}
		}
		dist[j] = d;
	}
	REP(j, 2) {
		
	}
}

