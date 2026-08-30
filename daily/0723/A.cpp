#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, K;
pair<int,int> p[103];
bool ori[103][103];
bitset<100> adj[103];
int W[103];

struct State{
	ll w;
	bitset<100> mask;
	int last;
	bool operator<(const State &other) const{
		return w > other.w;
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("clique.in", "r", stdin);
	freopen("clique.out", "w", stdout);
	cin >> n >> K;
	for (int i = 0; i < n; i++){
		cin >> W[i];
		p[i] = {W[i], i};
	}
	sort(p, p+n);
	for (int i = 0; i < n; i++) W[i] = p[i].first;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			char c; cin >> c;
			ori[i][j] = (c=='1');
		}
	}
	for (int i = 0; i < n; i++){
		for (int j= 0; j < n; j++){
			adj[i][j] = ori[p[i].second][p[j].second];
		}
	}
	if (K == 1) {
		cout << 0 << endl;
		return 0;
	}

	K--;

	priority_queue<State> PQ;
	bitset<100> b; b[0] = 1;
	PQ.push({W[0], b, 0});

	while (!PQ.empty()){
		State me = PQ.top(); PQ.pop();
		bitset<100> B = me.mask;
		ll w = me.w;
		int i = me.last;
		K--;
		if (K == 0) {
			cout << w << endl;
			return 0;
		}
		for (int j = i+1; j < n; j++){
			if ((B & adj[j]) == B){
				B[j] = 1;
				PQ.push({w+W[j], B, j});
				B[j] = 0;
				break;
			}
		}
		B[i] = 0;
		for (int j = i+1; j < n; j++){
			if ((B & adj[j]) == B){
				B[j] = 1;
				PQ.push({w+W[j]-W[i], B, j});
				B[j] = 0;
				break;
			}
		}
	}
	cout << -1 << endl;
	return 0;
}


