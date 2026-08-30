#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 3e11;
int n;
ll a[200005], b[200005], c[200005];
bool s[200005];

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		char c; cin >> c;
		s[i] = (c=='1');
	}
	for (int i = 1; i <= n; i++) cin >> a[i];

	vector<int> V; V.push_back(0);
	c[0] = 0; 
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		if (i == 1 || c[i] != c[i-1]) V.push_back(i);
	}
	int L = V.size();
	for (int i = 0; i < L-1; i++){
		// consider V[i] and V[i+1]
		ll running = 0;
		for (int j = V[i]+1; j <= V[i+1]; j++){
			if (!s[j]) a[j] = -INF;
			running += a[j];
		}
		ll needed = c[V[i+1]]-c[V[i]];
		ll increase = needed-running;
		for (int j = V[i+1]; j >= V[i]+1; j--){
			if (!s[j]) {a[j] += increase; break;}
		}
	}
	for (int i = V[L-1]+1; i <= n; i++){
		if (!s[i]) a[i] = -INF;
	}

	ll curr = 0, C = -INF;
	for (int i = 1; i <= n; i++){
		curr += a[i];
		C = max(C, curr);
		if (C != c[i]){
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++){
		cout << a[i] << ' ';
	}
	cout << '\n';
	return;
}

int main(){
	int T; cin >> T;
	while (T--) solve();
}

