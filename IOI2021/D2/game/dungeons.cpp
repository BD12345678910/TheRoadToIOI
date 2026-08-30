#include "dungeons.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// nodes 0 ... n-1, we start at one of these points
// s[i] = threshold at x, power >= s[i], power += s[i], to w[i] > i
// if power < s[i], power += p[i], to l[i] (unsure);
// node n is endpoint
const ll INF = 1e18;
const int LOG = 24;
const int DIV = 9;
const int MAXN = 50004;
int n;
int nxt[DIV][MAXN][LOG];
ll suma[DIV][MAXN][LOG];
// the exclusive 
ll limv[DIV][MAXN][LOG];
ll border[DIV];
int S[MAXN], P[MAXN], W[MAXN], L[MAXN];

void init(int N, vector<int> s, 
	vector<int> p, vector<int> w, vector<int> l) {
	n = N; 
	for (int i = 0; i < n; i++){
		S[i] = s[i]; P[i] = p[i];
		W[i] = w[i]; L[i] = l[i];
	}

	// these are the lower_bounds
	border[0] = 1;
	for (int i = 1; i < DIV; i++) border[i] = border[i-1]*8;

	// B takes that z >= B but z < nextB
	for (int k = 0; k < DIV; k++){
		ll B = border[k];
		// this is always true
		for (int i = 0; i < n; i++){
			if (S[i] < B){
				nxt[k][i][0] = W[i];
				suma[k][i][0] = S[i];
				limv[k][i][0] = INF;
			} else {
				// this prediction is false when 
				// z >= S[i], this means limv, which is the exclusive max
				// of z, is S[i] for the prediction to be true
				nxt[k][i][0] = L[i];
				suma[k][i][0] = P[i];
				limv[k][i][0] = S[i];
			}
		}
		nxt[k][n][0] = n;
		suma[k][n][0] = 0;
		limv[k][n][0] = INF;
		for (int j = 1; j < LOG; j++){
			for (int i = 0; i <= n; i++){
				int mid = nxt[k][i][j-1];
				nxt[k][i][j] = nxt[k][mid][j-1];
				suma[k][i][j] = suma[k][i][j-1]+suma[k][mid][j-1];
				limv[k][i][j] = min(limv[k][i][j-1], 
					limv[k][mid][j-1]-suma[k][i][j-1]);
			}
		}
	}

	return;
}

// starting node x, power z
ll simulate(int x, int dontnameitz) {
	ll z = dontnameitz;
	// time complexity: DIV*8*Q*LOG = 8.6e7
	while (x != n){
		int k = DIV-1;
		while (k > 0 && border[k] > z) k--;
		for (int j = LOG-1; j >= 0; j--){
			if (z < limv[k][x][j]){
				z += suma[k][x][j];
				x = nxt[k][x][j];
				if (x == n) return z;
			}
		}
		z += S[x];
		x = W[x];
	}
	return z;
}


// The Process:
// Wins are guaranteed
// Losses may be false
// we maintain which are correct
// to reach the first lie &
// that first lie must be a win!
// and we have s[i] >= B
// then z + s[i] >= 2B






