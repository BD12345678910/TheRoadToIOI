struct DSU{
	int fa[N], sz[N], comp;
	vector<pair<int,int>> stk;

	int find(int x){
		if (fa[x]==x) return x;
		return find(fa[x]);
	}

	int snap() {return stk.size();}
	void join(int a, int b){
		a = find(a); b = find(b);
		if (a == b){
			stk.push_back({-1, 1});
			return;
		}
		if (sz[a] < sz[b]) swap(a, b);
		stk.push_back({b, sz[a]});
		fa[b] = a;
		sz[a] += sz[b];
		comps--;
	}
	void rollback(int s){
		while ((int) stk.size() > s){
			auto [b, old] = stk.back();
			stk.pop_back();
			if (b == -1) continue;
			int a = fa[b];
			sz[a] = old;
			fa[a] = b;
			comps++;
		}
	}
}