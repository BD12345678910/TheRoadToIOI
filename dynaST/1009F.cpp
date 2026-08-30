#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> G[1000006];
int ans[1000006];
int best[1000006];
vector<int> V[1000006];

void merge(int x, int y){
	vector<int> &A = V[x], &B = V[y]; 
	if (A.size() < B.size()) {
		swap(A, B);
		swap(best[x], best[y]);
	}
	int a = A.size(), b = B.size();
	for (int i = a-b; i < a; i++){
		A[i] += B[i-(a-b)];
		if (A[i]>A[best[x]]||(A[i]==A[best[x]]&&i>best[x])){
			best[x] = i;
		}
	}
	B.clear();
}

void dfs(int x, int pa){
	for (int v : G[x]){
		if (v == pa) continue;
		dfs(v, x);
		merge(x, v);
	}
	V[x].push_back(1);
	int i = V[x].size()-1;
	vector<int> &A = V[x];
	if (A[i]>A[best[x]]||(A[i]==A[best[x]]&&i>best[x])){
		best[x] = i;
	}
	ans[x] = V[x].size()-1-best[x];
}

int main(){
	cin >> n;
	for (int i = 1; i < n; i++){
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1, 1);
	for (int i = 1; i <= n; i++){
		cout << ans[i] << '\n';
	}
	return 0;
}


