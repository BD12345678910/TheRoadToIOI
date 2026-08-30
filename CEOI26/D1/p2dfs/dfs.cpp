#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1e9+7;
int n, root;
vector<int> G[200005];
int fa[200005], prv;
int dep[200005];

// range: [0,n]
int curmax[200005];
ll ans = 0;

int t[200005];
void add(int x, int v){
	// cout << x << ' ' << v << endl;
	x++;
	for (int i = x; i <= n+1; i += i&(-i)){
		t[i] += v;
	}
}
int qry(int x){
	x++; int s = 0;
	for (int i = x; i; i -= i&(-i)){
		s += t[i];
	}
	return s;
}
int qry(int x, int y){
	// cout << "Queried: " << x << ' ' << y << endl;
	if (x > y) return 0;
	return qry(y)-qry(x-1);
}

void dfs(int x){
	// cout << x << endl;
	ans += qry(1, x-1);
	add(curmax[x], 1);
	for (int v : G[x]){
		add(curmax[x], -1);
		curmax[x] = v;
		add(curmax[x], 1);
		dfs(v);
	}
	add(curmax[x], -1);
}

ll qpow(ll x, ll nn){
	ll res = 1;
	while (nn){
		if (nn & 1) res = res * x % MOD;
		x = x * x % MOD;
		nn >>= 1;
	}
	return res;
}

int main() {
	// freopen("00.in", "r", stdin);
	// freopen("00.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
    int d, x; char slash;
    while (cin >> d >> slash >> x) {
        ++n; ++x;
		dep[x] = d;
		if (n == 1){
			root = prv = x;
		} else {
			while (d != dep[prv]+1){
				prv = fa[prv];
			}
			fa[x] = prv;
			G[prv].push_back(x);
			prv = x;
		}
	}

	dfs(root);
	cout << qpow(2LL, ans) << endl;
	return 0;
}

