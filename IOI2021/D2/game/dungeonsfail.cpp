#include "dungeons.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// nodes 0 ... n-1, we start at one of these points
// s[i] = threshold at x, power >= s[i], power += s[i], to w[i] > i
// if power < s[i], power += p[i], to l[i] (unsure);
// node n is endpoint
int n, allS;
vector<int> S, P, W, L;
ll add[50005];
vector<int> Gwin[50005];
int cycleof[50005];
int ord[50005];
vector<int> cycle[50005];
vector<ll> cyclev[50005];

void init(int N, vector<int> s, 
	vector<int> p, vector<int> w, vector<int> l) {
	// consider the winning tree:
	n = N; S = s; P = p; W = w; L = l;
	allS = s[0];
	for (int i = 0; i < n; i++){
		Gwin[w[i]].push_back(i);
	}
	queue<int> Q; Q.push(n);
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		for (int v : Gwin[x]){
			add[v] = add[x] + s[v];
			Q.push(v);
		}
	}
	int cc = 0;
	for (int i = 0; i < n; i++){
		if (!cycleof[i]) {
			// start a cycle from i:
			cycleof[i] = ++cc;
			cycle[cc].push_back(i);
			cyclev[cc].push_back(0);
			ord[i] = 0;
			int x = l[i], o = 0;
			ll suma = 0;
			while (x != i){
				cycleof[x] = cc;
				cycle[cc].push_back(x);
				cyclev[cc].push_back(p[i]);
				ord[x] = ++o;
				suma += p[x];
				x = l[x];
			}
			cyclev[cc].push_back(suma);
		}
	}

	return;
}

// starting node x, power z
ll simulate(int x, int dontnameitz) {
	ll z = dontnameitz;
	int c = cycleof[x];
	auto &cyc = cycle[c];
	auto &vals = cyclev[c];
	int len = (int)cyc.size();
	ll diff = (allS - z);
	if (diff <= 0) return z+add[x];
	int idx = lower_bound(vals.begin()+ord[x], 
		vals.end(), diff+vals[ord[x]]) - vals.begin();
	if (idx <= len) {
		return z + add[cyc[idx]] + vals[idx] - vals[ord[x]];
	} else {
		z += (vals[len] - vals[ord[x]]);
		diff -= (vals[len] - vals[ord[x]]);
		// we are at the first element of the cycle
		ll tot = vals[len];
		ll times = diff / tot;
		z += times * tot;
		diff -= times * tot;
		idx = lower_bound(vals.begin(), vals.end(), diff)-vals.begin();
		z += (vals[idx]);
		z += add[cyc[idx]];
		return z;
	}
}



