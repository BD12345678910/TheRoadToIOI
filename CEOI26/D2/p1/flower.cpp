#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int n, m;
int e[100005][2];
bool adj[1003][1003];
int ans = 0;

int f(int x){
	int tot = x*(x-1)/2;
	if (x % 2){
		// 5 keeps 6
		return tot-(x-5)/2*3-6;
	} else {
		return tot-(x-4)/2*3-4;
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		adj[a][b] = adj[b][a] = 1;
		e[i][0] = a; e[i][1] = b;
	}
	for (int i = 1; i <= m; i++){
		int a = e[i][0], b = e[i][1];
		if (!adj[a][b]) continue;
		vector<int> V; V.push_back(a); V.push_back(b);
		for (int j = 1; j <= n; j++){
			if (adj[a][j] && adj[b][j]){
				V.push_back(j);
			}
		}
		if ((int)V.size()>=4){
			ans += f((int)V.size());
		}
		for (int x : V){
			for (int y: V){
				adj[x][y] = 0;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
