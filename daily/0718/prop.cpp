#include <bits/stdc++.h>
using namespace std;

const int D = 400000;
int n, k;
int a[200005];
pair<int,int> ind[200005];
int belong[200005];
// 160 MB
bool dp[26][800005];
int last[26][800005];
map<int,vector<int>> M;

void answer(int X, int Y){
	vector<int> add, subtract;
	for (int j = 0; j < n; j++){
		if ((X>>j)&1){
			add.push_back(j+1);
		} 
		if ((Y>>j)&1){
			subtract.push_back(j+1);
		}
	}
	cout << (int)add.size() << ' ';
	for (int x : add) cout << x << ' ';
	cout << '\n';
	cout << (int)subtract.size() << ' ';
	for (int x : subtract) cout << x << ' ';
	cout << '\n';
}

int main(){
	freopen("prop.in", "r", stdin);
	freopen("prop.out", "w", stdout);
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		ind[i] = {a[i], i};
	}

	if (n <= 25){
		int N = 1<<n;
		for (int i = 1; i < N; i++){
			int s = 0;
			for (int j = 0; j < n; j++){
				if ((i>>j) & 1){
					s += a[j+1];
				}
			}
			if (M.count(s)){
				for (int x : M[s]){
					if ((x&i) == 0 && __builtin_popcount(x|i) >= n-k){
						answer(x, i);
						return 0;
					}
				}
				M[s].push_back(i);
			} else {
				M[s] = vector<int>{i};
			}
		}
		cout << -1 << endl;
	} else {
		sort(a+1, a+n+1, greater<int>());
		sort(ind+1, ind+n+1, greater<pair<int,int>>());
		int curr = 0;
		int up = n-min(25, k);
		for (int i = 1; i <= up; i++){
			if (curr <= 0) {
				belong[i] = 1;
				curr += a[i];
			} else {
				belong[i] = 2;
				curr -= a[i];
			}
		}

		dp[0][D] = 1;
		for (int i = up+1; i <= n; i++){
			int idx = i-up;
			for (int j = -400000; j <= 400000; j++){
				if (j-a[i]>=-400000) {
					if (dp[idx-1][D+j-a[i]]) {
						dp[idx][D+j] = 1;
						last[idx][D+j] = i;
					}
				}
				if (j+a[i]<=400000){
					if (dp[idx-1][D+j+a[i]]){
						dp[idx][D+j] = 1;
						last[idx][D+j] = -i;
					}
				}
				if (dp[idx-1][D+j]){
					dp[idx][D+j] = 1;
					last[idx][D+j] = 0;
				}
			}
		}
		if (dp[n-up][D-curr]){
			int tmp = -curr;
			for (int i = n; i >= up+1; i--){
				int idx = i-up;
				if (last[idx][D+tmp] > 0){
					belong[i] = 1;
					tmp -= a[last[idx][D+tmp]];
				} else if (last[idx][D+tmp] < 0){
					belong[i] = 2;
					tmp += a[-last[idx][D+tmp]];
				} else {
					belong[i] = 0;
				}
			}
			vector<int> add, subtract;
			long long s1 = 0, s2 = 0; int cnt = 0;
			for (int i = 1; i <= n; i++){
				if (belong[i]==1) {
					add.push_back(i);
					s1 += a[i];
					cnt++;
				}
				else if (belong[i]==2){
					subtract.push_back(i);
					s2 += a[i];
					cnt++;
				}
			}
			assert(s1 == s2);
			assert(cnt >= n-k);
			cout << (int)add.size() << ' ';
			for (int x : add) cout << ind[x].second << ' ';
			cout << '\n';
			cout << (int)subtract.size() << ' ';
			for (int x : subtract) cout << ind[x].second << ' ';
			cout << '\n';
		} else {
			cout << -1 << '\n';
		}
	}

	return 0;
}


