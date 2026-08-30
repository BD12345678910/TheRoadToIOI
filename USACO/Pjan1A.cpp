#include <bits/stdc++.h>
using namespace std;

const long double INF = 1e6;
int n, m;
struct Cow{
	int x, y; long double angle;
} cow[200004], b[400004];
int cnt[400004];
bool win(Cow A, Cow B){
	return 1LL * A.x * B.y > 1LL* A.y * B.x;
}

void solve(){
	cin >> n; cow[m = 0].angle = INF;
	for (int i = 1; i <= n; i++){
		int x,y,z; cin >> x >> y >> z;
		if (x==y && y==z) {
			cow[i].angle = INF;
		} else {
			cow[i] = {x - y, y - z, atan2l(y-z, x-y)};
		}
	}
	sort(cow+1, cow+n+1, [&](Cow A, Cow B){return A.angle < B.angle;});
	for (int i = 1; i <= n; i++){
		if (cow[i].angle == INF) continue;
		if (i ==1 || 1LL*cow[i].x*cow[i-1].y != 1LL*cow[i].y*cow[i-1].x) 
			b[++m] = cow[i];
		cnt[m]++;
	}
	long long ans = 0, s1 = 0, s2 = 0;
	for (int i = 1; i <= m; i++){
		ans += s2*cnt[i];
		s2 += s1*cnt[i];
		s1 += cnt[i];

		b[i+m] = b[i];
		cnt[i+m] = cnt[i];
	}
	int p = 1; s1 = cnt[1]; s2 = 1LL*cnt[1]*cnt[1];
	for (int i = 1; i <= m; i++){
		if (p < i){
			// if nobody remained
			p = i; s1 = cnt[i]; s2 = 1LL*cnt[i]*cnt[i];
		}
		while (p < 2*m && win(b[i], b[p+1])){
			s1 += cnt[++p];
			s2 += 1LL*cnt[p]*cnt[p];
		}
		s1 -= cnt[i]; s2 -= 1LL*cnt[i]*cnt[i];
		ans -= 1LL*cnt[i]*(s1*s1-s2)/2;
		if (!win(b[p+1], b[i]) && p+1 != i+m){
			ans -= 1LL*cnt[i]*cnt[p+1]*s1;
		}
	}
	cout << ans << '\n';
	for (int i = 1; i <= 2*m; i++){
		cnt[i] = 0;
	}

	return;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}
