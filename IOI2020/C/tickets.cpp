#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

int freq[1505];
int cur[1505];
int up[1505];

long long find_maximum(int k, vector<vector<int>> x) {
	int n = x.size();
	int m = x[0].size();
	long long ans = 0;
	vector<vector<int>> answer(n, vector<int>(m, -1));
	vector<vector<bool>> nulll(n, vector<bool>(m, 0));

	vector<pair<int,pair<int,int>>> VV;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			VV.push_back({x[i][j], {i, j}});
		}
	}
	sort(VV.begin(), VV.end());
	for (int i = 0; i < n*m/2; i++){
		int xx = VV[i].second.first, yy = VV[i].second.second;
		nulll[xx][yy] = 1;
		ans -= VV[i].first;
	}
	for (int i = n*m/2; i < n*m; i++){
		ans += VV[i].first;
	}

	// x = 0 or 1
	// for each round, take the largest n/2;
	for (int i = 0; i < n; i++){
		cur[i] = 0; up[i] = m-1;
		for (int j = 0; j < m; j++){
			if (nulll[i][j]){
				freq[i]++;
			}
		}
	}

	for (int rd = 0; rd < k; rd++){
		// for this round, take the n/2 largest when possible:
		vector<pair<int,int>> V;
		for (int i = 0; i < n; i++){
			V.push_back({freq[i], i});
		}
		sort(V.begin(), V.end(), greater<pair<int,int>>());

		int took;
		for (took = 0; took < n/2; took++){
			answer[V[took].second][cur[V[took].second]++] = rd;
			freq[V[took].second]--;
		}
		for (int i = took; i < n; i++){
			answer[V[i].second][up[V[i].second]--] = rd;
		}
	}

	allocate_tickets(answer);
	return ans;
}
