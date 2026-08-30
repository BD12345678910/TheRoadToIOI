#include "parrots.h"
#include <bits/stdc++.h>
using namespace std;



void encode(int N, int M[]){
	// consider encoding two elements at a time:
	for (int i = 1; i <= (N+1)/2; i++){
		int G = M[2*(i-1)]*256+M[2*(i-1)+1];

	}
	return;
}
void decode(int N, int L, int X[]){

	if (L == 1){
		for (int i = 0; i < N; i++){
			output(255);
		}
		return;
	}

	sort(X, X+L);
	int prev = 0;
	for (int i = 0; i < N; i++){
		int s = 0;
		for (int j = 0; j < 8; j++){
			if (X[i*8+j]-prev) s |= (1<<j);
			prev = X[i*8+j];
		}
		output(s);
	}
	return;
}

