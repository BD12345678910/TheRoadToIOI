#include <bits/stdc++.h>
using namespace std;

// P is a matrix after scrambling rows s.t. each column 
// perfectly contains 1..n
// row[i][j] = representation of P
// where row[i][j] = the column index of the original that 
// should be in position (i, j)

int n;
int row[205][205], a[205][205];
bool alive[205][205], vis[205];

vector<pair<int,int>> G[205];
pair<int,int> belong[205];

bool dfs(int x){
	if (vis[x]) return 0;
	vis[x] = 1;
	for (auto [v, col]: G[x]){
		if (belong[v].first == 0 || dfs(belong[v].first)){
			belong[v] = {x, col};
			return 1;
		}
	}
	return 0;
}

int main(){
	int T; cin >> T; 
	while (T--){
		cin >> n;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				cin >> a[i][j];
				alive[i][j] = 1;
			}
		}
		for (int col = 1; col <= n; col++){
			// build graph
			for (int i = 1; i <= n; i++){
				G[i].clear();
				belong[i] = {0, 0};
			}
			for (int i = 1; i <= n; i++){
				for (int j = 1; j <= n; j++){
					if (alive[i][j]){
						G[i].push_back({a[i][j], j});
					}
				}
			}
			for (int i = 1; i <= n; i++){
				memset(vis, 0, sizeof(vis));
				assert(dfs(i));
			}
			for (int i = 1; i <= n; i++){
				auto [x, y] = belong[i];
				alive[x][y] = 0;
				row[x][col] = y;
			}
		}
		cout << (n*n-n)/2 << '\n';
		for (int i = 1; i <= n; i++){
			for (int j = i+1; j <= n; j++){
				cout << i << ' ' << row[i][j] << ' ';
				cout << j << ' ' << row[j][i] << '\n';
			}
		}
	}

	return 0;
}