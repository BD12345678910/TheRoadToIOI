#include "dungeons.h"
#include <bits/stdc++.h>
using namespace std;

// nodes 0 ... n-1, we start at one of these points
// s[i] = threshold at x, power >= s[i], power += s[i], to w[i] > i
// if power < s[i], power += p[i], to l[i] (unsure);
// node n is endpoint
int n;
vector<int> S, P, W, L;

void init(int N, vector<int> s, 
	vector<int> p, vector<int> w, vector<int> l) {
	n = N;
	S = s;
	P = p;
	W = w;
	L = l;
	return;
}

// starting node x, power z
long long simulate(int x, int z) {
	long long power = z;
	while (x != n){
		if (power >= S[x]){
			power += S[x];
			x = W[x];
		} else {
			power += P[x];
			x = L[x];
		}
	}
	return power;
}

