// template for ODT Tree :)
// expected queries before removal of segment roughly 4, O(1)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// because placed in set, mutable v is ok because ordering 
// is not dependent on it
// usually, set assumes that the ordering is unchanged by changes
struct Node{
	int l, r; mutable ll v;
	bool operator<(const Node &o) const { return l < o.l; }
};

int n, m; ll seed, vmax;
set<Node> s;

ll rnd(){
	ll ret = seed;
	seed = (seed * 7 + 13) % 1000000007;
	return ret;
}

// break so that returned iterator->l = p
set<Node>::iterator split(int p){
	if (p > n) return s.end();
	auto it = prev(s.upper_bound({p,0,0}));
	if (it->l == p) return it;
	int l = it->l, r = it->r; ll v = it->v;
	s.erase(it);
	s.insert({l, p-1, v});
	return s.insert({p, r, v}).first;
}

void add(int l, int r, ll v){
	auto R = split(r+1), L = split(l);
	for (auto it = L; it != R; it++){
		it->v += v;
	}
}

void assign(int l, int r, ll v){
	auto R = split(r+1), L = split(l);
	s.erase(L, R);
	s.insert({l, r, v});
}

ll kth(int l, int r, int k){
	auto R = split(r+1), L = split(l);
	vector<pair<ll,int>> a;
	for (auto it = L; it != R; it++){
		a.push_back({it->v, it->r-it->l+1});
	}
	sort(a.begin(), a.end());
	for (auto [v, len] : a){
		if (k <= len) return v;
		k -= len;
	}
}

ll power(ll a, ll b, ll mod){
	ll ret = 1; a %= mod;
	while (b){
		if (b&1) ret = ret*a%mod;
		a = a*a%mod; 
		b >>= 1;
	}
	return ret;
}

ll sum(int l, int r, ll k, ll mod){
	auto R = split(r+1), L = split(l);
	ll ans = 0;
	for (auto it = L; it != R; it++){
		ans = (ans + power(it->v, k, mod) * (it->r-it->l+1)) % mod;
	}
	return ans;
}

int main(){
	cin >> n >> m >> seed >> vmax;
	for (int i = 1; i <= n; i++) s.insert({i, i, rnd()%vmax+1});
	while (m--){
		int op=rnd()%4+1, l=rnd()%n+1, r=rnd()%n+1;
		if (l>r) swap(l,r);
		ll x = (op==3) ? rnd()%(r-l+1)+1 : rnd()%vmax+1;
		if (op == 1) add(l, r, x);
		if (op == 2) assign(l, r, x);
		if (op == 3) cout << kth(l, r, x) << '\n';
		if (op == 4) cout << sum(l, r, x, rnd()%vmax+1) << '\n';
	}
	return 0;
}