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

	// x = 0 or 1
	// for each round, take the largest n/2;
	for (int i = 0; i < n; i++){
		cur[i] = 0; up[i] = m-1;
		for (int j = 0; j < m; j++){
			if (x[i][j] == 0){
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
			if (V[took].first > 0){
				answer[V[took].second][cur[V[took].second]++] = rd;
				freq[V[took].second]--;
			} else {
				break;
			}
		}

		while (took < n && V[took].first == up[V[took].second]-cur[V[took].second]+1){
			answer[V[took].second][cur[V[took].second]++] = rd;
			freq[V[took].second]--;
			took++;
		}

		for (int i = took; i < n; i++){
			answer[V[i].second][up[V[i].second]--] = rd;
		}
		ans += min(took, n-took);
	}

	allocate_tickets(answer);
	return ans;
}
