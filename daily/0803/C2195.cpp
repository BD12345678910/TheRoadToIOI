#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define x first
#define y second
typedef pair<ll,ll> pt;

ll dist(pt a, pt b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

ll cross(pt a, pt b){
	return a.x*b.y-a.y*b.x;
}

ll ccw(pt a, pt b, pt c){
	b = {b.x-a.x, b.y-a.y};
	c = {c.x-a.x, c.y-a.y};
	return cross(b, c);
}

int n;
pt p[200005];
pt sta[200005];

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> p[i].x >> p[i].y;
		if (p[i].x < p[1].x || (p[i].x == p[1].x && p[i].y < p[1].y)){
			swap(p[1], p[i]);
		}
	}
	sort(p+2, p+n+1, [&](pt a, pt b){
		ll o = ccw(p[1], a, b);
		if (o == 0) return dist(p[1], a) < dist(p[1], b);
		else return o > 0;
	});
	for (int i = n; i >= 1; i--){
		if (i == 1 || ccw(p[1], p[i], p[n]) != 0){
			reverse(p+i+1, p+n+1);
			break;
		}
	}
	int tp = 0;
	for (int i = 1; i <= n; i++){
		while (tp >= 2 && ccw(sta[tp-1],sta[tp],p[i]) < 0){
			tp--;
		}
		sta[++tp] = p[i];
	}
	cout << tp << '\n';
	for (int i = 1; i <= tp; i++){
		cout << sta[i].x << ' ' << sta[i].y << '\n';
	}

	return 0;
}



