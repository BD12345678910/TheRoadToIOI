#include <bits/stdc++.h>
using namespace std;

int n, m;
int cnt[300005];

struct Bird{
	int a, b, d;
} bird[300005];

bool cmp(Bird A, Bird B){
	return A.d < B.d;
}

int ret[300005];

int main(){
	cin >> n >> m;
	int ans = 0;
	for (int i = 1; i <= n; i++){
		cin >> bird[i].a >> bird[i].d >> bird[i].b;
		if (cnt[bird[i].a] == 0) ans++;
		cnt[bird[i].a]++;
	}	
	sort(bird+1, bird+n+1, cmp);
	ret[0] = ans;

	for (int i = 1; i <= n; i++){
		if (cnt[bird[i].a] == 1) ans--;
		cnt[bird[i].a]--;
		if (cnt[bird[i].b] == 0) ans++;
		cnt[bird[i].b]++;

		if (bird[i].d != bird[i+1].d){
			ret[bird[i].d] = ans;
		}
	}
	int last = ret[0];
	for (int i = 1; i <= m; i++){
		if (!ret[i]) cout << last << '\n';
		else {
			cout << ret[i] << '\n';
			last = ret[i];
		}
	}

	return 0;
}