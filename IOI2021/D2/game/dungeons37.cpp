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
int nxt[400005][19];
int suma[400005][19];
int need[400005][19];

void init(int N, vector<int> s, 
	vector<int> p, vector<int> w, vector<int> l) {
	// consider the winning tree:
	n = N; S = s; P = p; W = w; L = l;
	for (int i = 0; i < n; i++){
		nxt[i][0] = w[i];
		suma[i][0] = s[i];
		need[i][0] = s[i];
	}
	nxt[n][0] = n;
	for (int i = 1; i < 19; i++){
		 for (int j = 0; j <= n; j++){
		 	nxt[j][i] = nxt[nxt[j][i-1]][i-1];
		 	suma[j][i] = suma[j][i-1]+suma[nxt[j][i-1]][i-1];
		 	need[j][i] = max(need[j][i-1], need[nxt[j][i-1]][i-1]-suma[j][i-1]);
		 }
	}

	return;
}

// starting node x, power z
ll simulate(int x, int dontnameitz) {
	ll z = dontnameitz;
	// roughly log W
	for (int t = 0; t <= 25; t++){
		for (int i = 18; i >= 0; i--){
			if (z >= need[x][i]) {
				z += suma[x][i];
				x = nxt[x][i];
			}
			if (x == n) return z;
		}
		z += P[x];
		x = L[x];
		if (x == n) return z;
	}
	return z;
}



