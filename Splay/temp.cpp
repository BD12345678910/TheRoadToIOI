#include <bits/stdc++.h>
using namespace std;
const int N = 1000006;

struct Node{
	int key, l, r, p;
} t[N];

void rotate(int x){
	int pa = t[x].p;
	if (t[pa].l == x){
		t[pa].l = t[x].r;
		if (t[x].r) t[t[x].r].p = pa;
		t[x].r = pa;
	} else {
		t[p].r = t[x].l;
		if (t[x].l) t[t[x].l].p = pa;
		t[x].l = pa;
	}
	int grand = t[pa].p;
	t[pa].p = x;
	t[x].p = grand;
	
}

int main(){

	return 0;
}