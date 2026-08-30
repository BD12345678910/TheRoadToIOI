#include <bits/stdc++.h>
using namespace std;

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]){
	int green = 0;
	for (int i = 1; i <= H; i++){
		for (int j = 1; j <= W; j++){
			if (R[i][j] >= G[i][j] && G[i][j] >= B[i][j]){
				green++;
			}
		}
	}
	cout << green << ' ' << H*W << endl;
	return green;
}
