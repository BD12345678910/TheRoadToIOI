#include <bits/stdc++.h>
using namespace std;

int n, k;
int A, B;
pair<int,int> P[100005];
int pmx[100005];

int rec(int x){
	if (x == 1) return P[x].first;
	int far = max(rec(x-1), pmx[x-2]);
	return max(min(far, P[x].first)+P[x].second, P[x].first);
}

bool solve(){
	cin >> n >> k; n--;
	cin >> A >> B;
	for (int i = 1; i <= n; i++){
		cin >> P[i].first >> P[i].second;
	}
	if (A + B < k) return 0;
	if (A >= k) return 1;
	if (n == 0) return 0;
	sort(P+1, P+n+1);
	for (int i = 1; i <= n; i++){
		pmx[i] = max(pmx[i-1], P[i].first+P[i].second);
	}
	// if A is not largest
	if (P[n].first >= A) return 1;
	// if A is largest: a's that are not max
	if (pmx[n-1] >= k-B) return 1;
	// if A is largest: the a that is maximum: recurse:
	if (rec(n) >= k-B) return 1;
	return 0;
}

int main(){
	int T; cin >> T;
	while (T--) {
		if (solve()) cout << "YES\n";
		else cout << "NO\n";
	}
}