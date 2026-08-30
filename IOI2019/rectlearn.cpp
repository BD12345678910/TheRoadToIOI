#include <bits/stdc++.h>
using namespace std;

const int N = 2520;
int n, m, a[N][N], stk[N], cnt, top, ans;
vector<int> ok[N][N];
pair<int,int> tmp[N]; 
int lok[N][N], rok[N][N];

// universal machine...
void solve(int *num, int len){
	cnt = top = 0;
	for (int i = 1; i <= len; i++){
		while (top && num[i] > num[stk[top]]){
			if (i > stk[top]+1){
				tmp[++cnt] = {stk[top]+1, i-1};
			}
			top--;
		}
		if (top){
			if (i > stk[top]+1){
				tmp[++cnt] = {stk[top]+1, i-1};
			}
			if (num[i]==num[stk[top]]) top--;
		}
		stk[++top] = i;
	}
}

void calc(int l, int r, int u, int d){
	int len = 0;
	for (int i = u-1; i <= d+1; i++){
		a[0][++len] = a[i][r];
	}
	solve(a[0], len);
	for (int i = 1; i <= cnt; i++){
		int tl = tmp[i].first+u-2;
		int tr = tmp[i].second+u-2;
		if (lok[tl][tr] <= l) ans++;
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for (int i = 2; i < n; i++){
		solve(a[i], m);
		for (int j = 1; j <= cnt; j++){
			ok[tmp[j].first][tmp[j].second].push_back(i);
		}
	}
	for (int r = 2; r < m; r++){
		for (int i = 1; i <= n; i++) a[0][i] = a[i][r];
		solve(a[0], n);
		for (int i = 1; i <= cnt; i++){
			if (rok[tmp[i].first][tmp[i].second]+1 < r)
				lok[tmp[i].first][tmp[i].second] = r;
			rok[tmp[i].first][tmp[i].second] = r;
		}
		for (int l = 2; l <= r; l++){
			if (!ok[l][r].size()) continue;
			int lst = ok[l][r][0];
			for (int i = 1; i < (int)ok[l][r].size(); i++){
				if (ok[l][r][i] > ok[l][r][i-1]+1){
					calc(l, r, lst, ok[l][r][i-1]);
					lst = ok[l][r][i];
				}
			}
			calc(l, r, lst, ok[l][r][ok[l][r].size()-1]);
		}
	}
	cout << ans << endl;
	return 0;
}




