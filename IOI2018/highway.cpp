#include <bits/stdc++.h>
using namespace std;

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

bool check2(int pref){
	vector<int> w(M, 1);
	for (int i = 0; i <= pref; i++) w[rev[i]] = 0;
	return ask(w) == od;
}

void find_pair(int N, vector<int> U, vector<int> V, int a, int b){
	A = a, B = b;
	M = U.size();
	for (int i = 0; i < M; i++){
		G[U[i]].push_back({V[i], i});
		G[V[i]].push_back({U[i], i});
	}
	od = ask(vector<int>(M, 0));
	int l = 0, r = M-1;
	while (l < r){
		int mid = (l+r)>>1;
		if (check(mid)) r = mid;
		else l = mid+1;
	}

	// l is a contained edge
	int k = U[l]; queue<int> Q; Q.push(k);
	vis[k] = 1;
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		ord[x] = ++cc;
		for (auto [v, e]: G[x]){
			if (!vis[v]){
				vis[v] = 1;
				rev[cnt++] = e;
				Q.push(v);
			}
		}
	}

	l = 0, r = N-2;
	while (l < r){
		int mid = (l+r)>>1;
		if (check2(mid)) r = mid;
		else l = mid+1;
	}
	l = rev[l];
	int s = U[l], tmp = V[l], t;
	if (ord[s] < ord[tmp]) s = tmp;

	memset(vis, 0, sizeof(vis));
	memset(ord, 0, sizeof(ord));
	memset(rev, 0, sizeof(rev));
	Q.push(s); vis[s] = 1;
	cc = cnt = 0;

	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		ord[x] = ++cc;
		for (auto [v, e]: G[x]){
			if (!vis[v]){
				vis[v] = 1;
				rev[cnt++] = e;
				Q.push(v);
			}
		}
	}

	l = 0, r = N-2;
	while (l < r){
		int mid = (l+r)>>1;
		if (check2(mid)) r = mid;
		else l = mid+1;
	}
	l = rev[l]; t = U[l]; tmp = V[l];
	if (ord[tmp] > ord[t]) t = tmp;
	answer(s, t);
}

