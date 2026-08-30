#include <bits/stdc++.h>
using namespace std;


// the problem is quite free
int N, K;
vector<int> R;
int cmp[5005][5005];

void init(int k, vector<int> r) {
	N = (int)r.size();
	K = k;
	R = r;

	queue<int> Q;
	for (int i = 0; i < n; i++){
		if (R[i]==k-1) Q.push(i);
	}
	for (int i = 0; i < n; i++){
		for (int j = i-1; j >= i-(k-1); j--){
			int actual = (j+n)%n;
			
		}
	}
	return;
}

int compare_plants(int x, int y) {
	
}






