#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;
int n, m;
int cnt[100005];
int fa[100005];
int sz[100005];
bool vis[100005];
int ed[100005];

ll qpow(ll x, ll nn){
	ll res = 1;
	while (nn){
		if (nn % 2) res = res * x % MOD;
		nn >>= 1;
		x = x * x % MOD;
	}
	return res;
}

int find(int x){
	if (fa[x]==x) return x;
	return fa[x] = find(fa[x]);
}

int main(){
	ll s = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		fa[i] = i; sz[i] = 1;
	}
	for (int i = 1; i <= m; i++){
		int a,b; cin >> a >> b;
		cnt[a]++; 
		a = find(a); b = find(b);
		if (a == b) continue;
		fa[a] = b;
		sz[b] += sz[a];
	}
	for (int i = 1; i <= n; i++){
		ed[find(i)] += cnt[i];
	}
	for (int i = 1; i <= n; i++){
		int x = find(i);
		if (!vis[x]){
			s += (ed[x]-sz[x]+1);
			vis[x] = 1;
		}
	}
	cout << qpow(2LL, s) << endl;

	return 0;
}




