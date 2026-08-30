#include "vision.h"
#include <bits/stdc++.h>
using namespace std;

int cnt;
vector<int> V;
int mem[505];
int gor[505];
int gxor[505];

int check(int K, int H, int W){
	for (int diag = 0; diag <= H+W-2; diag++){
		V.clear();
		for (int i = 0; i < H; i++){
			int j = diag-i;
			if (j >= W || j < 0) continue;
			V.push_back(i*W+j);
		}
		add_or(V); cnt++;
		add_xor(V); cnt++;
		mem[diag] = cnt;
	}
	for (int d = 0; d+K-1 <= H+W-2; d++){
		V.clear();
		for (int i = d; i <= d+K-1; i++){
			V.push_back(mem[i]-1);
		}
		add_or(V); cnt++;
		gor[d] = cnt;
	}
	for (int d = 0; d+K-1 <= H+W-2; d++){
		V.clear();
		for (int i = d; i <= d+K-1; i++){
			V.push_back(mem[i]);
		}
		add_xor(V); cnt++;
		add_not(cnt); cnt++;
		gxor[d] = cnt;
	}

	V.clear();
	for (int d = 0; d+K-1 <= H+W-2; d++){
		add_and(vector<int>{gxor[d], gor[d]}); cnt++;
		V.push_back(cnt);
	}
	add_or(V); int X = ++cnt;



	for (int diag = -H+1; diag <= W-1; diag++){
		V.clear();
		for (int i = 0; i < H; i++){
			int j = i+diag;
			if (j >= W || j < 0) continue;
			V.push_back(i*W+j);
		}
		add_or(V); cnt++;
		add_xor(V); cnt++;
		mem[diag+H] = cnt;
	}
	for (int d = -H+1; d+K-1 <= W-1; d++){
		V.clear();
		for (int i = d; i <= d+K-1; i++){
			V.push_back(mem[i+H]-1);
		}
		add_or(V); cnt++;
		gor[d+H] = cnt;
	}
	for (int d = -H+1; d+K-1 <= W-1; d++){
		V.clear();
		for (int i = d; i <= d+K-1; i++){
			V.push_back(mem[i+H]);
		}
		add_xor(V); cnt++;
		add_not(cnt); cnt++;
		gxor[d+H] = cnt;
	}

	V.clear();
	for (int d = -H+1; d+K-1 <= W-1; d++){
		add_and(vector<int>{gxor[d+H], gor[d+H]}); cnt++;
		V.push_back(cnt);
	}
	add_or(V); int Y = ++cnt;
	add_and(vector<int>{X, Y}); return ++cnt;
}

void construct_network(int H, int W, int K) {
	cnt = H*W-1;
	int A = check(K+1, H, W);
	int B = check(K, H, W);
	int C = ++cnt; add_not(B);
	++cnt; add_and(vector<int>{A, C});
}
