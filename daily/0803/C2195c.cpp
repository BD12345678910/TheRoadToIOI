// https://cses.fi/problemset/task/2195
#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pt;
 
ll dist(pt a, pt b) {
	return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
}
 
ll ccw(pt b, pt c) {
	return b.X * c.Y - b.Y * c.X;
}
 
ll ccw(pt a, pt b, pt c) {
	b = {b.X - a.X, b.Y - a.Y};
	c = {c.X - a.X, c.Y - a.Y};
	return ccw(b, c);
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	vector<pt> p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i].X >> p[i].Y;
		if (p[i].X < p[0].X || (p[i].X == p[0].X && p[i].Y < p[0].Y))
			swap(p[0], p[i]);
	}
	
 
	sort(p.begin() + 1, p.end(), [&](pt a, pt b) {
		ll o = ccw(p[0], a, b);
		if (o == 0)
			return dist(p[0], a) < dist(p[0], b);
		return o > 0;
	});
 
	for (int i = n - 1; i >= -1; i--) {
		if (i == -1 || ccw(p[0], p[i], p[n - 1]) != 0) {
			reverse(p.begin() + i + 1, p.end());
			break;
		}
	}
 
	int m = 0;
	vector<pt> hull;
	for (int i = 0; i < n; i++) {
		while (m > 2 && ccw(hull[m - 2], hull[m - 1], p[i]) < 0)
			hull.pop_back(), m--;
		hull.push_back(p[i]), m++;
	}
 
	cout << size(hull) << "\n";
	for (auto [x, y]: hull)
		cout << x << " " << y << "\n";
}