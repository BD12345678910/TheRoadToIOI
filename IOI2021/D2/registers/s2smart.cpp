#include "registers.h"
#include <bits/stdc++.h>
using namespace std;
static const int M = 100;
static const int B = 2000;

void construct_instructions(int s, int n, int k, int q) {
	// subtasks 1 and 2, but not just for k <= 2:
	// a b
	vector<bool> V(B, 0);
	for (int i = 0; i < k; i++) V[i] = 1;
	append_store(99, V);
	int kmask = 99;

	vector<bool> ONE(B, 0); ONE[0] = 1;
	append_store(98, ONE);
	int one = 98;

	append_and(1, 0, kmask);
	append_move(2, 0);
	append_right(2, 2, k);
	// 1: exactly a, 2: exactly b
	append_not(3, 2);
	// a + ~b = a + (-b-1) = a-b-1 in [-2^k, 2^k-2]
	// if a <= b: -1 or less
	// when negative, the kth bit is 1
	append_add(4, 1, 3);
	// bit 0 tells me if a <= b
	append_right(4, 4, k);
	append_and(4, one, 4);
	for (int i = 1; i < k; i++){
		append_left(5, 4, 1);
		append_or(4, 4, 5);
	}
	append_not(6, 4);
	append_and(7, 1, 4);
	append_and(8, 2, 6);
	append_or(0, 7, 8);

	return;
}



