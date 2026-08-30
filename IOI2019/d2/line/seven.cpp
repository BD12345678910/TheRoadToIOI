#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9+9;
int n, X, Y, cnt, ans;
vector<pair<int,int>> ANS;
void write(){
	ans++;
	ANS.push_back({X,Y});
}

struct point{
	int x, y;
} A[100005];

vector<point> Q;

bool cmp(point A, point B){
	return A.x < B.x;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("07.in", "r", stdin);
	freopen("07.out", "w", stdout);
	cin >> n; ans = 0;
	for (int i = 1; i <= n; i++){
		cin >> A[i].x >> A[i].y;
		Q.push_back(A[i]);
	}
	sort(Q.begin(), Q.end(), cmp);
	Y = INF;
	write();
	bool turn = 1;
	for (auto v : Q){
		if (turn) X = v.x;
		else Y = v.y;
		turn = !turn;
		write();
	}
	if (turn) X = INF;
	else Y = 0;
	write();

	cout << ans << '\n';
	for (auto [x, y]: ANS){
		cout << x << ' ' << y << '\n';
	}

	return 0;
}



