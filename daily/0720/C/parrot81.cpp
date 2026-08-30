#include "parrots.h"
#include <bits/stdc++.h>
using namespace std;

void encode(int N, int M[]){
	int curr = 0;

	bool flag = 1;
	for (int i = 0; i < N; i++){
		if (M[i] != 255) flag = 0;
	}

	if (flag) send(0);
 	else 
	for (int i = 0; i < N; i++){
		for (int j = 0; j < 8; j++){
			if (M[i]>>j&1) curr++;
			send(curr);
		}
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

