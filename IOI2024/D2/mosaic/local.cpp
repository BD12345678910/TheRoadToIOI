#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int n = 10;
int board[65][65];

int main(){
	for (int i = 1; i <= n; i++){
		board[i][1] = rng()%2;
		board[1][i] = rng()%2;
	}
	for (int i = 2; i <= n; i++){
		for (int j = 2; j <= n; j++){
			if (!board[i][j-1] && !board[i-1][j]) board[i][j] = 1;
			else board[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			cout << board[i][j] << ' ';
		}
		cout << '\n';
	}


	return 0;
}