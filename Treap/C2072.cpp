#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
	char ch; int lc, rc, sz;
	ui pri;
} t[200005];

int root, cnt;

int newNode(char c){
	t[++cnt] = {c, 0, 0, 1, rng()};
	return cnt;
}

void pull(int x){
	t[x].sz = t[t[x].lc].sz + t[t[x].rc].sz + 1;
}

int merge(int x, int y){
	if (!x || !y) return x|y;
	if (t[x].pri < t[y].pri){
		t[x].rc = merge(t[x].rc, y);
		pull(x); return x;
	} else {
		t[y].lc = merge(x, t[y].lc);
		pull(y); return y;
	}
}

void split(int x, int &a, int &b, int k){
	if (!x) {a = b = 0; return;}
	if (t[t[x].lc].sz >= k){
		split(t[x].lc, a, t[x].lc, k);
		// x becomes the larger part
		pull(x); b = x;
	} else {
		split(t[x].rc, t[x].rc, b, k-t[t[x].lc].sz-1);
		pull(x); a = x;
	}
}

void traverse(int x){
	if (t[x].lc){
		traverse(t[x].lc);
	}
	cout << t[x].ch;
	if (t[x].rc){
		traverse(t[x].rc);
	}
}

int n, m;

int main(){
	cin >> n >> m;
	string s; cin >> s;
	s = "$"+s;
	for (int i = 1; i <= n; i++){
		root = merge(root, newNode(s[i]));
	}
	for (int i = 1; i <= m; i++){
		int l, r; cin >> l >> r;
		int a, b, c; 
		split(root, a, c, r);
		split(a, a, b, l-1);
		root = merge(merge(a, c), b);
	}
	traverse(root);
	return 0;
}



