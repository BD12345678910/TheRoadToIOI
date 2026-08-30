#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int ans[200005];
char c[200005]; 
ll s[200005];

struct T{
	int t[200005];
	void upd(int x, int v){
		for (int i = x; i <= n; i+=i&(-i)){
			t[i] += v; 
		}
	}
	int qry(int x){
		int s = 0;
		for (int i = x; i >= 1; i-=i&(-i)){
			s += t[i];
		}
		return s;
	}
	int kth(int x){
		int pos = 0;
		for (int pw = 1<<18; pw; pw >>= 1){
			int nxt = pos+pw;
			if (nxt <= n && t[nxt] < x){
				pos = nxt;
				x -= t[nxt];
			}
		}
		return pos + 1;
	}
} alive, I;

ll check(int mid, int l, int m){
	ll res = mid;
	for (int i = l+1; i < m; i++){
		if (alive.qry(s[i]) < mid) res++;
	}
	return res;
}

void solve(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> c[i] >> s[i];
		alive.upd(i, 1);
	}
	c[0] = 's'; s[0] = 0;
	for (int p = n; p >= 1; ){
		if (c[p] == 'p'){
			alive.upd(s[p], -1);
			ans[p] = s[p];
			p--;
			continue;
		} 
		int m = p, l = p-1;
		while (c[l] != 's') l--;
		ll C = m+s[l]-s[m]; int seen = 0;
		vector<int> touched;
		for (int j = m-1; j > l; j--){
			int x = alive.qry(s[j]);
			int internal = seen-I.qry(x);
			I.upd(x, 1);
			touched.push_back(x);
			seen++;
			C += (m-x)-internal;
		}
		for (int v : touched) I.upd(v, -1);

		// find y, the rank of p:
		int le = 1, ri = n;
		while (le < ri){
			int mid = (le+ri)>>1;
			if (check(mid, l, m) >= C) ri = mid;
			else le = mid+1;
		}
		int w = alive.kth(le);
		ans[p] = w;
		alive.upd(w, -1);
		p--;
	}
	for (int i = 1; i <= n; i++){
		cout << ans[i] << ' ';
	}
	cout << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T; cin >> T;
	while (T--) solve();

	return 0;
}





