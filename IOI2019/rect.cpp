#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[2503][2503];

vector<int> row[2503][2503];

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	queue<int> Q;
	for (int i = 1; i <= n; i++){
		// al >= ar
		// maintain decreasing deque
		Q.clear();
		for (int j = 1; j <= m; j++){
			while (a[i][j] > a[i][Q.front()]){
				Q.pop();
			}
			while (a[i][j] == a[i][Q.front()]){
				row[Q.front()][j].push_back(i);
				Q.pop();
			}
			if (Q.front()+1<j)
			row[Q.front()][j].push_back(i);
			Q.push(j);
		}
		// al < ar
		Q.clear();
		for (int j = m; j >= 1; j--){
			while (a[i][j] >= a[i][Q.front()]){
				Q.pop();
			}
			row[j][Q.front()].push_back(i);
			Q.push(j);
		}
	}



	return 0;
}


