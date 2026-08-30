#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INFF = 1e18;
const ll INF = 1000000001LL;
map<ll,bool> vis;
map<ll,ll> dist;
vector<int> sky[100005];
ll code(int x, int y){return INF*x+y;}
ll min_distance(vector<int> X, vector<int> H, vector<int> L, vector<int> R, vector<int> Y, int S, int G) {
	int m = L.size();
	for (int i = 0; i < m; i++){
		for (int j = L[i]; j <= R[i]; j++){
			if (H[j] < Y[i]) continue;
			sky[j].push_back(i);
		}
	}
	priority_queue<pair<ll,pair<int,int>>> P;
	P.push({0, {S, 0}});
	dist[code(S, 0)] = 0;
	ll ans = INFF;
	while (!P.empty()){
		ll d = P.top().first;
		auto x = P.top().second; 
		P.pop();
		ll me = code(x.first, x.second);
		if (vis.count(me)) continue;
		// cout << x.first << ' ' << x.second << ' ' << -d << '\n';
		if (x.first == G) ans = min(ans, -d + x.second);
		vis[me] = 1;
		for (int sk : sky[x.first]){
			for (int j = L[sk]; j <= R[sk]; j++){
				if (H[j] < Y[sk]) continue;
				ll c = code(j, Y[sk]);
				if (!vis.count(c)){
					ll cand = dist[me]+abs(x.second-Y[sk])+abs(X[j]-X[x.first]);
					// cout << "!" << j << ' ' << cand << endl;
					if (!dist.count(c) || cand < dist[c]){
						dist[c] = cand;
						P.push({-dist[c], {j, Y[sk]}});
					}
				}
			}
		}
	}
	if (ans == INFF) ans = -1;
	return ans;
}



/*
7 7
0 8 3 7 5 9 7 7 10 6 12 6 14 9                       
0 1 1   
0 2 6
0 6 8
2 3 1
2 6 7
3 4 2
4 6 5
1 5
*/



