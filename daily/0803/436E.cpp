// CUT THE ROPE

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
struct choice{
	int star, cost, idx;
	bool operator<(const choice &other) const{
		return 1LL * star * other.cost > 1LL * other.star * cost;
	}
};

int n, k;
int a[300005], b[300005];
vector<choice> P;
int t[300005];

int typ, re, add;
void update(ll &x, ll y, int ty, int rem, int ad){
	if (y < x) {
		x = y;
		typ = ty; re = rem; add = ad;
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> a[i] >> b[i];
	}
	for (int i = 1; i <= n; i++){
		if (a[i] < b[i]-a[i]){
			P.push_back({1, a[i], i});
			P.push_back({1, b[i]-a[i], i});
		} else {
			P.push_back({2, b[i], i});
		}
	}
	sort(P.begin(), P.end());
	int achieved = 0;
	ll cost = 0;
	ll ans = INF;
	for (int i = 0; i < (int)P.size(); i++){
		if (k-achieved >= P[i].star){
			achieved += P[i].star;
			t[P[i].idx] += P[i].star;
			cost += P[i].cost;
			if (achieved == k){
				ans = cost;
				break;
			}
		} else {
			// this means P[i].star = 2 and we have achieved = k-1
			// choice 1a: choose the later 1, which include 1->2
			for (int j = i+1; j < (int)P.size(); j++){
				if (P[j].star == 1){
					update(ans, cost + P[j].cost, 1, -1, P[j].idx);
					break;
				}
			}
			// choice 1b: choose any untaken 1
			for (int j = 1; j <= n; j++){
				if (t[j] == 0){
					update(ans, cost + a[j], 1, -1, j);
				}
			}

			// choice 2: remove the most expensive taken star 1
			int exp = 0, rem = 0;
			for (int j = 1; j <= n; j++){
				if (t[j] == 1){
					if (a[j] > exp){
						exp = a[j];
						rem = j;
					}
				}
			}
			if (rem) update(ans, cost-exp+P[i].cost, 2, rem, P[i].idx);

			// choice 3: remove the most expensive gap from 2 to 1 
			exp = 0, rem = 0;
			for (int j = 1; j <= n; j++){
				if (t[j] == 2){
					if (b[j]-a[j] > exp){
						exp = b[j]-a[j];
						rem = j;
					}
				}
			}
			if (rem) update(ans, cost-exp+P[i].cost, 2, rem, P[i].idx);
			break;
		}
	}
	if (typ == 1){
		t[add]++;
	} else if (typ == 2) {
		t[re]--;
		t[add]+=2;
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++){
		cout << t[i];
	}
	cout << endl;

	return 0;
}





