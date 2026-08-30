#include "vision.h"
#include <bits/stdc++.h>
using namespace std;

void construct_network(int H, int W, int K) {
	vector<int> V;
	// Ns = {0, 1};
	// int a = add_and(Ns);
	// Ns = {0, a};
	// int b = add_or(Ns);
	// Ns = {0, 1, b};
	// int c = add_xor(Ns);
	// add_not(c);

	int curr = H*W-1;
	for (int i = 0; i < H; i++){
	for (int j = 0; j < W; j++){
	for (int i2 = i; i2 < H; i2++){
	for (int j2 = 0; j2 < W; j2++){
		if (i2 == i && j2 <= j) continue;
		int dist = i2-i+abs(j2-j);
		if (dist == K){
			// cout << i << j << i2 << j2 << '\n';
			V = {i*W+j, i2*W+j2};
			add_and(V); ++curr;
		}
	}
	}
	}
	}
	V.clear();
	for (int i = H*W; i <= curr; i++){
		V.push_back(i);
	}
	add_or(V);
	return;
}
