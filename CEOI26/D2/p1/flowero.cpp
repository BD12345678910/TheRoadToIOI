#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int n, m;
int e[100005][2];
bool adj[1003][1003];
bool alive[1003];
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
	for (int i = 1; i <= n; i++){
		alive[i] = 1;
	}
	for (int i = 1; i <= m; i++){
		int a, b; cin >> a >> b;
		adj[a][b] = adj[b][a] = 1;
		e[i][0] = a; e[i][1] = b;
	}
	for (int i = 1; i <= m; i++){
		int a = e[i][0], b = e[i][1];
		if (!alive[a] || !alive[b]) continue;
		for (int j = 1; j <= n; j++){
			if (!alive[j]) continue;
			if (adj[a][j] && adj[b][j]){
				// we found a triangle:
				for (int k = 1; k <= n; k++){
					if (!alive[k]) continue;
					if (adj[a][k]&&adj[b][k]&&adj[j][k]){
						// this is a quad!!
						vector<int> V;
						V.push_back(a); V.push_back(b);
						V.push_back(j); V.push_back(k);
						for (int l = 1; l <= n; l++){
							bool flag = 1;
							for (int x : V){
								if (!adj[x][l]) {
									flag = 0;
									break;
								}
							}
							if (flag) V.push_back(l);
						}
						// cout << V.size() << endl;
						ans += f((int)V.size());
						for (int x : V){
							alive[x] = 0;
						}
						break;
					}
				}
			}
			if (!alive[j]) break;
		}
		if (!alive[a] || !alive[b]) continue;
	}

	cout << ans << endl;

	return 0;
}
