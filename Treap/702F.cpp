#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int n, q;
pii tshirt[200005];
pii tmp[200005];

int rt, cnt;
struct Node{
	int C, lc, rc, sz, lz, id;
	unsigned pri;
	int buy, buylz;
} t[200005];
int ans[200005];

int newNode(int val, int id){
	t[++cnt] = {val, 0, 0, 1, 0, id, rng(), 0, 0};
	return cnt;
}

void pull(int x){
	t[x].sz = t[t[x].lc].sz + t[t[x].rc].sz + 1;
}

void push(int x){
	int l = t[x].lc;
	int r = t[x].rc;
	if (t[x].lz){
		if (l) {
			t[l].C -= t[x].lz;
			t[l].lz += t[x].lz;
		}
		if (r) {
			t[r].C -= t[x].lz;
			t[r].lz += t[x].lz;
		}
		t[x].lz = 0;
	}
	if (t[x].buylz){
		if (l){
			t[l].buy += t[x].buylz;
			t[l].buylz += t[x].buylz;
		}
		if (r){
			t[r].buy += t[x].buylz;
			t[r].buylz += t[x].buylz;
		}
		t[x].buylz = 0;
	}
}

int merge(int a, int b){
	if (!a || !b) return a|b;
	if (t[a].pri < t[b].pri){
		push(a);
		t[a].rc = merge(t[a].rc, b);
		pull(a); return a;
	} else {
		push(b);
		t[b].lc = merge(a, t[b].lc);
		pull(b); return b;
	}
}

void split(int x, int &a, int &b, int k){
	if (!x) {a = b = 0; return;}
	push(x);
	if (t[x].C >= k){
		split(t[x].lc, a, t[x].lc, k);
		pull(b = x);
	} else {
		split(t[x].rc, t[x].rc, b, k);
		pull(a = x);
	}
}

// MELD

bool keyLess(int x, int C, int id){
	if (t[x].C != C) return t[x].C < C;
	return t[x].id < id;
}

void splitKey(int x, int &a, int &b, int C, int id){
	if (!x) {a = b = 0; return;}
	push(x);
	if (keyLess(x, C, id)){
		splitKey(t[x].rc, t[x].rc, b, C, id);
		a = x; pull(a);
	} else {
		splitKey(t[x].lc, a, t[x].lc, C, id);
		b = x; pull(b);
	}
}

int meld(int a, int b){
	if (!a || !b) return a | b;
	if (t[a].pri > t[b].pri) swap(a, b);
	push(a); push(b);
	int bl, br;
	// split by a's key!
	splitKey(b, bl, br, t[a].C, t[a].id);
	// insert into a
	t[a].lc = meld(t[a].lc, bl);
	t[a].rc = meld(t[a].rc, br);
	pull(a); return a;
}

bool cmp(pii A, pii B){
	if (A.first != B.first) return A.first > B.first;
	return A.second < B.second;
}

void collect(int x){
	ans[t[x].id] = t[x].buy;
	push(x);
	if (t[x].lc) collect(t[x].lc);
	if (t[x].rc) collect(t[x].rc);
}

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> tshirt[i].second >> tshirt[i].first;
	}
	sort(tshirt+1, tshirt+n+1, cmp);
	cin >> q;
	for (int i = 1; i <= q; i++){
		int c; cin >> c;
		tmp[i] = {c, i};
	}
	sort(tmp+1, tmp+q+1);
	for (int i = 1; i <= q; i++){
		rt = merge(rt, newNode(tmp[i].first, tmp[i].second));
	}
	for (int i = 1; i <= n; i++){
		// try buying the i'th tshirt:
		// b = tree of those who can afford
		int cost = tshirt[i].second;
		int a, b; split(rt, a, b, tshirt[i].second);
		if (b){
			t[b].buy++;
			t[b].buylz++;
			t[b].C -= cost;
			t[b].lz += cost;
		} 
		rt = meld(a, b);
	}
	collect(rt);
	for (int i = 1; i <= q; i++){
		cout << ans[i] << " \n"[i == q];
	}

	return 0;
}


