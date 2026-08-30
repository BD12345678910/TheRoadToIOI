#include <bits/stdc++.h>
using namespace std;
int n;
int a[1000006];
int ans[1003];
bool used[1003][1003];
set<int> S;
map<int,int> M;
map<int,vector<int>> MM;

void solve(){
	cin >> n;
	int N = (n+1)*n/2-1;
	int T = 0;
	for (int i = 1; i <= N; i++){
		cin >> a[i]; T = max(a[i]);
		if (S.count(a[i])) M.erase(a[i]);
		else S.insert(a[i]);
	}
	vector<int> simsum;
	for (int x : S) {
		simsum.push_back(x);
	}
	int exp = (n+1)/2;
	if ((int)simsum.size()==exp){
		simsum.push_back(0);
		sort(simsum.begin(), simsum.end());
		for (int i = n/2; i >= 1; i--){
			ans[i] = ans[n+1-i] = simsum[n/2-i+1]-simsum[n/2-i];
		}
	} else if ((int)simsum.size()-1==exp){
		int l = simsum.size();
		for (int i = 0; i < l; i++){
			vector<int> tmp;
			for (int j = 0; j < l; j++){
				if (j == i) continue;
				tmp.push_back(simsum[j]);
			}
			tmp.push_back(0);
			sort(tmp.begin(), tmp.end());
			for (int j = n/2; j >= 1; j--){
				ans[j] = ans[n+1-j] = simsum[n/2-j+1]-simsum[n/2-j];
			}
			for (int j = 1; j <= N; j++){
				used[j] = 0;
				MM[a[j]].push_back(j);
				M[a[j]] = 0;
			}
			for (int j = 1; j < n; j++){
				for (int k = 1; k <= n; k++){

				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}