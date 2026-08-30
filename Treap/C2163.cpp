#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rt, cnt;

struct Node{
	int val, lc, rc, sz;
	unsigned pri;
} t[200005];

int newNode(int v){
	t[++cnt] = {v,0,0,1,rng()};
	return cnt;
}

void pull(int x){
	t[x].sz = t[t[x].lc].sz + t[t[x].rc].sz + 1;
}

int merge(int a, int b){
	if (!a || !b) return a|b;
	if (t[a].pri < t[b].pri){
		t[a].rc = merge(t[a].rc, b);
		pull(a); return a;
	} else {
		t[b].lc = merge(a, t[b].lc);
		pull(b); return b;
	}
}

void split(int x, int &a, int &b, int k){
	if (!x) {a = b = 0; return;}
	if (t[t[x].lc].sz >= k){
		split(t[x].lc, a, t[x].lc, k);
		pull(b = x);
	} else {
		split(t[x].rc, t[x].rc, b, k-t[t[x].lc].sz-1);
		pull(a = x);
	}
}

int n, k;

int main(){
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		rt = merge(rt, newNode(i));
	}
	int curr = 1;
	int alive = n;
	for (int i = 1; i <= n; i++){
		int now = k % alive;
		// take the now'th element
		curr = curr + now;
		if (curr > alive) curr -= alive;
		int a,b,c;
		split(rt, a, c, curr-1);
		split(c, b, c, 1);
		cout << t[b].val << '\n';
		rt = merge(a, c);
		alive--;
		if (curr > alive) curr -= alive;
	}
	return 0;
}



