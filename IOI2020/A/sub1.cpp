#include <bits/stdc++.h>
using namespace std;


// r[0] is how many of [1...r-1] are taller than [0]
// r[i] is how many of [i+1..i+r-1] are taller than [i]
// all up to mod n

// the problem is quite free
int N;
int p[200005];

void init(int k, vector<int> r) {
	N = (int)r.size();
	for (int i = 0; i < N; i++){
		p[i+1] = p[i] + r[i];
	}
	return;
}

int circSum(int x, int y){
	if (x < y)
	return p[y-1]-p[x-1];
	else 
	return p[y-1]-p[x-1]+p[N];
}

int len(int x, int y){
	if (x < y)
	return y-x;
	else 
	return y-x+N;
}

int compare_plants(int x, int y) {
	x++; y++;
	// if x must be less than y, then we have a strict chain of 1 from 
	// x to y or a strict chain of 0 from y to x
	if (circSum(x, y) == len(x, y)) return -1;
	if (circSum(y, x) == 0) return -1;

	// if x must be greater than y, then we have a strict chain of 0
	// from x to y or a strict chain of 1 from y to x
	if (circSum(x, y) == 0) return 1;
	if (circSum(y, x) == len(y, x)) return 1;

	return 0;
}



