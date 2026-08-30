#include "graph.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> G[202];
int color[202];

void mydfs(int x){
	for (int v : G[x]){
		if (!color[v]){
			color[v] = 3-color[x];
			mydfs(v);
		}
	}
}

vector<int> check_bipartite(int n){
	// consider island i
	vector<pair<int,int>> P;
	for (int i = 0; i < n; i++){
		// add j and remove:
		for (int j = i+1; j < n; j++){
			P.push_back({i, j});
			if (!query(P)) {
				G[i].push_back(j);
				G[j].push_back(i);
				P.pop_back();
			} 
		}
	}

	color[0] = 1; mydfs(0);
	vector<int> ans;
	for (int i = 0; i < n; i++){
		if (color[i]==1) 
			ans.push_back(i);
	}
	return ans;
}


