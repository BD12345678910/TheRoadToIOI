#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int d[1003][1003];
bool vis[1003][1003];
string s[1003][1003];
string fs[1003];

void init(){
	string super = string(N+5, 'k');
	for (int i = 1; i <= N; i++){
		fs[i] = super;
	}
	memset(d, 0x3f, sizeof(d));
	d[1][1] = 0;
	priority_queue<pair<int,pair<int,int>>> P;
	P.push({0,{1,1}});
	while (!P.empty()){
		auto [_, x] = P.top(); P.pop();
		int n = x.first, p = x.second;
		// cout << n << ' ' << p << ' ' << d[n][p] << endl;
		if (vis[n][p]) continue;
		vis[n][p] = 1;
		if (fs[n].length()>s[n][p].length()){
			fs[n] = s[n][p];
		}
		if (p > 1){
			if (d[n][p-1] > d[n][p]+1){
				d[n][p-1] = d[n][p]+1;
				s[n][p-1] = s[n][p]+"l";
				P.push({-d[n][p-1], {n, p-1}});
			}
		}
		if (p < n){
			if (d[n][p+1] > d[n][p]+1){
				d[n][p+1] = d[n][p]+1;
				s[n][p+1] = s[n][p]+"h";
				P.push({-d[n][p+1], {n, p+1}});
			}
		}

		for (int k = 1; n+p*k <= N; k++){
			int nn = n+p*k;
			int pp = p+k;
			// cout << nn << ' ' <<pp << endl;
			if (d[nn][pp] > d[n][p]+k+1){
				d[nn][pp] = d[n][p]+k+1;
				s[nn][pp] = s[n][p]+"Y";
				for (int i = 1; i <= k; i++){
					s[nn][pp] += "P";
				}
				P.push({-d[nn][pp], {nn, pp}});
			}
		}
	}
}

int main(){
	init();
	int T; cin >> T;
	while (T--){
		int n; cin >> n;
		cout << fs[n].length() << ' ' << fs[n] << '\n';
	}
	return 0;
}