#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull B = 131;

string s; int n, k;
ull hsh[1003], pw[1003];

ull get(int l, int r){
	return hsh[r]-hsh[l-1]*pw[r-l+1];
}

void solve(){
	cin >> s;
	cin >> k;
	n = s.length(); s = "#"+s;
	hsh[0] = 0; pw[0] = 1;
	for (int i = 1; i <= n; i++){
		hsh[i] = hsh[i-1]*B+s[i];
		pw[i] = pw[i-1]*B;
	}
	string ans = "";
	for (int len = 1; len <= n; len++){
		map<ull, vector<int>> M;
		for (int i = 1; i+len-1 <= n; i++){
			M[get(i, i+len-1)].push_back(i);
		}
		for (auto &[_, v]: M){
			int f = 1;
			for (int i = 1; i < (int)v.size(); i++){
				if (v[i] > v[i-1] + len){
					f++;
				}
			}
			if (f == k){
				string t = s.substr(v[0], len);
				if (ans == "" || t < ans) ans = t;
			}
		}
	}
	if (ans == "") ans = "-1";
	cout << ans << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("str.in", "r", stdin);
	freopen("str.out", "w", stdout);
	int T; cin >> T;
	while (T--){
		solve();
	}
}