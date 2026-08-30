#include <bits/stdc++.h>
using namespace std;

int n, N;
int a[200005];
int cur[200005];
vector<int> tmp[200005];
int nxt[200005];
bool bb[200005];
int t[200005];

void add(int x, int v){
	for (int i = x; i <= N; i += i&(-i)){
		t[i] += v;
	}
}
int qry(int x){
	int s = 0;
	for (int i = x; i; i -= i&(-i)){
		s += t[i];
	}
	return s;
}
int id(int x){
	if (x < 0) return n-x;
	else return x;
}

int main(){
	cin >> n; N = n<<1;
	for (int i = 1; i <= N; i++){
		add(i, 1);
		cin >> a[i];
	}
	for (int i = 1; i <= N; i++){
		int me = id(a[i]);
		int opp = id(-a[i]);
		if (cur[opp] == (int)tmp[opp].size()) {
			tmp[me].push_back(i);
		} else {
			int last = tmp[opp][cur[opp]++];
			nxt[last] = i;
			bb[last] = 1;
		}
	}
	long long ans = 0;
	for (int i = 1; i <= N; i++){
		if (bb[i]){
			int p = nxt[i];
			int dist = qry(p-1) - qry(i);
			if (a[i] > 0) dist++;
			ans += dist;
			add(p, -1);
		}
	}
	cout << ans << '\n';

	return 0;
}