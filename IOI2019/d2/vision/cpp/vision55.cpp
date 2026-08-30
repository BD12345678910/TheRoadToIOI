#include "vision.h"
#include <bits/stdc++.h>
using namespace std;

void construct_network(int H, int W, int K) {
	if (min(H, W) == 1 || max(H, W) <= 10){
		vector<int> V;
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
		}}}}
		V.clear();
		for (int i = H*W; i <= curr; i++){
			V.push_back(i);
		}
		add_or(V);
		return;
	} 

	else if (K == 1){
		vector<int> V;
		int cnt = H*W-1;
		// HW ... HW+H-1
		for (int i = 0; i < H; i++){
			V.clear();
			for (int j = 0; j < W; j++){
				V.push_back(i*W+j);
			}
			add_xor(V); ++cnt;
		}
		// HW+H ... HW+H+W-1
		for (int j = 0; j < W; j++){
			V.clear();
			for (int i = 0; i < H; i++){
				V.push_back(i*W+j);
			}
			add_xor(V); ++cnt;
		}
		V.clear();
		for (int i = H*W; i <= H*W+H-1; i++){
			V.push_back(i);
		}
		add_or(V); ++cnt;
		add_not(cnt); int A = ++cnt; // result of rows
		V.clear();
		for (int i = H*W+H; i <= H*W+H+W-1; i++){
			V.push_back(i);
		}
		add_or(V); ++cnt;
		add_not(cnt); int B = ++cnt; // result of columns

		V.clear();
		for (int j = 0; j < W; j++){
			V.push_back(j);
		}
		add_or(V); ++cnt;

		V.clear();
		for (int j = 0; j < W; j++){
			V.push_back((H-1)*W + j);
		}
		add_or(V); ++cnt;

		for (int i = 0; i < H-1; i++){
			V.clear();
			for (int j = 0; j < W; j++){
				V.push_back(i*W+j);
				V.push_back((i+1)*W+j);
			}
			add_or(V); ++cnt;
		}

		V.clear();
		for (int i = B+1; i <= cnt; i++){
			V.push_back(i);
		}
		add_xor(V); int C = ++cnt;



		V.clear();
		for (int i = 0 ; i < H; i++){
			V.push_back(i*W);
		}
		add_or(V); ++cnt;

		V.clear();
		for (int i = 0 ; i < H; i++){
			V.push_back(i*W+W-1);
		}
		add_or(V); ++cnt;

		for (int j = 0; j < W-1; j++){
			V.clear();
			for (int i = 0; i < H; i++){
				V.push_back(i*W+j);
				V.push_back(i*W+j+1);
			}
			add_or(V); ++cnt;
		}
		V.clear();
		for (int i = C+1; i <= cnt; i++){
			V.push_back(i);
		}
		add_xor(V); int D = ++cnt;

		V = {B, C}; add_and(V); int E = ++cnt;
		V = {A, D}; add_and(V); int F = ++cnt;
		V = {E, F}; add_or(V);
		return;
	}

	else {
		vector<int> V;
		for (int i = 0; i <= K; i++){
			int j = K-i;
			if (i >= H || j >= W) continue;
			V.push_back(i*W+j);
			add_or(V);
		}
		return;
	}
	
}
