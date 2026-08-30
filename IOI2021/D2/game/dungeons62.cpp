#include "dungeons.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// nodes 0 ... n-1, we start at one of these points
// s[i] = threshold at x, power >= s[i], power += s[i], to w[i] > i
// if power < s[i], power += p[i], to l[i] (unsure);
// node n is endpoint
const ll INF = 1e18;
int n;
int nxt[6][400005][25];
ll suma[6][400005][25];
set<ll> border;

void init(int N, vector<int> s, 
	vector<int> p, vector<int> w, vector<int> l) {
	// consider the winning tree:
	n = N; 

	border.insert(INF);
	for (int i = 0; i < n; i++) border.insert(s[i]);

	int cnt = -1;
	for (ll t : border){
		cnt++;
		for (int i = 0; i < n; i++){
			nxt[cnt][i][0] = (s[i]>=t)?l[i]:w[i];
			suma[cnt][i][0] = (s[i]>=t)?p[i]:s[i];
		}
		nxt[cnt][n][0] = n;
		suma[cnt][n][0] = 0;
		for (int i = 1; i < 25; i++){
			 for (int j = 0; j <= n; j++){
			 	nxt[cnt][j][i] = nxt[cnt][nxt[cnt][j][i-1]][i-1];
			 	suma[cnt][j][i] = suma[cnt][j][i-1]+
			 	suma[cnt][nxt[cnt][j][i-1]][i-1];
			 }
		}	
		// cout << nxt[cnt][0][23];
	}

	return;
}

// starting node x, power z
ll simulate(int x, int dontnameitz) {
	ll z = dontnameitz;
	int cnt = -1;
	for (ll bd : border){
		cnt++;
		if (z >= bd) continue;
		for (int i = 24; i >= 0; i--){
			if (z + suma[cnt][x][i] < bd){
				z += suma[cnt][x][i];
				x = nxt[cnt][x][i];
			}
			if (x == n) return z;
		}
		z += suma[cnt][x][0];
		x = nxt[cnt][x][0];
		if (x == n) return z;
	}	
	return z;
}



