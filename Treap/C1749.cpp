// https://cses.fi/alon/task/1749


#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int cnt, rt;

struct Node{
	int val, sz, lc, rc;
	unsigned pri;
} t[N];

int newNode(int val){
	t[++cnt] = {val, 1, 0, 0, rng()};
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
	if (t[t[x].lc].sz >= k) {
		split(t[x].lc, a, t[x].lc, k);
		pull(b = x);
	} else { 
		split(t[x].rc, t[x].rc, b, k-t[t[x].lc].sz-1);
		pull(a = x); 
	}
}

int n;

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		int x; cin >> x;
		rt = merge(rt, newNode(x));
	}
	for (int i = 1; i <= n; i++){
		int a, b, c, k; cin >> k;
		split(rt, a, c, k-1);
		split(c, b, c, 1);
		cout << t[b].val << '\n';
		rt = merge(a, c);
	}

	return 0;
}



