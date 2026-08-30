#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INFF = 1e18;
const ll INF = 1000000001LL;
pair<int,int> tmp[100005];
pair<int,int> tmpbr[100005];
set<int> SS;

map<ll,bool> vis;
map<ll,ll> dist;
vector<int> sky[100005];
vector<int> ofsky[100005];
ll code(int x, int y){return INF*x+y;}

ll min_distance(vector<int> X, vector<int> H, vector<int> L, vector<int> R, vector<int> Y, int S, int G) {
	int m = L.size(), n = X.size();
	for (int i = 0; i < m; i++) tmpbr[i] = {Y[i], i};
	sort(tmpbr, tmpbr+m);
	for (int i = 0; i < n; i++) tmp[i] = {H[i], i};
	sort(tmp, tmp+n);
	int curr = n-1;
	for (int i = m-1; i >= 0; i--){
		while (curr >= 0 && tmp[curr].first >= tmpbr[i].first){
			SS.insert(tmp[curr].second);
			curr--;
		}
		int idx = tmpbr[i].second;
		auto no = SS.upper_bound(R[idx]);
		for (auto it = SS.lower_bound(L[idx]); it != no; it++){
			sky[*it].push_back(idx);
			ofsky[idx].push_back(*it);
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
			for (int j : ofsky[sk]){
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



