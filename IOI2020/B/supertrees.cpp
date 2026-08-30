#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1003;

// each vector<int> is a tree
int tp;
vector<vector<int>> cc[N];

int construct(vector<vector<int>> p) {
	int n = p.size();
	vector<vector<int>> adj(n, vector<int>(n, 0));

	// consider where i belongs..
	tp = 0;
	for (int i = 0; i < n; i++){
		int c = 0;
		for (int j = 1; j <= tp; j++){
			if (p[i][cc[j][0][0]] != 0){
				c = j;
				break;
			}
		}
		if (!c){
			bool flag = 0;
			for (int k = 1; k <= tp; k++){
				for (auto v : cc[k]){
					for (int x : v){
						if (p[i][x] != 0) {
							flag = 1;
						}
					}
				}
			}
			if (flag){
				return 0;
			}
			vector<int> tmp; tmp.push_back(i);
			cc[++tp].push_back(tmp);
		} else {
			auto V = cc[c];
			int j = -1;
			for (int jj = 0; jj < (int)V.size(); jj++){
				if (p[i][V[jj][0]] == 1){
					j = jj;
					break;
				}
			}
			// put i into component c, j

			// check: V[j][~] should all be 1
			// V[~ not j][~] should all be 2
			// all others should be 0
			bool flag = 0;
			if (j != -1)
			for (int x : V[j]){
				if (p[x][i] != 1) flag = 1;
			}
			for (int k = 0; k < (int)V.size(); k++){
				if (k == j) continue;
				for (int x : V[k]){
					if (p[x][i] != 2) flag = 1;
				}
			}
			for (int k = 1; k <= tp; k++){
				if (k == c) continue;
				for (auto v : cc[k]){
					for (int x : v){
						if (p[x][i] != 0) flag = 1;
					}
				}
			}
			if (flag){
				return 0;
			}
			if (j == -1){
				vector<int> tmp; tmp.push_back(i);
				cc[c].push_back(tmp);
			} else {
				if ((int)cc[c][j].size() > 0){
					adj[cc[c][j][0]][i] = 1;
					adj[i][cc[c][j][0]] = 1;
				}
				cc[c][j].push_back(i);
			}
		}
	}

	for (int i = 1; i <= tp; i++){
		if (cc[i].size() == 1) continue;
		if (cc[i].size() == 2) return 0;
		int s = (int)cc[i].size()-1;
		for (int j = 0; j < s; j++){
			adj[cc[i][j][0]][cc[i][j+1][0]] = 1;
			adj[cc[i][j+1][0]][cc[i][j][0]] = 1;
		}
		adj[cc[i][0][0]][cc[i][s][0]] = 1;
		adj[cc[i][s][0]][cc[i][0][0]] = 1;
	}

	build(adj);
	return 1;
}
