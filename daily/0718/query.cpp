#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> G[21];

int main(){
	cin >> n;
	for (int i = 2; i <= n; i++){
		int x; cin >> x;
		G[x].push_back(i);
	}
	
	return 0;
}