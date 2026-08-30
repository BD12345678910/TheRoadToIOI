#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> G[200005];

int main(){
	cin >> n;
	for (int i = 2; i <= n; i++){
		int p; cin >> p;
		G[p].push_back(i);
	}

	

	int q; cin >> q;
	while (q--){
		int x; cin >> x;
		cout << ans[x] << '\n';
	}

	return 0;
}