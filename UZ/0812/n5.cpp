// 3+4+5+6+5+5 = 28 points

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
int x[205];
int p[205];
int lab[205];
pair<int,int> a[301];
pair<int,int> z[301];
// leftfix, leftmove, rightfix, rightmove
ll dp[33][33][33][33];
ll ndp[33][33][33][33];

// - means fixed
// 2 means on the left side

void mn(ll &a, ll b){
	if (b < a) a = b;
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> x[i];
		lab[i] = 1;
	}
	for (int i = 1; i <= m; i++){
		cin >> p[i];
		lab[p[i]+1] = -1;
	}
	// remove fixed opposite pairs

	map<int,vector<int>> rec;
	for (int i = 1; i <= n; i++){
		if (lab[i] != -1) continue;
		if (x[i] == 0){
			lab[i] = -3;
			continue;
		}
		if (rec.count(-x[i])){
			lab[rec[-x[i]].back()] = -3;
			lab[i] = -3;
			rec[-x[i]].pop_back();
			if (rec[-x[i]].empty()) rec.erase(-x[i]);
		} else {
			rec[x[i]].push_back(i);
		}
	}

	int actual = 0;
	for (int i = 1; i <= n; i++){
		if (lab[i] != -3){
			a[++actual] = {x[i], lab[i]};
		}
	}
	if (actual % 2){
		a[++actual] = {0, -1};
	}
	long long ans = 0;
	for (int i = 1; i <= actual; i++){
		if (i <= actual/2){
			a[i].second *= 2;
		} 
		int xx = (abs(a[i].second)==2)?-a[i].first:a[i].first;
		z[i] = {xx, a[i].second};
	}
	sort(z+1, z+actual+1);
	
	// run the dp on z...

	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0][0] = 0;
	z[0].first = z[1].first;
	for (int i = 1; i <= cnt; i++){
		memset(ndp, 0x3f, sizeof(ndp));
		for (int leftfix = 0; leftfix <= i-1; leftfix++){
		for (int leftmove = 0; leftmove <= i-1-leftfix; leftmove++){
		for (int rightfix = 0; rightfix <= i-1-leftfix-leftmove; rightfix++){
		for (int rightmove = 0; rightmove <= i-1-leftfix-leftmove-rightfix; rightmove++){
			ll me = dp[leftfix][leftmove][rightfix][rightmove];
			if (me == INF) continue;
			// cout << leftfix << ' ' << leftmove << ' ' << rightfix << ' ' << rightmove << '\n';
			// cout << me << endl;;
			ll bonus = 1LL*(leftfix+leftmove+rightfix+rightmove)*(z[i].first-z[i-1].first);
			if (z[i].second == -1){
				// right fixed, must find leftmove or accumulate
				if (leftmove) mn(ndp[leftfix][leftmove-1][rightfix][rightmove], me+bonus);
				mn(ndp[leftfix][leftmove][rightfix+1][rightmove], me+bonus);
			} else if (z[i].second == -2){
				if (rightmove) mn(ndp[leftfix][leftmove][rightfix][rightmove-1], me+bonus);
				mn(ndp[leftfix+1][leftmove][rightfix][rightmove], me+bonus);
			} else if (z[i].second == 1){
				// right movable, can find leftmove, leftfix or accumulate
				if (leftfix) mn(ndp[leftfix-1][leftmove][rightfix][rightmove], me+bonus);
				if (leftmove) mn(ndp[leftfix][leftmove-1][rightfix][rightmove], me+bonus);
				mn(ndp[leftfix][leftmove][rightfix][rightmove+1], me+bonus);
			} else if (z[i].second == 2){
				// left movable, can find rightmove, rightfix or accumulate
				if (rightfix) mn(ndp[leftfix][leftmove][rightfix-1][rightmove], me+bonus);
				if (rightmove) mn(ndp[leftfix][leftmove][rightfix][rightmove-1], me+bonus);
				mn(ndp[leftfix][leftmove+1][rightfix][rightmove], me+bonus);
			}
		}}}}
		memcpy(dp, ndp, sizeof(dp));
	}

	ans += dp[0][0][0][0];
	cout << ans << endl;
	return 0;
}


