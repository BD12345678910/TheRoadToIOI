#include <bits/stdc++.h>
using namespace std;

set<vector<int>> S;
vector<int> prime;
bool p[1000006];
vector<int> VV[1000006];

int main(){
	fill(p+1, p+1000001, 1);
	for (int i = 2; i <= 1000000; i++){
		if (p[i]){
			prime.push_back(i);
			for (int j = i + i; j <= 1000000; j+=i){
				p[j] = 0;
			}
		}
	}
	cout << prime.size() << endl;
	for (int pp : prime){
		for (int i = pp; i <= 1000000; i += pp){
			int t = 0;
			int cop = i;
			while (cop % pp == 0){
				cop /= pp;
				t++;
			}
			VV[i].push_back(t);
		}
	}
	for (int i = 1; i <= 1000000; i++){
		sort(VV[i].begin(), VV[i].end());
		S.insert(VV[i]);
	}
	cout << S.size();
	return 0;
}


// conclusion: the number of primes below 1e6 is 78498
// the number of different signatures below 1e6 is 289


