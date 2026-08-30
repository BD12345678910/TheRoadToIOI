#include <bits/stdc++.h>
using namespace std;

int h, w, q;
char what[200005];
vector<pair<int,int>> row[1000006];
int best[1000006];

int main(){
	cin >> h >> w >> q;
	what[0] = 'A';
	for (int i = 1; i <= q; i++){
		int r, c; cin >> r >> c >> what[i];
		row[r].push_back({c, i});
	}
	vector<vector<char>> ans(h+2, vector<char>(w+2));
	for (int x = h; x >= 1; x--){
		for (auto [c, i]: row[x]){
			best[c] = max(best[c], i);
		}
		for (int y = w-1; y >= 1; y--){
			best[y] = max(best[y+1], best[y]);
		}
		for (int y = 1; y <= w; y++){
			ans[x][y] = what[best[y]];
		}
	}
	for (int i = 1; i <= h; i++){
		for (int j = 1; j <= w; j++){
			cout << ans[i][j];
		}
		cout << '\n';
	}
	return 0;
}