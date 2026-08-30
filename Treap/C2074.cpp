#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
	int val; int lc, rc, sz;
	ll suma; bool rev; ui pri;
} t[200005];

int root, cnt;

int newNode(int v){
	t[++cnt] = {v, 0, 0, 1, v, 0, rng()};
	return cnt;
}

void pull(int x){
	t[x].sz = t[t[x].lc].sz + t[t[x].rc].sz + 1;
	t[x].suma = t[t[x].lc].suma + t[t[x].rc].suma +t[x].val;
}

void push(int x){
	if (t[x].rev){
		swap(t[x].lc, t[x].rc);
		if (t[x].lc) t[t[x].lc].rev ^= 1;
		if (t[x].rc) t[t[x].rc].rev ^= 1;
		t[x].rev = 0;
	}
	t[x].suma = t[t[x].lc].suma + t[t[x].rc].suma + t[x].val;
}

int merge(int x, int y){
	if (!x || !y) return x | y;
	if (t[x].pri < t[y].pri){
		push(x);
		t[x].rc = merge(t[x].rc, y);
		pull(x); return x;
	} else {
		push(y);
		t[y].lc = merge(x, t[y].lc);
		pull(y); return y;
	}
}

void split(int x, int &a, int &b, int k){
	if (!x) {a = b = 0; return ;}
	push(x);
	if (t[t[x].lc].sz >= k){
		split(t[x].lc, a, t[x].lc, k);
		pull(x); b = x;
	} else {
		split(t[x].rc, t[x].rc, b, k-t[t[x].lc].sz-1);
		pull(x); a = x;
	}
}

int n, m;

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		int x; cin >> x;
		root = merge(root, newNode(x));
	}
	while (m--){
		// traverse(root); cout << endl;
		int op, l, r, a, b, c; cin >> op >> l >> r;
		split(root, a, c, r);
		split(a, a, b, l-1);
		if (op == 1){
			t[b].rev ^= 1;
		} else {
			cout << t[b].suma << '\n';
		}
		root = merge(a, merge(b, c));
	}

	return 0;
}



