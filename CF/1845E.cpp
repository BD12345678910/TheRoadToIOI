#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int n, k;
vector<int> V;
int dp[1503][1503];
int dpp[1503][1503];

int main(){
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		char c; cin >> c;
		if (c == '1') V.push_back(i);
	}
	int L = V.size();
	dp[0][0] = 1; 
	for (int i = 0; i < L; i++){
		memset(dpp, 0, sizeof(dpp));
		for (int j = 0; j <= n; j++){
			int d = abs(V[i]-j);
		}
		memcpy(dp, dpp, sizeof(dpp));
	}
	return 0;
}






